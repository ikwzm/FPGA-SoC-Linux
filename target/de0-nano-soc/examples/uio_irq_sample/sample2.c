#include        <stdio.h>
#include        <fcntl.h>
#include        <string.h>
#include        <time.h>
#include        <poll.h>
#include        <sys/types.h>
#include        <sys/mman.h>

#include        "sample_common.h"

int uio_irq_on(int uio_fd)
{
    unsigned int  irq_on = 1;
    write(uio_fd, &irq_on, sizeof(irq_on));
}

int uio_poll_irq(int uio_fd)
{
    struct pollfd   fds[1];
    struct timespec timeout;
    sigset_t        sigmask;
    int             poll_result;
    unsigned int    irq_count;
    fds[0].fd       = uio_fd;
    fds[0].events   = POLLIN;
    timeout.tv_sec  = 100;
    timeout.tv_nsec = 0;
    poll_result = ppoll(fds, 1, &timeout, &sigmask);
    if ((poll_result > 0) && (fds[0].revents & POLLIN)) {
        read(uio_fd, &irq_count,  sizeof(irq_count));
    }
    return poll_result;
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
        int poll_return;
        int i;

        for(i = 0; i < check_size ; i++) {
            ((unsigned char*)(intake_buf.buf))[i] = (i & 0xFF);
            ((unsigned char*)(outlet_buf.buf))[i] = 0;
        }
    
        gettimeofday(&start_time, NULL);
        pump_setup(regs, intake_buf.phys_addr, outlet_buf.phys_addr, check_size);
        uio_irq_on(uio_fd);
        pump_start(regs);
        poll_return = uio_poll_irq(uio_fd);
        if (poll_return == -1) {
            printf("uio_poll_irq error\n");
            break;
        }
        if (poll_return == 0) {
            printf("uio_poll_irq timeout\n");
            break;
        }
        pump_clear_status(regs);
        gettimeofday(&end_time  , NULL);
        print_diff_time(start_time, end_time);

        error_count = 0;
        for(i = 0; i < check_size ; i++) {
            if (((unsigned char*)(outlet_buf.buf))[i] != ((unsigned char*)(intake_buf.buf))[i])
                error_count++;
        }
        if (error_count > 0) {
            printf("check buffer error\n");
            break;
        }
    }

    pump_reset(regs);
    udmabuf_close(&outlet_buf);
    udmabuf_close(&intake_buf);
    close(uio_fd);
}

