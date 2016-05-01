/*********************************************************************************
 *
 *       Copyright (C) 2016 Ichiro Kawazome
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
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_fdt.h>
#include <linux/stat.h>
#include <linux/limits.h>
#include <linux/types.h>
#include <linux/file.h>
#include <linux/firmware.h>
#include <linux/fs.h>
#include <linux/version.h>
#include "minor_number_allocator.h"

#define DRIVER_NAME        "fclkcfg"

#if     (LINUX_VERSION_CODE >= 0x030B00)
#define USE_DEV_GROUPS      1
#else
#define USE_DEV_GROUPS      0
#endif

static struct class*  fclkcfg_sys_class     = NULL;
static dev_t          fclkcfg_device_number = 0;

/**
 * struct fclk_driver_data - Device driver structure
 */
struct fclk_driver_data {
    struct device*       device;
    struct clk*          clk;
    dev_t                device_number;
    unsigned long        round_rate;
};


/**
 * fclk_show_enable()
 */
static ssize_t fclk_show_enable(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct fclk_driver_data* this = dev_get_drvdata(dev);
    return sprintf(buf, "%d\n", __clk_is_enabled(this->clk));
}

/**
 * fclk_set_enable()
 */
static ssize_t fclk_set_enable(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    ssize_t       status = 0;
    unsigned long enable;
    struct fclk_driver_data* this = dev_get_drvdata(dev);

    if (0 != (status = kstrtoul(buf, 0, &enable)))
        return status;

    if (enable) {
        if (__clk_is_enabled(this->clk) == false) {
            status = clk_prepare_enable(this->clk);
            if (status) {
                dev_err(this->device, "enable failed.");
                return status;
            }
            else {
                dev_dbg(this->device, "enable success.");
                return size;
            }
        } else {
                return size;
        }
    } else {
        if (__clk_is_enabled(this->clk) == true) {
            clk_disable_unprepare(this->clk);
            dev_dbg(this->device, "disable done.");
        }
        return size;
    }
}

/**
 * fclk_show_rate()
 */
static ssize_t fclk_show_rate(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct fclk_driver_data* this = dev_get_drvdata(dev);
    return sprintf(buf, "%lu\n", clk_get_rate(this->clk));
}

/**
 * fclk_set_rate()
 */
static ssize_t fclk_set_rate(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    ssize_t       status;
    unsigned long rate;
    unsigned long round_rate;
    struct fclk_driver_data* this = dev_get_drvdata(dev);

    if (0 != (status = kstrtoul(buf, 0, &rate)))
        return status;

    round_rate = clk_round_rate(this->clk, rate);
    status     = clk_set_rate(this->clk, round_rate);

    if (status) {
        dev_err(this->device, "set_rate(%lu=>%lu) failed." , rate, round_rate);
        return status;
    } else {
        dev_dbg(this->device, "set_rate(%lu=>%lu) success.", rate, round_rate);
        return size;
    }
}

/**
 * fclk_show_round_rate()
 */
static ssize_t fclk_show_round_rate(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct fclk_driver_data* this = dev_get_drvdata(dev);
    return sprintf(buf, "%lu => %lu\n",
                   this->round_rate,
                   clk_round_rate(this->clk, this->round_rate)
    );
}

/**
 * fclk_set_round_rate()
 */
static ssize_t fclk_set_round_rate(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    ssize_t       status;
    unsigned long round_rate;
    struct fclk_driver_data* this = dev_get_drvdata(dev);

    if (0 != (status = kstrtoul(buf, 0, &round_rate)))
        return status;
    this->round_rate = round_rate;
    return size;
}

static struct device_attribute fclkcfg_device_attrs[] = {
  __ATTR(enable    , 0664, fclk_show_enable    , fclk_set_enable    ),
  __ATTR(rate      , 0664, fclk_show_rate      , fclk_set_rate      ),
  __ATTR(round_rate, 0664, fclk_show_round_rate, fclk_set_round_rate),
  __ATTR_NULL,
};

