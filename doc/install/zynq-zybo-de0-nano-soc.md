### Dual Boot (ZYBO and DE0-Nano-SoC)

It corresponds to boot of both ZYBO and DE0-Nano-SoC in one SD-Card.

#### Downlowd from github

**Note: Downloading the entire repository takes time, so download the source code from https://github.com/ikwzm/FPGA-SoC-Linux/releases.**

```console
shell$ wget https://github.com/ikwzm/FPGA-SoC-Linux/archive/refs/tags/v2.1.1.tar.gz
shell$ tar xfz v2.1.1.tar.gz
shell$ cd FPGA-SoC-Linux-v2.1.1
```
#### Build boot files

```console
shell$ cd target/zynq-zybo-de0-nano-soc/
shell$ make
mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "linux boot script" -d boot/boot.script boot/boot.scr
Image Name:   linux boot script
Created:      Fri Apr 27 08:32:40 2018
Image Type:   ARM Linux Script (uncompressed)
Data Size:    1878 Bytes = 1.83 kB = 0.00 MB
Load Address: 00000000
Entry Point:  00000000
Contents:
   Image 0: 1870 Bytes = 1.83 kB = 0.00 MB
cp ../../vmlinuz-5.10.109-armv7-fpga boot/
cp ../zynq-zybo/boot/boot.bin boot/boot.bin
cp ../zynq-zybo/boot/design_1_wrapper.bit boot/design_1_wrapper.bit
cp ../zynq-zybo/boot/devicetree-5.10.109-zynq-zybo.dtb boot/devicetree-5.10.109-zynq-zybo.dtb
cp ../zynq-zybo/boot/devicetree-5.10.109-zynq-zybo.dts boot/devicetree-5.10.109-zynq-zybo.dts
cp ../zynq-zybo/boot/u-boot.img boot/u-boot.img
cp ../de0-nano-soc/boot/devicetree-5.10.109-socfpga.dtb boot/devicetree-5.10.109-socfpga.dtb
cp ../de0-nano-soc/boot/devicetree-5.10.109-socfpga.dts boot/devicetree-5.10.109-socfpga.dts
cp ../de0-nano-soc/boot/DE0_NANO_SOC.rbf boot/DE0_NANO_SOC.rbf
cp ../de0-nano-soc/u-boot/u-boot-spl.sfp u-boot/u-boot-spl.sfp
cp ../de0-nano-soc/u-boot/u-boot.img u-boot/u-boot.img
```

#### File Description

 * tareget/zynq-zybo-de0-nano-soc/
   + boot/
     - boot.bin                                 : Stage 1 Boot Loader      (for ZYBO U-boot-spl)
     - u-boot.img                               : Stage 2 Boot Loader      (for ZYBO U-boot image)
     - uEnv.txt                                 : U-Boot environment variables for set kernel version
     - boot.script                              : U-Boot boot script       (source)
     - boot.scr                                 : U-Boot boot script       (binary)
     - design_1_wrapper.bit                     : FPGA configuration file  (for ZYBO)
     - DE0_NANO_SOC.rbf                         : FPGA configuration file  (for DE0-Nano-SoC)
     - vmlinuz-5.10.109-armv7-fpga              : Linux Kernel Image
     - devicetree-5.10.109-zynq-zybo.dtb        : Linux Device Tree Blob   (for ZYBO)
     - devicetree-5.10.109-zynq-zybo.dts        : Linux Device Tree Source (for ZYBO)
     - devicetree-5.10.109-socfpga.dtb          : Linux Device Tree Blob   (for DE0-Nano-SoC)
     - devicetree-5.10.109-socfpga.dts          : Linux Device Tree Source (for DE0-Nano-SoC)
   + u-boot/
     - u-boot-spl.sfp                           : Stage 1 Boot Loader      (for DE0-Nano-SoC U-boot-spl)
     - u-boot.img                               : Stage 2 Boot Loader      (for DE0-Nano-SoC U-boot image)
 * debian11-rootfs-vanilla.tgz.files/           : Debian11 Root File System
   + x00 .. x07                                 : (splited files)
 * linux-image-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb   : Linux Image Package
 * linux-headers-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb : Linux Headers Package
 * dtbocfg-ctrl_0.0.5-1_all.deb                                      : dtbocfg Control Pakcage
 * dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb                     : dtbocfg Kernel Module
 * fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb                     : fclkcfg Kernel Module
 * u-dma-buf-5.10.109-armv7-fpga_3.2.5-0_armhf.deb                   : u-dma-buf Kernel Module
 * zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb                       : zptty   Kernel Module
 * zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb                    : Zynq AFI Kernel Module

#### Format SD-Card

[./doc/install/format-disk-de0-nano-soc.md](format-disk-de0-nano-soc.md)

#### Write to SD-Card

````console
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/zynq-zybo-de0-nano-soc/boot/* /mnt/usb1
shell# dd if=target/zynq-zybo-de0-nano-soc/u-boot/u-boot-spl.sfp of=/dev/sdc3 bs=64k seek=0
shell# dd if=target/zynq-zybo-de0-nano-soc/u-boot/u-boot.img     of=/dev/sdc3 bs=64k seek=4
shell# cat debian11-rootfs-vanilla.tgz.files/* | tar xfz - -C               /mnt/usb2
shell# mkdir                                                                /mnt/usb2/home/fpga/debian
shell# cp linux-image-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb   /mnt/usb2/home/fpga/debian
shell# cp linux-headers-5.10.109-armv7-fpga_5.10.109-armv7-fpga-1_armhf.deb /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-ctrl_0.0.5-1_all.deb                                      /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb                     /mnt/usb2/home/fpga/debian
shell# cp fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb                     /mnt/usb2/home/fpga/debian
shell# cp u-dma-buf-5.10.109-armv7-fpga_3.2.5-0_armhf.deb                   /mnt/usb2/home/fpga/debian
shell# cp zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb                       /mnt/usb2/home/fpga/debian
shell# cp zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb                    /mnt/usb2/home/fpga/debian
shell# cp zptty-5.10.109-armv7-fpga_1.0.0-1_armhf.deb                       /mnt/usb2/home/fpga/debian
shell# umount mnt/usb1
shell# umount mnt/usb2
````

### Install Device Drivers and Services

[./doc/install/device-drivers.md](device-drivers.md)

