/*********************************************************************************
 *
 *       Copyright (C) 2016-2017 Ichiro Kawazome
 *       All rights reserved.
 * 
 *       Redistribution and use in source and binary forms, with or without
 *       modification, are permitted provided that the following conditions
 *       are met:
 * 
 *         1. Redistributions of source code must retain the above copyright
 *            notice, this list of conditions and the following disclaimer.
 * 
 *         2. Redistributions in binary form must reproduce the above copyright
 *            notice, this list of conditions and the following disclaimer in
 *            the documentation and/or other materials provided with the
 *            distribution.
 * 
 *       THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *       "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *       LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *       A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
 *       OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *       SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *       LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *       DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *       THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *       (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *       OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 ********************************************************************************/
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/stat.h>
#include <linux/limits.h>
#include <linux/types.h>
#include <linux/file.h>
#include <linux/firmware.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/version.h>
#include <linux/fpga/fpga-mgr.h>
#include "minor_number_allocator.h"

#define DRIVER_NAME        "fpgacfg"
#define DEVICE_NAME_FORMAT "fpgacfg%d"

#if     (LINUX_VERSION_CODE >= 0x030B00)
#define USE_DEV_GROUPS      1
#else
#define USE_DEV_GROUPS      0
#endif

#define FPGACFG_MAX_DATA_SIZE (1024*1024*4)

#define U32(ptr) (htonl(*(uint32_t *)(ptr)))
#define U16(ptr) (htons(*(uint16_t *)(ptr)))
#define U8(ptr)	 (*(char *)(ptr))

static struct class*  fpgacfg_sys_class     = NULL;
static dev_t          fpgacfg_device_number = 0;

/**
 * enum buf_states - fpga configuration data buffer states
 * @FPGACFG_BUF_NONE_STATE:       buffer not allocated state
 * @FPGACFG_BUF_EMPTY_STATE:      buffer allocated but buffer empty state
 * @FPGACFG_BUF_HEAD_STORE_STATE: header store from user space (only xilinx bitstream format)
 * @FPGACFG_BUF_DATA_STORE_STATE: data   store from user space
 * @FPGACFG_BUF_DATA_FILL_STATE:  data   store done then buffer fill state
 * @FPGACFG_BUF_FPGA_LOAD_STATE:  buffer load to FPGA state
 * @FPGACFG_BUF_DONE_STATE:       buffer load done state  (buffer not allocated)
 * @FPGACFG_BUF_ERROR_STATE:      buffer error done state (buffer not allocated)
 */
enum   fpgacfg_buf_states {
    FPGACFG_BUF_NONE_STATE       ,
    FPGACFG_BUF_EMPTY_STATE      ,
    FPGACFG_BUF_HEAD_STORE_STATE ,
    FPGACFG_BUF_DATA_STORE_STATE ,
    FPGACFG_BUF_DATA_FILL_STATE  ,
    FPGACFG_BUF_FPGA_LOAD_STATE  ,
    FPGACFG_BUF_DONE_STATE       ,
    FPGACFG_BUF_ERROR_STATE      ,
};
static const char * const fpgacfg_buf_state_str[] = {
    [FPGACFG_BUF_NONE_STATE           ] = "none"        ,
    [FPGACFG_BUF_EMPTY_STATE          ] = "empty"       ,
    [FPGACFG_BUF_HEAD_STORE_STATE     ] = "header store",
    [FPGACFG_BUF_DATA_STORE_STATE     ] = "data store"  ,
    [FPGACFG_BUF_DATA_FILL_STATE      ] = "data fill"   ,
    [FPGACFG_BUF_FPGA_LOAD_STATE      ] = "fpga load"   ,
    [FPGACFG_BUF_DONE_STATE           ] = "done"        ,
    [FPGACFG_BUF_ERROR_STATE          ] = "error"       ,
};

/**
 * enum data_format - 
 * @FPGACFG_FORMAT_RAW_BINARY:
 * @FPGACFG_FORMAT_XILINX_BITSTREAM:
 */
enum   fpgacfg_data_format {
    FPGACFG_FORMAT_RAW_BINARY      ,
    FPGACFG_FORMAT_XILINX_BITSTREAM,
};

static const char * const fpga_mgr_state_str[] = {
    [FPGA_MGR_STATE_UNKNOWN           ] = "unknown",
    [FPGA_MGR_STATE_POWER_OFF         ] = "power off",
    [FPGA_MGR_STATE_POWER_UP          ] = "power up",
    [FPGA_MGR_STATE_RESET             ] = "reset",
    [FPGA_MGR_STATE_FIRMWARE_REQ      ] = "firmware request",
    [FPGA_MGR_STATE_FIRMWARE_REQ_ERR  ] = "firmware request error",
    [FPGA_MGR_STATE_WRITE_INIT        ] = "write init",
    [FPGA_MGR_STATE_WRITE_INIT_ERR    ] = "write init error",
    [FPGA_MGR_STATE_WRITE             ] = "write",
    [FPGA_MGR_STATE_WRITE_ERR         ] = "write error",
    [FPGA_MGR_STATE_WRITE_COMPLETE    ] = "write complete",
    [FPGA_MGR_STATE_WRITE_COMPLETE_ERR] = "write complete error",
    [FPGA_MGR_STATE_OPERATING         ] = "operating",
};