#if (USE_DEV_GROUPS == 1)
static struct attribute *fclkcfg_attrs[] = {
  &(fclkcfg_device_attrs[0].attr),
  &(fclkcfg_device_attrs[1].attr),
  &(fclkcfg_device_attrs[2].attr),
  NULL
};
static struct attribute_group  fclkcfg_attr_group = {
  .attrs = fclkcfg_attrs
};
static const struct attribute_group* fclkcfg_attr_groups[] = {
  &fclkcfg_attr_group,
  NULL
};
#define SET_SYS_CLASS_ATTRIBUTES(sys_class) {(sys_class)->dev_groups = fclkcfg_attr_groups; }
#else
#define SET_SYS_CLASS_ATTRIBUTES(sys_class) {(sys_class)->dev_attrs  = fclkcfg_device_attrs;}
#endif

/**
 * fclkcfg_device_minor_number_bitmap
 */
DECLARE_MINOR_NUMBER_ALLOCATOR(fclkcfg_device, 64);

/**
 * fclkcfg_platform_driver_probe() -  Probe call for the device.
 *
 * @pdev:	handle to the platform device structure.
 * Returns 0 on success, negative error otherwise.
 *
 * It does all the memory allocation and registration for the device.
 */
static int fclkcfg_platform_driver_probe(struct platform_device *pdev)
{
    int                      retval = 0;
    struct fclk_driver_data* this   = NULL;
    const char*              device_name;

    dev_dbg(&pdev->dev, "driver probe start.\n");
    /*
     * create (fclk_driver_data*) this.
     */
    {
        this = kzalloc(sizeof(*this), GFP_KERNEL);
        if (IS_ERR_OR_NULL(this)) {
            retval = PTR_ERR(this);
            this   = NULL;
            goto failed;
        }
        this->device        = NULL;
        this->clk           = NULL;
        this->device_number = 0;
    }
    /*
     * get device number
     */
    dev_dbg(&pdev->dev, "get device_number start.\n");
    {
        int minor_number = fclkcfg_device_minor_number_new();
        if (minor_number < 0) {
            dev_err(&pdev->dev, "invalid or conflict minor number %d.\n", minor_number);
            retval = -ENODEV;
            goto failed;
        }
        this->device_number = MKDEV(MAJOR(fclkcfg_device_number), minor_number);
    }
    dev_dbg(&pdev->dev, "get device_number done.\n");

    /*
     * get clk
     */
    dev_dbg(&pdev->dev, "of_clk_get() start.\n");
    {
        this->clk = of_clk_get(pdev->dev.of_node, 0);
        if (IS_ERR_OR_NULL(this->clk)) {
            dev_err(&pdev->dev, "clk_get failed for fclk0.\n");
            retval = PTR_ERR(this->clk);
            this->clk = NULL;
            goto failed;
        }
    }    
    dev_dbg(&pdev->dev, "of_clk_get() done.\n");

    /*
     * get device name
     */
    dev_dbg(&pdev->dev, "get device name start.\n");
    {
        device_name = of_get_property(pdev->dev.of_node, "name", NULL);
        
        if (IS_ERR_OR_NULL(device_name)) {
            device_name = dev_name(&pdev->dev);
        }
    }
    dev_dbg(&pdev->dev, "get device name done.\n");

    /*
     * create device
     */
    dev_dbg(&pdev->dev, "device_create start.\n");
    {
        this->device = device_create(fclkcfg_sys_class,
                                     NULL,
                                     this->device_number,
                                     (void *)this,
                                     device_name);
        if (IS_ERR_OR_NULL(this->device)) {
            dev_err(&pdev->dev, "device create falied.\n");
            this->device = NULL;
            goto failed;
        }
    }
    dev_dbg(&pdev->dev, "device_create done\n");

    dev_set_drvdata(&pdev->dev, this);

    dev_info(&pdev->dev, "driver installed.\n");
    dev_info(&pdev->dev, "device name : %s\n" , device_name);
    dev_info(&pdev->dev, "clock  name : %s\n" , __clk_get_name(this->clk));
    dev_info(&pdev->dev, "clock  rate : %lu\n", clk_get_rate(this->clk));
    return 0;

 failed:
    if (this != NULL) {
        if (this->clk          ) {
            clk_put(this->clk);
            this->clk = NULL;
        }
        if (this->device       ){
            device_destroy(fclkcfg_sys_class, this->device_number);
            this->device = NULL;
        }
        if (this->device_number){
            fclkcfg_device_minor_number_free(MINOR(this->device_number));
            this->device_number = 0;
        }
        kfree(this);
    }
    dev_info(&pdev->dev, "driver install failed.\n");
    return retval;
}

