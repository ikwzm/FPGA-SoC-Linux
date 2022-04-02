### ZYBO

#### Downlowd from github

**Note: Downloading the entire repository takes time, so download the source code from https://github.com/ikwzm/FPGA-SoC-Linux/releases.**

```console
shell$ wget https://github.com/ikwzm/FPGA-SoC-Linux/archive/refs/tags/v2.0.1.tar.gz
shell$ tar xfz v2.0.1.tar.gz
shell$ cd FPGA-SoC-Linux-v2.0.1
```

#### File Description

 * tareget/zynq-zybo/
   + boot/
     - boot.bin                                                      : Stage 1 Boot Loader(U-boot-spl)
     - design_1_wrapper.bit                                          : FPGA configuration file (Xilinx Bitstream Format)
     - u-boot.img                                                    : Stage 2 Boot Loader(U-boot)
     - uEnv.txt                                                      : U-Boot environment variables for linux boot
     - vmlinuz-5.10.69-armv7-fpga                                    : Linux Kernel Image       (use Git LFS)
     - devicetree-5.10.69-zynq-zybo.dtb                              : Linux Device Tree Blob   
     - devicetree-5.10.69-zynq-zybo.dts                              : Linux Device Tree Source
   + examples/                                                       : Example Programs
 * debian10-rootfs-vanilla.tgz                                       : Debian10 Root File System (use Git LFS)
 * linux-image-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb     : Linux Image Package      (use Git LFS)
 * linux-headers-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb   : Linux Headers Package    (use Git LFS)
 * dtbocfg-ctrl_0.0.5-1_all.deb                                      : dtbocfg Control Pakcage  (use Git LFS)
 * dtbocfg-5.10.69-armv7-fpga_0.0.9-1_armhf.deb                      : dtbocfg Kernel Module    (use Git LFS)
 * fclkcfg-5.10.69-armv7-fpga_1.7.2-1_armhf.deb                      : fclkcfg Kernel Module    (use Git LFS)
 * u-dma-buf-5.10.69-armv7-fpga_3.2.4-0_armhf.deb                    : u-dma-buf Kernel Module  (use Git LFS)
 * zptty-5.10.69-armv7-fpga_1.0.0-1_armhf.deb                        : zptty   Kernel Module    (use Git LFS)
 * zynq-afi-5.10.69-armv7-fpga_0.0.1-0_armhf.deb                     : Zynq AFI Kernel Module   (use Git LFS)

#### Format SD-Card

[./doc/install/format-disk-zynq.md](format-disk-zynq.md)

#### Write to SD-Card

````console
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/zynq-zybo/boot/*                                           /mnt/usb1
shell# tar xfz debian11-rootfs-vanilla.tgz -C                               /mnt/usb2
shell# mkdir                                                                /mnt/usb2/home/fpga/debian
shell# cp linux-image-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb     /mnt/usb2/home/fpga/debian
shell# cp linux-headers-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb   /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-ctrl_0.0.5-1_all.deb                                      /mnt/usb2/home/fpga/debian
shell$ cp dtbocfg-5.10.69-armv7-fpga_0.0.9-1_armhf.deb                      /mnt/usb2/home/fpga/debian
shell# cp fclkcfg-5.10.69-armv7-fpga_1.7.2-1_armhf.deb                      /mnt/usb2/home/fpga/debian
shell# cp u-dma-buf-5.10.69-armv7-fpga_3.2.4-0_armhf.deb                    /mnt/usb2/home/fpga/debian
shell# cp zptty-5.10.69-armv7-fpga_1.0.0-1_armhf.deb                        /mnt/usb2/home/fpga/debian
shell# cp zynq-afi-5.10.69-armv7-fpga_0.0.1-0_armhf.deb                     /mnt/usb2/home/fpga/debian
shell# cp -r target/zynq-zybo/examples                                      /mnt/usb2/home/fpga
shell# umount /mnt/usb1
shell# umount /mnt/usb2
````

### Install Device Drivers and Services

[./doc/install/device-drivers.md](device-drivers.md)