/**
 *
 */
#if (LINUX_VERSION_CODE < 0x040A00)
struct fpga_image_info {
	u32 flags;
};
#endif

/**
 * struct fpgacfg_driver_data - Device driver structure
 */
struct fpgacfg_driver_data {
    struct device*             device;
    struct cdev                cdev;
    dev_t                      device_number;
    struct fpga_manager*       fpga_mgr;
    struct mutex               sem;
    enum   fpgacfg_buf_states  buf_state;
    enum   fpgacfg_data_format data_format;
    void*                      data_buffer;
    size_t                     data_buffer_size;
    size_t                     data_store_size;
    size_t                     max_data_size;
    void*                      head_buffer;
    size_t                     head_buffer_size;
    size_t                     head_store_size;
    bool                       load_start;
    struct fpga_image_info     info;
    bool                       endian_swap;
    bool                       is_open;
    bool                       is_partial_bitstream;
}; 
 
/**
 * fpgacfg_driver_buf_load() - 
 * returns:	Success or error status.
 */
static int fpgacfg_driver_buf_load(struct fpgacfg_driver_data* this)
{
    int status = 0;
    if ((this->buf_state == FPGACFG_BUF_DATA_FILL_STATE) && (this->load_start != 0)) {
        dev_dbg(this->device, "fpga_Mgr_buf_load start\n ");

        this->buf_state = FPGACFG_BUF_FPGA_LOAD_STATE;

        if (this->is_partial_bitstream)
            this->info.flags |=  (FPGA_MGR_PARTIAL_RECONFIG);
        else
            this->info.flags &= ~(FPGA_MGR_PARTIAL_RECONFIG);

#if (LINUX_VERSION_CODE < 0x040A00)
        status = fpga_mgr_buf_load(this->fpga_mgr, this->info.flags, this->data_buffer, this->data_store_size);
#else
        status = fpga_mgr_buf_load(this->fpga_mgr, &this->info     , this->data_buffer, this->data_store_size);
#endif
        this->buf_state = (status == 0) ? FPGACFG_BUF_DONE_STATE : FPGACFG_BUF_ERROR_STATE;

        vfree(this->data_buffer);
        this->data_buffer      = NULL;
        this->data_buffer_size = 0;
        this->data_store_size  = 0;

        dev_dbg(this->device, "fpga_Mgr_buf_load done (%d)\n", status);
    }
    return status;
}
 
#define DEF_ATTR_SHOW(__attr_name, __format, __value)                   \
static ssize_t fpgacfg_show_ ## __attr_name(struct device *dev, struct device_attribute *attr, char *buf) \
{                                                            \
    ssize_t status;                                          \
    struct fpgacfg_driver_data* this = dev_get_drvdata(dev); \
    if (mutex_lock_interruptible(&this->sem) != 0)           \
        return -ERESTARTSYS;                                 \
    status = sprintf(buf, __format, (__value));              \
    mutex_unlock(&this->sem);                                \
    return status;                                           \
}

static inline int NO_ACTION(struct fpgacfg_driver_data* this){return 0;}
 
#define DEF_ATTR_SET(__attr_name, __min, __max, __pre_action, __post_action) \
static ssize_t fpgacfg_set_ ## __attr_name(struct device *dev, struct device_attribute *attr, const char *buf, size_t size) \
{ \
    ssize_t       status; \
    unsigned long value;  \
    struct fpgacfg_driver_data* this = dev_get_drvdata(dev);                 \
    if (0 != mutex_lock_interruptible(&this->sem)){return -ERESTARTSYS;}     \
    if (0 != (status = kstrtoul(buf, 10, &value))){            goto failed;} \
    if ((value < __min) || (__max < value)) {status = -EINVAL; goto failed;} \
    if (0 != (status = __pre_action(this)))       {            goto failed;} \
    this->__attr_name = value;                                               \
    if (0 != (status = __post_action(this)))      {            goto failed;} \
    status = size;                                                           \
  failed:                                                                    \
    mutex_unlock(&this->sem);                                                \
    return status;                                                           \
}
 
DEF_ATTR_SET( load_start          , 0, 1                               , NO_ACTION, fpgacfg_driver_buf_load);
DEF_ATTR_SET( max_data_size       , 0, FPGACFG_MAX_DATA_SIZE+1         , NO_ACTION, NO_ACTION              );
DEF_ATTR_SET( data_format         , 0, sizeof(enum fpgacfg_data_format), NO_ACTION, NO_ACTION              );
DEF_ATTR_SET( is_partial_bitstream, 0, 1                               , NO_ACTION, NO_ACTION              );

