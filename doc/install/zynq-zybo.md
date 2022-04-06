### ZYBO

#### Downlowd from github

**Note: Downloading the entire repository takes time, so download the source code from https://github.com/ikwzm/FPGA-SoC-Linux/releases.**

```console
shell$ wget https://github.com/ikwzm/FPGA-SoC-Linux/archive/refs/tags/v2.1.1.tar.gz
shell$ tar xfz v2.1.1.tar.gz
shell$ cd FPGA-SoC-Linux-v2.1.1
```

#### File Description

 * tareget/zynq-zybo/
   + boot/
     - boot.bin                                                      : Stage 1 Boot Loader(U-boot-spl)
     - design_1_wrapper.bit                                          : FPGA configuration file (Xilinx Bitstream Format)
     - u-boot.img                                                    : Stage 2 Boot Loader(U-boot)
     - uEnv.txt                                                      : U-Boot environment variables for linux boot
     - devicetree-5.10.109-zynq-zybo.dtb                             : Linux Device Tree Blob   
     - devicetree-5.10.109-zynq-zybo.dts                             : Linux Device Tree Source
   + examples/                                                       : Example Programs
 * vmlinuz-5.10.109-armv7-fpga                                       : Linux Kernel Image
 * debian11-rootfs-vanilla.tgz.files/                                : Debian11 Root File System
   + x00 .. x07                                                      : (splited files)
 * linux-image-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb   : Linux Image Package
 * linux-headers-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb : Linux Headers Package
 * dtbocfg-ctrl_0.0.5-1_all.deb                                      : dtbocfg Control Pakcage
 * dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb                     : dtbocfg Kernel Module
 * fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb                     : fclkcfg Kernel Module
 * u-dma-buf-5.10.109-armv7-fpga_3.2.5-0_armhf.deb                   : u-dma-buf Kernel Module
 * zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb                       : zptty   Kernel Module
 * zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb                    : Zynq AFI Kernel Module

#### Format SD-Card

[./doc/install/format-disk-zynq.md](format-disk-zynq.md)

#### Write to SD-Card

````console
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/zynq-zybo/boot/*                                           /mnt/usb1
shell# cp vmlinuz-5.10.109-armv7-fpga                                       /mnt/usb1
shell# cat debian11-rootfs-vanilla.tgz.files/* | tar xfz - -C               /mnt/usb2
shell# mkdir                                                                /mnt/usb2/home/fpga/debian
shell# cp linux-image-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb   /mnt/usb2/home/fpga/debian
shell# cp linux-headers-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-ctrl_0.0.5-1_all.deb                                      /mnt/usb2/home/fpga/debian
shell$ cp dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb                     /mnt/usb2/home/fpga/debian
shell# cp fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb                     /mnt/usb2/home/fpga/debian
shell# cp u-dma-buf-5.10.109-armv7-fpga_3.2.5-0_armhf.deb                   /mnt/usb2/home/fpga/debian
shell# cp zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb                       /mnt/usb2/home/fpga/debian
shell# cp zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb                    /mnt/usb2/home/fpga/debian
shell# cp -r target/zynq-zybo/examples                                      /mnt/usb2/home/fpga
shell# umount /mnt/usb1
shell# umount /mnt/usb2
````

### Install Device Drivers and Services

[./doc/install/device-drivers.md](device-drivers.md)