/**
 * fclkcfg_platform_driver_remove() -  Remove call for the device.
 *
 * @pdev:	handle to the platform device structure.
 * Returns 0 or error status.
 *
 * Unregister the device after releasing the resources.
 */
static int fclkcfg_platform_driver_remove(struct platform_device *pdev)
{
    struct fclk_driver_data* this = dev_get_drvdata(&pdev->dev);

    if (!this)
        return -ENODEV;
    if (this->clk          ) {
        clk_put(this->clk);
        this->clk = NULL;
    }
    if (this->device       ){
        device_destroy(fclkcfg_sys_class, this->device_number);
        this->device = NULL;
    }
    if (this->device_number){
        fclkcfg_device_minor_number_free(MINOR(this->device_number));
        this->device_number = 0;
    }
    kfree(this);
    dev_set_drvdata(&pdev->dev, NULL);
    dev_info(&pdev->dev, "driver unloaded\n");
    return 0;
}

/**
 * Open Firmware Device Identifier Matching Table
 */
static struct of_device_id fclkcfg_of_match[] = {
    { .compatible = "ikwzm,fclkcfg-0.10.a", },
    { /* end of table */}
};
MODULE_DEVICE_TABLE(of, fclkcfg_of_match);

/**
 * Platform Driver Structure
 */
static struct platform_driver fclkcfg_platform_driver = {
    .probe  = fclkcfg_platform_driver_probe,
    .remove = fclkcfg_platform_driver_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name  = DRIVER_NAME,
        .of_match_table = fclkcfg_of_match,
    },
};
static bool fclkcfg_platform_driver_done = 0;

/**
 * fclk_module_exit()
 */
static void __exit fclkcfg_module_exit(void)
{
    if (fclkcfg_platform_driver_done ){platform_driver_unregister(&fclkcfg_platform_driver);}
    if (fclkcfg_sys_class     != NULL){class_destroy(fclkcfg_sys_class);}
    if (fclkcfg_device_number != 0   ){unregister_chrdev_region(fclkcfg_device_number, 0);}
}

/**
 * fclkcfg_module_init()
 */
static int __init fclkcfg_module_init(void)
{
    int retval = 0;

    fclkcfg_device_minor_number_allocator_initilize();

    retval = alloc_chrdev_region(&fclkcfg_device_number, 0, 0, DRIVER_NAME);
    if (retval != 0) {
        printk(KERN_ERR "%s: couldn't allocate device major number\n", DRIVER_NAME);
        fclkcfg_device_number = 0;
        goto failed;
    }

    fclkcfg_sys_class = class_create(THIS_MODULE, DRIVER_NAME);
    if (IS_ERR_OR_NULL(fclkcfg_sys_class)) {
        printk(KERN_ERR "%s: couldn't create sys class\n", DRIVER_NAME);
        retval = PTR_ERR(fclkcfg_sys_class);
        fclkcfg_sys_class = NULL;
        goto failed;
    }
    SET_SYS_CLASS_ATTRIBUTES(fclkcfg_sys_class);

    retval = platform_driver_register(&fclkcfg_platform_driver);
    if (retval) {
        printk(KERN_ERR "%s: couldn't register platform driver\n", DRIVER_NAME);
    } else {
        fclkcfg_platform_driver_done = 1;
    }
    return 0;

 failed:
    fclkcfg_module_exit();
    return retval;
}

module_init(fclkcfg_module_init);
module_exit(fclkcfg_module_exit);

MODULE_AUTHOR("ikwzm");
MODULE_DESCRIPTION("FPGA Clock Configuration Driver");
MODULE_LICENSE("Dual BSD/GPL");