DEF_ATTR_SHOW(load_start          , "%d\n"       , this->load_start                                        );
DEF_ATTR_SHOW(max_data_size       , "%d\n"       , this->max_data_size                                     );
DEF_ATTR_SHOW(data_format         , "%d\n"       , this->data_format                                       );
DEF_ATTR_SHOW(is_partial_bitstream, "%d\n"       , this->is_partial_bitstream                              );
DEF_ATTR_SHOW(data_buffer_size    , "%d\n"       , this->data_buffer_size                                  );
DEF_ATTR_SHOW(data_store_size     , "%d\n"       , this->data_store_size                                   );
DEF_ATTR_SHOW(head_buffer_size    , "%d\n"       , this->head_buffer_size                                  );
DEF_ATTR_SHOW(head_store_size     , "%d\n"       , this->head_store_size                                   );
DEF_ATTR_SHOW(flags               , "0x%08X\n"   , this->info.flags                                        );
DEF_ATTR_SHOW(buffer_state        , "%s\n"       , fpgacfg_buf_state_str[this->buf_state]                  );
DEF_ATTR_SHOW(fpga_mgr_state      , "%s\n"       , fpga_mgr_state_str[this->fpga_mgr->state]               );
 
static struct device_attribute fpgacfg_device_attrs[] = {
  __ATTR(load_start           , 0664, fpgacfg_show_load_start           , fpgacfg_set_load_start           ),
  __ATTR(max_data_size        , 0664, fpgacfg_show_max_data_size        , fpgacfg_set_max_data_size        ),
  __ATTR(data_format          , 0664, fpgacfg_show_data_format          , fpgacfg_set_data_format          ),
  __ATTR(is_partial_bitstream , 0664, fpgacfg_show_is_partial_bitstream , fpgacfg_set_is_partial_bitstream ),
  __ATTR(data_buffer_size     , 0444, fpgacfg_show_data_buffer_size     , NULL                             ),
  __ATTR(data_store_size      , 0444, fpgacfg_show_data_store_size      , NULL                             ),
  __ATTR(head_buffer_size     , 0444, fpgacfg_show_head_buffer_size     , NULL                             ),
  __ATTR(head_store_size      , 0444, fpgacfg_show_head_store_size      , NULL                             ),
  __ATTR(flags                , 0444, fpgacfg_show_flags                , NULL                             ),
  __ATTR(buffer_state         , 0444, fpgacfg_show_buffer_state         , NULL                             ),
  __ATTR(fpga_mgr_state       , 0444, fpgacfg_show_fpga_mgr_state       , NULL                             ),
  __ATTR_NULL,
};
 
#if (USE_DEV_GROUPS == 1)
static struct attribute *fpgacfg_attrs[] = {
  &(fpgacfg_device_attrs[ 0].attr),
  &(fpgacfg_device_attrs[ 1].attr),
  &(fpgacfg_device_attrs[ 2].attr),
  &(fpgacfg_device_attrs[ 3].attr),
  &(fpgacfg_device_attrs[ 4].attr),
  &(fpgacfg_device_attrs[ 5].attr),
  &(fpgacfg_device_attrs[ 6].attr),
  &(fpgacfg_device_attrs[ 7].attr),
  &(fpgacfg_device_attrs[ 8].attr),
  &(fpgacfg_device_attrs[ 9].attr),
  &(fpgacfg_device_attrs[10].attr),
  NULL
};
static struct attribute_group  fpgacfg_attr_group = {
  .attrs = fpgacfg_attrs
};
static const struct attribute_group* fpgacfg_attr_groups[] = {
  &fpgacfg_attr_group,
  NULL
};
#define SET_SYS_CLASS_ATTRIBUTES(sys_class) {(sys_class)->dev_groups = fpgacfg_attr_groups; }
#else
#define SET_SYS_CLASS_ATTRIBUTES(sys_class) {(sys_class)->dev_attrs  = fpgacfg_device_attrs;}
#endif
 
/**
 * fpgacfg_driver_file_open() - This is the driver open function.
 * @inode:	Pointer to the inode structure of this device.
 * @file:	Pointer to the file structure.
 * returns:	Success or error status.
 */
static int fpgacfg_driver_file_open(struct inode *inode, struct file *file)
{
    struct fpgacfg_driver_data* this;
    int status = 0;

    this = container_of(inode->i_cdev, struct fpgacfg_driver_data, cdev);
    file->private_data = this;
    if (this->data_buffer != NULL) {
        vfree(this->data_buffer);
        this->data_buffer      = NULL;
        this->data_buffer_size = 0;
    }
    this->buf_state       = FPGACFG_BUF_NONE_STATE;
    this->data_store_size = 0;
    this->is_open         = 1;
    this->endian_swap     = 0;

    return status;
}
 
/**
 * fpgacfg_driver_file_release() - This is the driver release function.
 * @inode:	Pointer to the inode structure of this device.
 * @file:	Pointer to the file structure.
 * returns:	Success.
 */
