#include        <stdio.h>
#include        <stdlib.h>
#include        <fcntl.h>
#include        <string.h>
#include        <time.h>
#include        <sys/time.h>
#include        <poll.h>
#include        <sys/types.h>
#include        <sys/mman.h>

#include        "sample_common.h"

int uio_irq_on(int uio_fd)
{
    unsigned int  irq_on = 1;
    write(uio_fd, &irq_on, sizeof(irq_on));
}

int uio_wait_irq(int uio_fd)
{
    unsigned int  count = 0;
    return read(uio_fd, &count,  sizeof(count));
}

void main()
{
    int            uio_fd;
    void*          regs;
    struct udmabuf intake_buf;
    struct udmabuf outlet_buf;
    int            check_count = 10;
    int            check_size  = 0x1000;
    struct timeval start_time, end_time;

    if ((uio_fd = open("/dev/uio0", O_RDWR)) == -1) {
        printf("Can not open /dev/uio0\n");
        exit(1);
    }
    regs = mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, uio_fd, 0);

    if (udmabuf_open(&intake_buf, "udmabuf4") == -1)
        exit(1);
    
    if (udmabuf_open(&outlet_buf, "udmabuf5") == -1)
        exit(1);

    check_size = outlet_buf.buf_size;

    while (--check_count >= 0) {
        int error_count = 0;
        int i;

        for(i = 0; i < check_size ; i++) {
            ((unsigned char*)(intake_buf.buf))[i] = (i & 0xFF);
            ((unsigned char*)(outlet_buf.buf))[i] = 0;
        }
    
        gettimeofday(&start_time, NULL);
        pump_setup(regs, intake_buf.phys_addr, outlet_buf.phys_addr, check_size);
        uio_irq_on(uio_fd);
        pump_start(regs);
        if (uio_wait_irq(uio_fd) == -1) {
            printf("uio_wait_irq error\n");
            break;
        }
        pump_clear_status(regs);
        gettimeofday(&end_time  , NULL);
        print_diff_time(start_time, end_time);

        error_count = 0;
        for(i = 0; i < check_size ; i++) {
            if (((unsigned char*)(outlet_buf.buf))[i] != ((unsigned char*)(intake_buf.buf))[i]) {
                if (error_count < 0x10) {
                    printf("check buffer error addr=%08x, i=%02X, o=%02X\n",
                           i,
                           (((unsigned char*)(intake_buf.buf))[i]),
                           (((unsigned char*)(outlet_buf.buf))[i])
                    );
                }
                error_count++;
            }
        }
        if (error_count > 0) {
            printf("check buffer error\n");
            break;
        }
    }

    udmabuf_close(&outlet_buf);
    udmabuf_close(&intake_buf);
    close(uio_fd);
}

