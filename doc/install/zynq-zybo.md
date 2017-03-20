### ZYBO

#### Downlowd from github

```
shell$ git clone git://github.com/ikwzm/FPGA-SoC-Linux
shell$ cd FPGA-SoC-Linux
shell$ git lfs pull origin master
```

#### File Description

 * tareget/zynq-zybo/
   + boot/
     - boot.bin                                                  : Stage 1 Boot Loader(U-boot-spl)
     - design_1_wrapper.bit                                      : FPGA configuration file (Xilinx Bitstream Format)
     - u-boot.img                                                : Stage 2 Boot Loader(U-boot)
     - uEnv.txt                                                  : U-Boot environment variables for linux boot
     - zImage-4.8.17-armv7-fpga                                  : Linux Kernel Image       
     - devicetree-4.8.17-zynq-zybo.dtb                           : Linux Device Tree Blob   
     - devicetree-4.8.17-zynq-zybo.dts                           : Linux Device Tree Source
   + examples-001.tgz                                            : Examples Programs        (use Git LFS)
 * debian8-rootfs-vanilla.tgz                                    : Debian8 Root File System (use Git LFS)
 * linux-image-4.8.17-armv7-fpga_4.8.17-armv7-fpga-1_armhf.deb   : Linux Image Package      (use Git LFS)
 * linux-headers-4.8.17-armv7-fpga_4.8.17-armv7-fpga-1_armhf.deb : Linux Headers Package    (use Git LFS)
 * fpga-soc-linux-drivers-4.8.17-armv7-fpga_0.0.5-1_armhf.deb    : Device Drivers Package   (use Git LFS)
 * fpga-soc-linux-services_0.0.5-1_armhf.deb                     : Device Services Package  (use Git LFS)

#### Format SD-Card

````
shell# fdisk /dev/sdc
   :
   :
   :
shell# mkfs-vfat /dev/sdc1
shell# mkfs.ext3 /dev/sdc2
````

#### Write to SD-Card

````
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/zynq-zybo/boot/*                                       /mnt/usb1
shell# tar xfz debian8-rootfs-vanilla.tgz -C                            /mnt/usb2
shell# cp linux-image-4.8.17-armv7-fpga_4.8.17-armv7-fpga-1_armhf.deb   /mnt/usb2/home/fpga
shell# cp linux-headers-4.8.17-armv7-fpga_4.8.17-armv7-fpga-1_armhf.deb /mnt/usb2/home/fpga
shell# cp fpga-soc-linux-drivers-4.8.17-armv7-fpga_0.0.5-1_armhf.deb    /mnt/usb2/home/fpga
shell# cp fpga-soc-linux-services_0.0.5-1_armhf.deb                     /mnt/usb2/home/fpga
shell# tar xfz target/zynq-zybo/examples-001.tgz -C                     /mnt/usb2/home/fpga
shell# umount mnt/usb1
shell# umount mnt/usb2
````

