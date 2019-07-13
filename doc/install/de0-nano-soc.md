### DE0-Nano-SoC

#### Downlowd from github

```console
shell$ git clone --depth=1 --branch v1.0.0-rc1 git://github.com/ikwzm/FPGA-SoC-Linux
shell$ cd FPGA-SoC-Linux
shell$ git lfs pull
```

#### File Description

 * target/de0-nano-soc/
   + boot/
     - DE0_NANO_SOC.rbf                                              : FPGA configuration file  (Raw Binary Format)
     - uEnv.txt                                                      : U-Boot environment variables for linux boot
     - vmlinuz-4.19.57-armv7-fpga                                    : Linux Kernel Image       (use Git LFS)
     - devicetree-4.19.57-socfpga.dtb                                : Linux Device Tree Blob   
     - devicetree-4.19.57-socfpga.dts                                : Linux Device Tree Source
   + u-boot/
     - u-boot-spl.sfp                                                : Stage 1 Boot Loader(U-boot-spl)
     - u-boot.img                                                    : Stage 2 Boot Loader(U-boot)
   + examples/                                                       : Example Programs
 * debian10-rootfs-vanilla.tgz                                       : Debian10 Root File System (use Git LFS)
 * linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb     : Linux Image Package      (use Git LFS)
 * linux-headers-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb   : Linux Headers Package    (use Git LFS)
 * dtbocfg-ctrl_0.0.5-1_all.deb                                      : dtbocfg Control Pakcage  (use Git LFS)
 * dtbocfg-4.19.57-armv7-fpga_0.0.7-1_armhf.deb                      : dtbocfg Kernel Module    (use Git LFS)
 * fclkcfg-4.19.57-armv7-fpga_1.1.0-1_armhf.deb                      : fclkcfg Kernel Module    (use Git LFS)
 * udmabuf-4.19.57-armv7-fpga_1.4.2-0_armhf.deb                      : udmabuf Kernel Module    (use Git LFS)
 * zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb                        : zptty   Kernel Module    (use Git LFS)

#### Format SD-Card

[./doc/install/format-disk-de0-nano-soc.md](format-disk-de0-nano-soc.md)

#### Write to SD-Card

````console
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/de0-nano-soc/boot/* /mnt/usb1
shell# dd if=target/de0-nano-soc/u-boot/u-boot-spl.sfp of=/dev/sdc3 bs=64k seek=0
shell# dd if=target/de0-nano-soc/u-boot/u-boot.img     of=/dev/sdc3 bs=64k seek=4
shell# tar xfz debian10-rootfs-vanilla.tgz -C                               /mnt/usb2
shell# mkdir                                                                /mnt/usb2/home/fpga/debian
shell# cp linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb     /mnt/usb2/home/fpga/debian
shell# cp linux-headers-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb   /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-ctrl_0.0.5-1_all.deb                                      /mnt/usb2/home/fpga/debian
shell# cp dtbocfg-4.19.57-armv7-fpga_0.0.7-1_armhf.deb                      /mnt/usb2/home/fpga/debian
shell# cp fclkcfg-4.19.57-armv7-fpga_1.1.0-1_armhf.deb                      /mnt/usb2/home/fpga/debian
shell# cp udmabuf-4.19.57-armv7-fpga_1.4.2-0_armhf.deb                      /mnt/usb2/home/fpga/debian
shell# cp zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb                        /mnt/usb2/home/fpga/debian
shell# cp -r target/de0-nano-soc/examples                                   /mnt/usb2/home/fpga
shell# umount mnt/usb1
shell# umount mnt/usb2
````

### Install Device Drivers and Services

[./doc/install/device-drivers.md](device-drivers.md)

