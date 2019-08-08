### Dual Boot (ZYBO and DE0-Nano-SoC)

It corresponds to boot of both ZYBO and DE0-Nano-SoC in one SD-Card.

#### Downlowd from github

```console
shell$ git clone --depth=1 --branch v1.0.1 git://github.com/ikwzm/FPGA-SoC-Linux
shell$ cd FPGA-SoC-Linux
shell$ git lfs pull
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
cp ../zynq-zybo/boot/vmlinuz-4.19.57-armv7-fpga boot/vmlinuz-4.19.57-armv7-fpga
cp ../zynq-zybo/boot/boot.bin boot/boot.bin
cp ../zynq-zybo/boot/design_1_wrapper.bit boot/design_1_wrapper.bit
cp ../zynq-zybo/boot/devicetree-4.19.57-zynq-zybo.dtb boot/devicetree-4.19.57-zynq-zybo.dtb
cp ../zynq-zybo/boot/devicetree-4.19.57-zynq-zybo.dts boot/devicetree-4.19.57-zynq-zybo.dts
cp ../zynq-zybo/boot/u-boot.img boot/u-boot.img
cp ../de0-nano-soc/boot/devicetree-4.19.57-socfpga.dtb boot/devicetree-4.19.57-socfpga.dtb
cp ../de0-nano-soc/boot/devicetree-4.19.57-socfpga.dts boot/devicetree-4.19.57-socfpga.dts
cp ../de0-nano-soc/boot/DE0_NANO_SOC.rbf boot/DE0_NANO_SOC.rbf
cp ../de0-nano-soc/u-boot/u-boot-spl.sfp u-boot/u-boot-spl.sfp
cp ../de0-nano-soc/u-boot/u-boot.img u-boot/u-boot.img
```

#### File Description

 * tareget/zynq-zybo-de0-nano-soc/
   + boot/
     - boot.bin                                                    : Stage 1 Boot Loader      (for ZYBO U-boot-spl)
     - u-boot.img                                                  : Stage 2 Boot Loader      (for ZYBO U-boot image)
     - uEnv.txt                                                    : U-Boot environment variables for set kernel version
     - boot.script                                                 : U-Boot boot script       (source)
     - boot.scr                                                    : U-Boot boot script       (binary)
     - design_1_wrapper.bit                                        : FPGA configuration file  (for ZYBO)
     - DE0_NANO_SOC.rbf                                            : FPGA configuration file  (for DE0-Nano-SoC)
     - vmlinuz-4.14.21-armv7-fpga                                  : Linux Kernel Image
     - devicetree-4.14.21-zynq-zybo.dtb                            : Linux Device Tree Blob   (for ZYBO)
     - devicetree-4.14.21-zynq-zybo.dts                            : Linux Device Tree Source (for ZYBO)
     - devicetree-4.14.21-socfpga.dtb                              : Linux Device Tree Blob   (for DE0-Nano-SoC)
     - devicetree-4.14.21-socfpga.dts                              : Linux Device Tree Source (for DE0-Nano-SoC)
   + u-boot/
     - u-boot-spl.sfp                                              : Stage 1 Boot Loader      (for DE0-Nano-SoC U-boot-spl)
     - u-boot.img                                                  : Stage 2 Boot Loader      (for DE0-Nano-SoC U-boot image)
 * debian9-rootfs-vanilla.tgz                                      : Debian9 Root File System (use Git LFS)
 * linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb   : Linux Image Package      (use Git LFS)
 * linux-headers-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb : Linux Headers Package    (use Git LFS)
 * dtbocfg-ctrl_0.0.5-1_all.deb                                    : dtbocfg Control Pakcage  (use Git LFS)
 * dtbocfg-4.19.57-armv7-fpga_0.0.8-1_armhf.deb                    : dtbocfg Kernel Module    (use Git LFS)
 * fclkcfg-4.19.57-armv7-fpga_1.2.0-1_armhf.deb                    : fclkcfg Kernel Module    (use Git LFS)
 * udmabuf-4.19.57-armv7-fpga_1.4.2-1_armhf.deb                    : udmabuf Kernel Module    (use Git LFS)
 * zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb                      : zptty   Kernel Module    (use Git LFS)

#### Format SD-Card

[./doc/install/format-disk-de0-nano-soc.md](format-disk-de0-nano-soc.md)

#### Write to SD-Card

````console
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/zynq-zybo-de0-nano-soc/boot/*                            /mnt/usb1
shell# dd if=target/zynq-zybo-de0-nano-soc/u-boot/u-boot-spl.sfp of=/dev/sdc3 bs=64k seek=0
shell# dd if=target/zynq-zybo-de0-nano-soc/u-boot/u-boot.img     of=/dev/sdc3 bs=64k seek=4
shell# tar xfz debian9-rootfs-vanilla.tgz -C                              /mnt/usb2
shell# mkdir                                                              /mnt/usb2/home/fpga/debian
shell# cp linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb   /mnt/usb2/home/fpga/debian
shell# cp linux-headers-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-ctrl_0.0.5-1_all.deb                                    /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-4.19.57-armv7-fpga_0.0.8-1_armhf.deb                    /mnt/usb2/home/fpga/debian
shell# cp fclkcfg-4.19.57-armv7-fpga_1.2.0-1_armhf.deb                    /mnt/usb2/home/fpga/debian
shell# cp udmabuf-4.19.57-armv7-fpga_1.4.2-1_armhf.deb                    /mnt/usb2/home/fpga/debian
shell# cp zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb                      /mnt/usb2/home/fpga/debian
shell# umount mnt/usb1
shell# umount mnt/usb2
````

### Install Device Drivers and Services

[./doc/install/device-drivers.md](device-drivers.md)

