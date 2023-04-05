#!/bin/bash

CURRENT_DIR=`pwd`
KERNEL_VERSION=6.1.22
LOCAL_VERSION=armv7-fpga
BUILD_VERSION=3
KERNEL_RELEASE=$KERNEL_VERSION-$LOCAL_VERSION
LINUX_BUILD_DIR=linux-$KERNEL_RELEASE

echo "KERNEL_RELEASE  =" $KERNEL_RELEASE
echo "BUILD_VERSION   =" $BUILD_VERSION
echo "LINUX_BUILD_DIR =" $LINUX_BUILD_DIR

## Download Linux Kernel Source

### Clone from linux-stable.git

git clone --depth 1 -b v$KERNEL_VERSION git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git $LINUX_BUILD_DIR

### Make Build Branch

cd $LINUX_BUILD_DIR
git checkout -b $KERNEL_RELEASE refs/tags/$KERNEL_VERSION

## Patch to Linux Kernel

### Patch for armv7-fpga
patch -p1 < ../files/linux-$KERNEL_VERSION-armv7-fpga.diff
git add --update
git add arch/arm/configs/armv7_fpga_defconfig
git add arch/arm/boot/dts/zynq-pynqz1.dts
git commit -m "patch for armv7-fpga"

### Patch for usb chipidea driver
patch -p1 < ../files/linux-$KERNEL_VERSION-armv7-fpga-patch-usb-chipidea.diff
git add --update
git commit -m "patch for usb chipidea driver for issue #3"

### Patch for build debian package script
patch -p1 < ../files/linux-$KERNEL_VERSION-armv7-fpga-patch-builddeb.diff
git add --update
git commit -m "patch for scripts/package/builddeb to add tools/include and arch/arm/tools and postinst script to header package"

### Create tag and .version
git tag -a $KERNEL_RELEASE-$BUILD_VERSION -m "release $KERNEL_RELEASE-$BUILD_VERSION"
echo $BUILD_VERSION > .version

## Build

### Setup for Build 
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make armv7_fpga_defconfig

### Build Linux Kernel and device tree
export DTC_FLAGS=--symbols
make deb-pkg
make zynq-zybo.dtb
make zynq-zybo-z7.dtb
make zynq-pynqz1.dtb
make socfpga_cyclone5_de0_nano_soc.dtb
 
### Install kernel image to this repository

cp arch/arm/boot/zImage ../vmlinuz-$KERNEL_RELEASE-$BUILD_VERSION
cp .config              ../files/config-$KERNEL_RELEASE-$BUILD_VERSION

### Install devicetree to this repository

install -d ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION
cp arch/arm/boot/dts/zynq*.dtsi    ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION
cp arch/arm/boot/dts/zynq*.dts     ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION
cp arch/arm/boot/dts/zynq*.dtb     ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION
cp arch/arm/boot/dts/socfpga*.dtsi ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION
cp arch/arm/boot/dts/socfpga*.dts  ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION
cp arch/arm/boot/dts/socfpga*.dtb  ../devicetrees/$KERNEL_RELEASE-$BUILD_VERSION


