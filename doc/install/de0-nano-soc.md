### DE0-Nano-SoC

#### Downlowd from github

```console
shell$ git clone git://github.com/ikwzm/FPGA-SoC-Linux
shell$ cd FPGA-SoC-Linux
shell$ git checkout v0.7.2
shell$ git lfs pull
```

#### File Description

 * target/de0-nano-soc/
   + boot/
     - DE0_NANO_SOC.rbf                                            : FPGA configuration file  (Raw Binary Format)
     - uEnv.txt                                                    : U-Boot environment variables for linux boot
     - zImage-4.14.21-armv7-fpga                                   : Linux Kernel Image       (use Git LFS)
     - devicetree-4.14.21-socfpga.dtb                              : Linux Device Tree Blob   
     - devicetree-4.14.21-socfpga.dts                              : Linux Device Tree Source
   + u-boot/
     - u-boot-spl.sfp                                              : Stage 1 Boot Loader(U-boot-spl)
     - u-boot.img                                                  : Stage 2 Boot Loader(U-boot)
   + examples/                                                     : Example Programs
 * debian9-rootfs-vanilla.tgz                                      : Debian9 Root File System (use Git LFS)
 * linux-image-4.14.21-armv7-fpga_4.14.21-armv7-fpga-2_armhf.deb   : Linux Image Package      (use Git LFS)
 * linux-headers-4.14.21-armv7-fpga_4.14.21-armv7-fpga-2_armhf.deb : Linux Headers Package    (use Git LFS)
 * fpga-soc-linux-drivers-4.14.21-armv7-fpga_0.1.2-1_armhf.deb     : Device Drivers Package   (use Git LFS)
 * fpga-soc-linux-services_0.0.9-1_armhf.deb                       : Device Services Package  (use Git LFS)

#### Format SD-Card

````console
shell# fdisk /dev/sdc
   :
   :
   :
shell# mkfs-vfat /dev/sdc1
shell# mkfs.ext3 /dev/sdc2
````

#### Write to SD-Card

````console
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/de0-nano-soc/boot/* /mnt/usb1
shell# dd if=target/de0-nano-soc/u-boot/u-boot-spl.sfp of=/dev/sdc3 bs=64k seek=0
shell# dd if=target/de0-nano-soc/u-boot/u-boot.img     of=/dev/sdc3 bs=64k seek=4
shell# tar xfz debian9-rootfs-vanilla.tgz -C                              /mnt/usb2
shell# mkdir                                                              /mnt/usb2/home/fpga/debian
shell# cp linux-image-4.14.21-armv7-fpga_4.14.21-armv7-fpga-2_armhf.deb   /mnt/usb2/home/fpga/debian
shell# cp linux-headers-4.14.21-armv7-fpga_4.14.21-armv7-fpga-2_armhf.deb /mnt/usb2/home/fpga/debian
shell# cp fpga-soc-linux-drivers-4.14.21-armv7-fpga_0.1.2-1_armhf.deb     /mnt/usb2/home/fpga/debian
shell# cp fpga-soc-linux-services_0.0.9-1_armhf.deb                       /mnt/usb2/home/fpga/debian
shell$ cp -r target/de0-nano-soc/examples                                 /mnt/usb2/home/fpga
shell# umount mnt/usb1
shell# umount mnt/usb2
````

### Install Device Drivers and Services

[./doc/install/device-drivers.md](device-drivers.md)

