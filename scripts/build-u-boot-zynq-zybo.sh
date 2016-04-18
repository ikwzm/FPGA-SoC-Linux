#!/bin/bash

UBOOT_BUILD_DIR=u-boot-zynq-zybo

### Download Linux Kernel Source
git clone git://git.denx.de/u-boot.git $UBOOT_BUILD_DIR
cd $UBOOT_BUILD_DIR

#### CHeckout v2016.03
git checkout -b u-boot-2016.03-zynq-zybo refs/tags/v2016.03

### Patch for zynq-zybo

patch -p0 < ../files/u-boot-2016.03-zynq-zybo.diff
git add --update
git commit -m "patch for zynq-zybo"
git tag -a v2016.03-zynq-zybo -m "relase v2016.03-zynq-zybo"

### Setup for Build 

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make zynq_zybo_defconfig

### Build u-boot

make

### Copy zImage and devicetree to zybo-zynq/boot/

cp spl/boot.bin  ../zynq-zybo/boot/
cp u-boot.img    ../zynq-zybo/boot/

cd ..
