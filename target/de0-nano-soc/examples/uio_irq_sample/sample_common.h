#ifndef SAMPLE_COMMON_H
#define SAMPLE_COMMON_H

#include        <stdio.h>
#include        <stdint.h>
#include        <unistd.h>
#include        <fcntl.h>
#include        <string.h>
#include        <sys/types.h>

static inline uint32_t regs_read32(void* addr)
{
    volatile uint32_t* regs_addr = (uint32_t*)(addr);
    return *regs_addr;
}

static inline uint16_t regs_read16(void* addr)
{
    volatile uint16_t* regs_addr = (uint16_t*)(addr);
    return *regs_addr;
}

static inline uint8_t  regs_read8(void* addr)
{
    volatile uint8_t*  regs_addr = (uint8_t* )(addr);
    return *regs_addr;
}

static inline void regs_write32(void* addr, uint32_t data)
{
    volatile uint32_t* regs_addr = (uint32_t*)(addr);
    *regs_addr = data;
}

static inline void regs_write16(void* addr, uint16_t data)
{
    volatile uint16_t* regs_addr = (uint16_t*)(addr);
    *regs_addr = data;
}

static inline void regs_write8(void* addr, uint8_t data)
{
    volatile uint8_t*  regs_addr = (uint8_t* )(addr);
    *regs_addr = data;
}

#define  PUMP_OUTLET_ADDR_REGS (0x0000)
#define  PUMP_OUTLET_RESV_REGS (0x0004)
#define  PUMP_OUTLET_SIZE_REGS (0x0008)
#define  PUMP_OUTLET_MODE_REGS (0x000C)
#define  PUMP_OUTLET_STAT_REGS (0x000E)
#define  PUMP_OUTLET_CTRL_REGS (0x000F)

#define  PUMP_INTAKE_ADDR_REGS (0x0010)
#define  PUMP_INTAKE_RESV_REGS (0x0014)
#define  PUMP_INTAKE_SIZE_REGS (0x0018)
#define  PUMP_INTAKE_MODE_REGS (0x001C)
#define  PUMP_INTAKE_STAT_REGS (0x001E)
#define  PUMP_INTAKE_CTRL_REGS (0x001F)

#define  PUMP_MODE_IRQ_ENABLE  (0x03 <<  0)
#define  PUMP_MODE_AXI_CACHE   (0x0F <<  4)
#define  PUMP_MODE_AXI_USER    (0x01 <<  8)
#define  PUMP_MODE_AXI_SPEC    (1    << 14)
#define  PUMP_MODE_AXI_SAFE    (1    << 15)
#define  PUMP_MODE_AXI_MODE    (PUMP_MODE_AXI_USER | PUMP_MODE_AXI_CACHE)

#define  PUMP_CTRL_RESET       (0x80)
#define  PUMP_CTRL_PAUSE       (0x40)
#define  PUMP_CTRL_STOP        (0x20)
#define  PUMP_CTRL_START       (0x10)
#define  PUMP_CTRL_IRQ_ENABLE  (0x04)
#define  PUMP_CTRL_FIRST       (0x02)
#define  PUMP_CTRL_LAST        (0x01)

#define  ALTERA_SOC_ACP_OFFSET (0x80000000)

static inline void pump_intake_setup(void* regs, unsigned long buf_addr, unsigned int xfer_size)
{
    regs_write32(regs + PUMP_INTAKE_ADDR_REGS, buf_addr + ALTERA_SOC_ACP_OFFSET);
    regs_write32(regs + PUMP_INTAKE_RESV_REGS, 0x00000000);
    regs_write32(regs + PUMP_INTAKE_SIZE_REGS, xfer_size);
    regs_write32(regs + PUMP_INTAKE_MODE_REGS, (PUMP_MODE_AXI_MODE));
}

static inline void pump_outlet_setup(void* regs, unsigned long buf_addr, unsigned int xfer_size)
{
    regs_write32(regs + PUMP_OUTLET_ADDR_REGS, buf_addr + ALTERA_SOC_ACP_OFFSET);
    regs_write32(regs + PUMP_OUTLET_RESV_REGS, 0x00000000);
    regs_write32(regs + PUMP_OUTLET_SIZE_REGS, xfer_size);
    regs_write32(regs + PUMP_OUTLET_MODE_REGS, (PUMP_MODE_AXI_MODE | PUMP_MODE_IRQ_ENABLE));
}

