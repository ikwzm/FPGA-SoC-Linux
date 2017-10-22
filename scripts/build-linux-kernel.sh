#!/bin/bash

CURRENT_DIR=`pwd`
LINUX_BUILD_DIR=linux-4.12.14-armv7-fpga

### Download Linux Kernel Source
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git $LINUX_BUILD_DIR
cd $LINUX_BUILD_DIR
git checkout -b linux-4.12.14-armv7-fpga refs/tags/v4.12.14

### Patch for armv7-fpga
patch -p0 < ../files/linux-4.12.14-armv7-fpga.diff
git add --update
git add arch/arm/configs/armv7_fpga_defconfig
git add arch/arm/boot/dts/zynq-pynqz1.dts
git commit -m "patch for armv7-fpga"

### Patch for usb chipidea driver
patch -p0 < ../files/linux-4.12.14-armv7-fpga-patch-usb-chipidea.diff
git add --update
git commit -m "patch for usb chipidea driver for issue #3"

### Create tag
git tag -a v4.12.14-armv7-fpga -m "relase v4.12.14-armv7-fpga"

### Setup for Build 
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
make armv7_fpga_defconfig

### Build Linux Kernel and device tree
export DTC_FLAGS=--symbols
make deb-pkg
make zynq-zybo.dtb
make zynq-pynqz1.dtb
make socfpga_cyclone5_de0_sockit.dtb
 
### Copy zImage and devicetree to tareget/zybo-zynq/boot/
cp arch/arm/boot/zImage            ../target/zynq-zybo/boot/zImage-4.12.14-armv7-fpga
cp arch/arm/boot/dts/zynq-zybo.dtb ../target/zynq-zybo/boot/devicetree-4.12.14-zynq-zybo.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/zynq-zybo/boot/devicetree-4.12.14-zynq-zybo.dts arch/arm/boot/dts/zynq-zybo.dtb

### Copy zImage and devicetree to tareget/zybo-pynqz1/boot/
cp arch/arm/boot/zImage              ../target/zynq-pynqz1/boot/zImage-4.12.14-armv7-fpga
cp arch/arm/boot/dts/zynq-pynqz1.dtb ../target/zynq-pynqz1/boot/devicetree-4.12.14-zynq-pynqz1.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/zynq-pynqz1/boot/devicetree-4.12.14-zynq-pynqz1.dts arch/arm/boot/dts/zynq-pynqz1.dtb

### Copy zImage and devicetree to tareget/de0-nano-soc/boot/
cp arch/arm/boot/zImage                              ../target/de0-nano-soc/boot/zImage-4.12.14-armv7-fpga
cp arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb ../target/de0-nano-soc/boot/devicetree-4.12.14-socfpga.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/de0-nano-soc/boot/devicetree-4.12.14-socfpga.dts arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb

cd ..