static int fpgacfg_driver_file_release(struct inode *inode, struct file *file)
{
    struct fpgacfg_driver_data* this = file->private_data;
 
    if (this->head_buffer != NULL) {
        kfree(this->head_buffer);
        this->head_buffer      = NULL;
        this->head_buffer_size = 0;
        this->head_store_size  = 0;
    }
    this->is_open = 0;
    return 0;
}

/**
 * fpgacfg_driver_file_write_xilinx_bitstream() - This is the driver write function for xilinx bitstream format.
 * @file:	Pointer to the file structure.
 * @buff:	Pointer to the user buffer.
 * @count:	The number of bytes to be written.
 * @ppos:	Pointer to the offset value
 * returns:	Success or error status.
 */
static ssize_t fpgacfg_driver_file_write_xilinx_bitstream(struct file* file, const char __user* buff, size_t count, loff_t* ppos)
{
    struct fpgacfg_driver_data* this      = file->private_data;
    int                         result    = 0;
    size_t                      xfer_size;
 
    dev_dbg(this->device, "%s start (count = %d, buf_status = %s)\n",
            __func__,
            count,
            fpgacfg_buf_state_str[this->buf_state]
    );
              
    if (count == 0) 
        return 0;
 
    if (mutex_lock_interruptible(&this->sem))
        return -ERESTARTSYS;
 
    if (this->buf_state == FPGACFG_BUF_NONE_STATE) {
        if (*ppos != 0) {
            result = -ENOSPC;
            goto return_unlock;
        }
        this->head_buffer = kmalloc(4096, GFP_KERNEL);
        if (IS_ERR_OR_NULL(this->head_buffer)) {
            result = -EFAULT;
            this->head_buffer      = NULL;
            this->head_buffer_size = 0;
            goto return_unlock;
        }
        this->head_buffer_size = 4096;
        this->head_store_size  = 0;
        this->buf_state        = FPGACFG_BUF_HEAD_STORE_STATE;
    }

    if (this->buf_state == FPGACFG_BUF_HEAD_STORE_STATE) {
        unsigned int pos = 0;
	uint32_t     u32;
	uint16_t     u16;
	uint8_t      u8;
        xfer_size = (*ppos + count >= this->head_buffer_size) ? this->head_buffer_size - *ppos : count;
        if (copy_from_user(this->head_buffer + this->head_store_size, buff, xfer_size) != 0) {
            result = -EFAULT;
            goto return_unlock;
        }
        *ppos += xfer_size;
        this->head_store_size = *ppos;
        if (this->head_store_size < this->head_buffer_size) {
            result = xfer_size;
            goto return_unlock;
        }
#define XBF_ERR  "Xilinx BitStream Format Error: "
#define XBF_INFO "Xilinx BitStream Format Info : "
	/*
	 * Field 1:
	 * 2 bytes          length 0x0009           (big endian) 
	 * 9 bytes          some sort of header
	 */
	u16 = U16(this->head_buffer+ pos);
	if (u16 != 9) {
            dev_err(this->device, XBF_ERR "Field1's length should be 9 but is %d\n", u16);
            result = -EFAULT;
            goto return_unlock;
        }
	pos += 2;
	pos += u16;
	/*
	 * Field 2
	 * 2 bytes          length 0x0001 
	 * 1 byte           key 0x61                (The letter "a")
	 */
	u16 = U16(this->head_buffer + pos);
	if (u16 != 1) {
            dev_err(this->device, XBF_ERR "Field2's length should be 1 but is %d\n", u16);
            result = -EFAULT;
            goto return_unlock;
        }
        pos += 2;
        u8 = U8(this->head_buffer + pos);
        if (u8 != 0x61) {
            dev_err(this->device, XBF_ERR "Field2's Magic 'a' missing (%#hhx)\n", u8);
            result = -EFAULT;
            goto return_unlock;
        }
        pos += 1;
	/*
	 * Field 3 
	 * 2 bytes          length                 (value depends on file name length) 
	 * 10 bytes         string design name "xform.ncd" (including a trailing 0x00) 
	 */
	u16 = U16(this->head_buffer + pos);
        pos += 2;
        dev_dbg(this->device, XBF_INFO "design name = %s\n", (char*)(this->head_buffer + pos));
        pos += u16;
	/*
	 * Field 4 
	 * 1 byte           key 0x62                (The letter "b") 
	 * 2 bytes          length                  (value depends on part name length) 
	 * 12 bytes         string part name "v1000efg860" (including a  trailing 0x00)
	 */
	u8  = U8(this->head_buffer + pos);
        if (u8 != 0x62) {
            dev_err(this->device, XBF_ERR "Field4's Magic 'b' missing (%#hhx)\n", u8);
            result = -EFAULT;
            goto return_unlock;
        }
        pos += 1;
	u16 = U16(this->head_buffer + pos);
        pos += 2;
        dev_dbg(this->device, XBF_INFO "part name = %s\n", (char*)(this->head_buffer + pos));
        pos += u16;
	/*
	 * Field 5
	 * 1 byte           key 0x63                 (The letter "c") 
	 * 2 bytes          length 0x000b
	 * 11 bytes         string date "2001/08/10" (including a trailing 0x00)
	 */
	u8  = U8(this->head_buffer + pos);
        if (u8 != 0x63) {
            dev_err(this->device, XBF_ERR "Field5's Magic 'c' missing (%#hhx)\n", u8);
            result = -EFAULT;
            goto return_unlock;
        }
        pos += 1;
	u16 = U16(this->head_buffer + pos);
        pos += 2;
        dev_dbg(this->device, XBF_INFO "date = %s\n", (char*)(this->head_buffer + pos));
        pos += u16;
	/*
	 * Field 6
	 * 1 byte           key 0x64                 (The letter "d") 
	 * 2 bytes          length 0x0009
	 * 9 bytes          string time "06:55:04"   (including a trailing 0x00)
	 */
	u8  = U8(this->head_buffer + pos);
        if (u8 != 0x64) {
            dev_err(this->device, XBF_ERR "Field6's Magic 'd' missing (%#hhx)\n", u8);
            result = -EFAULT;
            goto return_unlock;
        }
        pos += 1;
	u16 = U16(this->head_buffer + pos);
        pos += 2;
        dev_dbg(this->device, XBF_INFO "time = %s\n", (char*)(this->head_buffer + pos));
        pos += u16;
	/*
	 * Field 7 
	 * 1 byte           key 0x65                 (The letter "e") 
	 * 4 bytes          length                   (value depends on device type,
	 *                                            and maybe design details) 
	 */
	u8  = U8(this->head_buffer + pos);
        if (u8 != 0x65) {
            dev_err(this->device, XBF_ERR "Field7's Magic 'e' missing (%#hhx)\n", u8);
            result = -EFAULT;
            goto return_unlock;
        }
        pos += 1;
	u32 = U32(this->head_buffer + pos);
        pos += 4;
        dev_dbg(this->device, XBF_INFO "size = %d\n", u32);
        this->data_buffer_size = u32;
        /*
         * Look for sync word
         */
        {
            int  i;
            bool found = 0;
            for (i = pos; i < this->head_store_size - 4; i++) {
                if (memcmp(this->head_buffer + i, "\x66\x55\x99\xAA", 4) == 0) {
                    dev_dbg(this->device, XBF_INFO "Found normal sync word\n");
                    this->endian_swap = 0;
                    found = 1;
                    break;
                }
                if (memcmp(this->head_buffer + i, "\xAA\x99\x55\x66", 4) == 0) {
                    dev_dbg(this->device, XBF_INFO "Found swapped sync word\n");
                    this->endian_swap = 1;
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                dev_err(this->device, XBF_ERR "Not Found sync word\n");
                result = -EFAULT;
                goto return_unlock;
            }
        }
        this->head_store_size  = pos;
        /*
         *
         */
        this->data_buffer      = vmalloc(this->data_buffer_size);
        if (IS_ERR_OR_NULL(this->data_buffer)) {
            result = -EFAULT;
            this->data_buffer      = NULL;
            this->data_buffer_size = 0;
            goto return_unlock;
        }
        memcpy(this->data_buffer,
               this->head_buffer      + this->head_store_size,
               this->head_buffer_size - this->head_store_size);
        this->data_store_size  = this->head_buffer_size - this->head_store_size;
        this->buf_state = FPGACFG_BUF_DATA_STORE_STATE;
        result = xfer_size;
        goto return_unlock;
    }

    if (this->buf_state == FPGACFG_BUF_DATA_STORE_STATE) {
        int    load_status;
        size_t data_pos  = *ppos - this->head_store_size;
        size_t xfer_size = (data_pos + count >= this->data_buffer_size) ? this->data_buffer_size - data_pos : count;
        if (copy_from_user(this->data_buffer + this->data_store_size, buff, xfer_size) != 0) {
            result = -EFAULT;
            goto return_unlock;
        }
        this->data_store_size += xfer_size;
        if (this->data_store_size >= this->data_buffer_size) {
            if (this->endian_swap) {
                int i;
                for (i = 0; i < this->data_store_size; i += 4) {
                  uint32_t *p = (uint32_t *)(this->data_buffer + i);
                    *p = swab32(*p);
                }
            }
            this->buf_state = FPGACFG_BUF_DATA_FILL_STATE;
        }
        load_status = fpgacfg_driver_buf_load(this);
        if (load_status != 0) {
            result = load_status;
            goto return_unlock;
        }
        *ppos += xfer_size;
        result = xfer_size;
    }

 return_unlock:
    mutex_unlock(&this->sem);
    dev_dbg(this->device, "%s done (result = %d, buf_state = %s)\n",
            __func__,
            result  ,
            fpgacfg_buf_state_str[this->buf_state]
    );
    return result;
}

/**
 * fpgacfg_driver_file_write_raw_binary() - This is the driver write function for raw binary format.
 * @file:	Pointer to the file structure.
 * @buff:	Pointer to the user buffer.
 * @count:	The number of bytes to be written.
 * @ppos:	Pointer to the offset value
 * returns:	Success or error status.
 */
static ssize_t fpgacfg_driver_file_write_raw_binary(struct file* file, const char __user* buff, size_t count, loff_t* ppos)
{
    struct fpgacfg_driver_data* this      = file->private_data;
    int                         result    = 0;
    size_t                      xfer_size;
 
    dev_dbg(this->device, "%s start (count = %d, buf_status = %s)\n",
            __func__,
            count,
            fpgacfg_buf_state_str[this->buf_state]
    );
              
    if (count == 0) 
        return 0;
 
    if (mutex_lock_interruptible(&this->sem))
        return -ERESTARTSYS;
 
    if (this->buf_state == FPGACFG_BUF_NONE_STATE) {
        if (*ppos != 0) {
            result = -ENOSPC;
            goto return_unlock;
        }
        if (this->max_data_size == 0) {
            result = -ENOSPC;
            goto return_unlock;
        }
        this->data_buffer = vmalloc(this->max_data_size);
        if (IS_ERR_OR_NULL(this->data_buffer)) {
            result = -ENOSPC;
            this->data_buffer      = NULL;
            this->data_buffer_size = 0;
            goto return_unlock;
        }
        this->data_buffer_size = this->max_data_size;
        this->data_store_size  = 0;
        this->buf_state        = FPGACFG_BUF_EMPTY_STATE;
    }
                 
    if (this->buf_state == FPGACFG_BUF_EMPTY_STATE) {
        this->buf_state  = FPGACFG_BUF_DATA_STORE_STATE;
    }

    xfer_size = (*ppos + count >= this->data_buffer_size) ? this->data_buffer_size - *ppos : count;

    if ((xfer_size == 0) ||
        (this->buf_state != FPGACFG_BUF_DATA_STORE_STATE)) {
        result = -ENOSPC;
        goto return_unlock;
    }

    if (copy_from_user(this->data_buffer + *ppos, buff, xfer_size) != 0) {
        result = -EFAULT;
        goto return_unlock;
    }
    *ppos += xfer_size;
    this->data_store_size = *ppos;
 
    if (this->data_store_size >= this->data_buffer_size) {
        this->buf_state = FPGACFG_BUF_DATA_FILL_STATE;
    }
              
    {
        int load_status = fpgacfg_driver_buf_load(this);
        if (load_status != 0) {
            result = load_status;
            goto return_unlock;
        }
    }
 
    result = xfer_size;
 
  return_unlock:
    mutex_unlock(&this->sem);
    dev_dbg(this->device, "%s done (result = %d, buf_state = %s)\n",
            __func__,
            result  ,
            fpgacfg_buf_state_str[this->buf_state]
    );
    return result;
}

/**
 * fpgacfg_driver_file_write() - This is the driver write function.
 * @file:	Pointer to the file structure.
 * @buff:	Pointer to the user buffer.
 * @count:	The number of bytes to be written.
 * @ppos:	Pointer to the offset value
 * returns:	Success or error status.
 */
static ssize_t fpgacfg_driver_file_write(struct file* file, const char __user* buff, size_t count, loff_t* ppos)
{
    struct fpgacfg_driver_data* this = file->private_data;
    switch (this->data_format) {
        case FPGACFG_FORMAT_RAW_BINARY :
            return fpgacfg_driver_file_write_raw_binary(file, buff, count, ppos);
        case FPGACFG_FORMAT_XILINX_BITSTREAM :
            return fpgacfg_driver_file_write_xilinx_bitstream(file, buff, count, ppos);
        default :
            return -EFAULT;
    }
}

/**
 *
 */
static const struct file_operations fpgacfg_driver_file_ops = {
    .owner   = THIS_MODULE,
    .open    = fpgacfg_driver_file_open,
    .release = fpgacfg_driver_file_release,
 // .read    = fpgacfg_driver_file_read,
    .write   = fpgacfg_driver_file_write,
};
 
/**
 * fpgacfg_device_minor_number_bitmap
 */
DECLARE_MINOR_NUMBER_ALLOCATOR(fpgacfg_device, 32);
 
/**
 * fpgacfg_platform_driver_probe() -  Probe call for the device.
 *
 * @pdev:	handle to the platform device structure.
 * Returns 0 on success, negative error otherwise.
 *
 * It does all the memory allocation and registration for the device.
 */
static int fpgacfg_platform_driver_probe(struct platform_device *pdev)
{
    int                         retval = 0;
    struct fpgacfg_driver_data* this   = NULL;
    const char*                 device_name;
    int                         minor_number;
    unsigned int                done     = 0;
    const unsigned int          DONE_MINOR_ALLOC   = (1 << 0);
    const unsigned int          DONE_CHRDEV_ADD    = (1 << 1);
    const unsigned int          DONE_FPGA_MGR_GET  = (1 << 2);
    const unsigned int          DONE_DEVICE_CREATE = (1 << 3);
 
    dev_info(&pdev->dev, "driver probe start.\n");
    /*
     * create (fpgacfg_driver_data*) this.
     */
    {
        this = kzalloc(sizeof(*this), GFP_KERNEL);
        if (IS_ERR_OR_NULL(this)) {
            retval = PTR_ERR(this);
            this   = NULL;
            goto failed;
        }
        this->device               = NULL;
        this->fpga_mgr             = NULL;
        this->device_number        = 0;
        this->data_buffer          = NULL;
        this->data_buffer_size     = 0;
        this->data_store_size      = 0;
        this->head_buffer          = NULL;
        this->head_buffer_size     = 0;
        this->head_store_size      = 0;
        this->buf_state            = FPGACFG_BUF_NONE_STATE;
        this->max_data_size        = FPGACFG_MAX_DATA_SIZE;
        this->data_format          = FPGACFG_FORMAT_RAW_BINARY;
        this->load_start           = 0;
        this->is_partial_bitstream = 0;
    }
    /*
     * get device number
     */
    dev_dbg(&pdev->dev, "get device_number start\n");
    {
        minor_number = fpgacfg_device_minor_number_new();
        if (minor_number < 0) {
            dev_err(&pdev->dev, "invalid or conflict minor number %d.\n", minor_number);
            retval = -ENODEV;
            goto failed;
        }
        this->device_number = MKDEV(MAJOR(fpgacfg_device_number), minor_number);
        done |= DONE_MINOR_ALLOC;
    }
    dev_dbg(&pdev->dev, "get device_number done\n");
 
    /*
     * get fpga manager
     */
    dev_dbg(&pdev->dev, "get fpga manager start\n");
    {
        struct device_node*  node;
        char*                path;
        path = (char*)of_get_property(pdev->dev.of_node, "fpga-manager-path", NULL);
        if (IS_ERR_OR_NULL(path)) {
            node = of_parse_phandle(pdev->dev.of_node, "fpga-manager", 0);
            if (IS_ERR_OR_NULL(node)) {
                dev_err(&pdev->dev, "not found fpga-manager property\n");
                retval = PTR_ERR(node);
                goto failed;
            }
        } else {
            node = of_find_node_by_path(path);
            if (IS_ERR_OR_NULL(node)) {
                dev_err(&pdev->dev, "not found fpga-manager-path = %s\n", path);
                retval = PTR_ERR(node);
                goto failed;
            }
        }
        this->fpga_mgr = of_fpga_mgr_get(node);
        if (IS_ERR_OR_NULL(this->fpga_mgr)) {
            dev_err(&pdev->dev, "of_fpga_mgr_get() fail.\n");
            retval = PTR_ERR(this->fpga_mgr);
            of_node_put(node);
            goto failed;
        }
        of_node_put(node);
        done |= DONE_FPGA_MGR_GET;
    }
    dev_dbg(&pdev->dev, "get fpga manager done\n");
     
    /*
     * get device name
     */
    dev_dbg(&pdev->dev, "get device name start\n");
    {
        device_name = of_get_property(pdev->dev.of_node, "name", NULL);
         
        if (IS_ERR_OR_NULL(device_name)) {
            device_name = dev_name(&pdev->dev);
        }
    }
    dev_dbg(&pdev->dev, "get device name done\n");

    /*
     * get file format
     */
    dev_dbg(&pdev->dev, "get data format start\n");
    {
        int          status;
        unsigned int data_format;
        status = of_property_read_u32(pdev->dev.of_node, "data-format", &data_format);
        if (status == 0) {
            if (data_format >= sizeof(enum fpgacfg_data_format)) {
                dev_err(&pdev->dev, "invalid data format property %d\n", data_format);
                goto failed;
            }
            this->data_format = data_format;
        }
    }
    dev_dbg(&pdev->dev, "get data format done\n");
 
    /*
     * get auto start
     */
    dev_dbg(&pdev->dev, "get auto start start\n");
    {
        int          status;
        unsigned int load_start;
        status = of_property_read_u32(pdev->dev.of_node, "load-start", &load_start);
        if (status == 0) {
            if (load_start > 1) {
                dev_err(&pdev->dev, "invalid auto start property %d\n", load_start);
                goto failed;
            }
            this->load_start = load_start;
        }
    }
    dev_dbg(&pdev->dev, "get auto start done\n");
 
    /*
     * create device
     */
    dev_dbg(&pdev->dev, "device_create start\n");
    {
        this->device = device_create(fpgacfg_sys_class,
                                     NULL,
                                     this->device_number,
                                     (void *)this,
                                     device_name);
        if (IS_ERR_OR_NULL(this->device)) {
            dev_err(&pdev->dev, "device create falied\n");
            goto failed;
        }
        done |= DONE_DEVICE_CREATE;
    }
    dev_dbg(&pdev->dev, "device_create done\n");
 
    /*
     * add chrdev.
     */
    {
        cdev_init(&this->cdev, &fpgacfg_driver_file_ops);
        this->cdev.owner = THIS_MODULE;
        if (cdev_add(&this->cdev, this->device_number, 1) != 0) {
            dev_err(&pdev->dev, "cdev_add() failed\n");
            goto failed;
        }
        done |= DONE_CHRDEV_ADD;
    }
 
    /*
     *
     */
    mutex_init(&this->sem);
    dev_set_drvdata(&pdev->dev, this);
     
    dev_info(&pdev->dev, "driver installed.\n");
    dev_info(&pdev->dev, "device name  : %s\n" , device_name);
    dev_info(&pdev->dev, "fpga manager : %s\n" , this->fpga_mgr->name);
    return 0;
 
 failed:
    if (done & DONE_CHRDEV_ADD   ) { cdev_del(&this->cdev); }
    if (done & DONE_DEVICE_CREATE) { device_destroy(fpgacfg_sys_class, this->device_number);}
    if (done & DONE_FPGA_MGR_GET ) { fpga_mgr_put(this->fpga_mgr); }
    if (done & DONE_MINOR_ALLOC  ) { fpgacfg_device_minor_number_free(minor_number);}
    if (this != NULL)              { kfree(this); }
    dev_info(&pdev->dev, "driver install failed.\n");
    return retval;
}
 
/**
 * fpgacfg_platform_driver_remove() -  Remove call for the device.
 *
 * @pdev:	handle to the platform device structure.
 * Returns 0 or error status.
 *
 * Unregister the device after releasing the resources.
 */
static int fpgacfg_platform_driver_remove(struct platform_device *pdev)
{
    struct fpgacfg_driver_data* this = dev_get_drvdata(&pdev->dev);
 
    if (!this)
        return -ENODEV;

    if (this->head_buffer != NULL) {
        kfree(this->head_buffer);
        this->head_buffer      = NULL;
        this->head_buffer_size = 0;
    }
    
    if (this->data_buffer != NULL) {
        vfree(this->data_buffer);
        this->data_buffer      = NULL;
        this->data_buffer_size = 0;
    }

    cdev_del(&this->cdev);
    device_destroy(fpgacfg_sys_class, this->device_number);
    fpga_mgr_put(this->fpga_mgr);
    fpgacfg_device_minor_number_free(MINOR(this->device_number));
    kfree(this);
    dev_set_drvdata(&pdev->dev, NULL);
    dev_info(&pdev->dev, "driver unloaded\n");
    return 0;
}
 
/**
 * Open Firmware Device Identifier Matching Table
 */
static struct of_device_id fpgacfg_of_match[] = {
    { .compatible = "ikwzm,fpgacfg-0.10.a", },
    { /* end of table */}
};
MODULE_DEVICE_TABLE(of, fpgacfg_of_match);
 
/**
 * Platform Driver Structure
 */
static struct platform_driver fpgacfg_platform_driver = {
    .probe  = fpgacfg_platform_driver_probe,
    .remove = fpgacfg_platform_driver_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name  = DRIVER_NAME,
        .of_match_table = fpgacfg_of_match,
    },
};
static bool fpgacfg_platform_driver_done = 0;
 