static inline void pump_intake_start(void* regs)
{
    regs_write8(regs + PUMP_INTAKE_CTRL_REGS, (PUMP_CTRL_START | PUMP_CTRL_FIRST | PUMP_CTRL_LAST));
}

static inline void pump_outlet_start(void* regs)
{
    regs_write8(regs + PUMP_OUTLET_CTRL_REGS, (PUMP_CTRL_START | PUMP_CTRL_FIRST | PUMP_CTRL_LAST | PUMP_CTRL_IRQ_ENABLE));
}

static inline void pump_intake_clear_status(void* regs)
{
    regs_write8(regs + PUMP_INTAKE_STAT_REGS, 0x00);
}

static inline void pump_outlet_clear_status(void* regs)
{
    regs_write8(regs + PUMP_OUTLET_STAT_REGS, 0x00);
}

static inline void pump_setup(void* regs, unsigned long src_addr, unsigned long dst_addr, unsigned int xfer_size)
{
    pump_outlet_setup(regs, dst_addr, xfer_size);
    pump_intake_setup(regs, src_addr, xfer_size);
}

static inline void pump_start(void* regs)
{
    pump_outlet_start(regs);
    pump_intake_start(regs);
}

static inline void pump_clear_status(void* regs)
{
    pump_outlet_clear_status(regs);
    pump_intake_clear_status(regs);
}

struct udmabuf {
    char           name[128];
    int            file;
    unsigned char* buf;
    unsigned int   buf_size;
    unsigned long  phys_addr;
    unsigned long  debug_vma;
    unsigned long  sync_mode;
};

int udmabuf_open(struct udmabuf* udmabuf, const char* name)
{
    char           file_name[1024];
    int            fd;
    unsigned char  attr[1024];

    strcpy(udmabuf->name, name);
    udmabuf->file = -1;

    sprintf(file_name, "/sys/class/udmabuf/%s/phys_addr", name);
    if ((fd  = open(file_name, O_RDONLY)) == -1) {
        printf("Can not open %s\n", file_name);
        return (-1);
    }
    read(fd, (void*)attr, 1024);
    sscanf(attr, "%x", &udmabuf->phys_addr);
    close(fd);

    sprintf(file_name, "/sys/class/udmabuf/%s/size", name);
    if ((fd  = open(file_name, O_RDONLY)) == -1) {
        printf("Can not open %s\n", file_name);
        return (-1);
    }
    read(fd, (void*)attr, 1024);
    sscanf(attr, "%d", &udmabuf->buf_size);
    close(fd);

    sprintf(file_name, "/dev/%s", name);
    if ((udmabuf->file = open(file_name, O_RDWR)) == -1) {
        printf("Can not open %s\n", file_name);
        return (-1);
    }

    udmabuf->buf = mmap(NULL, udmabuf->buf_size, PROT_READ|PROT_WRITE, MAP_SHARED, udmabuf->file, 0);
    udmabuf->debug_vma = 0;
    udmabuf->sync_mode = 1;

    return 0;
}

int udmabuf_close(struct udmabuf* udmabuf)
{
    if (udmabuf->file < 0) 
        return -1;

    close(udmabuf->file);
    udmabuf->file = -1;
    return 0;
}

void print_diff_time(struct timeval start_time, struct timeval end_time)
{
    struct timeval diff_time;
    if (end_time.tv_usec < start_time.tv_usec) {
        diff_time.tv_sec  = end_time.tv_sec  - start_time.tv_sec  - 1;
        diff_time.tv_usec = end_time.tv_usec - start_time.tv_usec + 1000*1000;
    } else {
        diff_time.tv_sec  = end_time.tv_sec  - start_time.tv_sec ;
        diff_time.tv_usec = end_time.tv_usec - start_time.tv_usec;
    }
    printf("time = %ld.%06ld sec\n", diff_time.tv_sec, diff_time.tv_usec);
}

#endif
