#!/bin/bash

CURRENT_DIR=`pwd`
LINUX_BUILD_DIR=linux-4.4.7-armv7-fpga

### Download Linux Kernel Source
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git $LINUX_BUILD_DIR
cd $LINUX_BUILD_DIR
git checkout -b linux-4.4.7-armv7-fpga refs/tags/v4.4.7

### Patch for armv7-fpga
patch -p0 < ../files/linux-4.4.7-armv7-fpga.diff
git add --update
git add arch/arm/configs/armv7_fpga_defconfig
git commit -m "patch for armv7-fpga"
git tag -a v4.4.7-armv7-fpga -m "relase v4.4.7-armv7-fpga"

### Setup for Build 
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make armv7_fpga_defconfig

### Build Linux Kernel and device tree
make zImage
make zynq-zybo.dtb
make socfpga_cyclone5_de0_sockit.dtb
 
### Copy zImage and devicetree to zybo-zynq/boot/
cp arch/arm/boot/zImage            ../zynq-zybo/boot/vmlinuz-4.4.7-armv7-fpga
cp arch/arm/boot/dts/zynq-zybo.dtb ../zynq-zybo/boot/zynq-zybo.dtb

### Copy zImage and devicetree to de0-nano-soc/boot/
cp arch/arm/boot/zImage                              ../de0-nano-soc/boot/vmlinuz-4.4.7-armv7-fpga
cp arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb ../de0-nano-soc/boot/socfpga.dtb

cd ..