/**
 * fpga_module_exit()
 */
static void __exit fpgacfg_module_exit(void)
{
    if (fpgacfg_platform_driver_done ){platform_driver_unregister(&fpgacfg_platform_driver);}
    if (fpgacfg_sys_class     != NULL){class_destroy(fpgacfg_sys_class);}
    if (fpgacfg_device_number != 0   ){unregister_chrdev_region(fpgacfg_device_number, 0);}
}
 
/**
 * dtbocfg_module_init()
 */
static int __init fpgacfg_module_init(void)
{
    int retval = 0;

    fpgacfg_device_minor_number_allocator_initilize();

    retval = alloc_chrdev_region(&fpgacfg_device_number, 0, 0, DRIVER_NAME);
    if (retval != 0) {
        printk(KERN_ERR "%s: couldn't allocate device major number\n", DRIVER_NAME);
        fpgacfg_device_number = 0;
        goto failed;
    }
 
    fpgacfg_sys_class = class_create(THIS_MODULE, DRIVER_NAME);
    if (IS_ERR_OR_NULL(fpgacfg_sys_class)) {
        printk(KERN_ERR "%s: couldn't create sys class\n", DRIVER_NAME);
        retval = PTR_ERR(fpgacfg_sys_class);
        fpgacfg_sys_class = NULL;
        goto failed;
    }
    SET_SYS_CLASS_ATTRIBUTES(fpgacfg_sys_class);

    retval = platform_driver_register(&fpgacfg_platform_driver);
    if (retval) {
        printk(KERN_ERR "%s: couldn't register platform driver\n", DRIVER_NAME);
    } else {
        fpgacfg_platform_driver_done = 1;
    }
    return 0;
 
  failed:
    fpgacfg_module_exit();
    return retval;
}

module_init(fpgacfg_module_init);
module_exit(fpgacfg_module_exit);

MODULE_AUTHOR("ikwzm");
MODULE_DESCRIPTION("FPGA Configuration Driver");
MODULE_LICENSE("Dual BSD/GPL");
