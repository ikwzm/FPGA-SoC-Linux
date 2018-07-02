#!/bin/bash

CURRENT_DIR=`pwd`
LINUX_BUILD_DIR=linux-4.16.18-armv7-fpga

### Download Linux Kernel Source
git clone --depth=1 -b v4.16.18 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git $LINUX_BUILD_DIR
cd $LINUX_BUILD_DIR
git checkout -b linux-4.16.18-armv7-fpga refs/tags/v4.16.18

### Patch for armv7-fpga
patch -p1 < ../files/linux-4.16.18-armv7-fpga.diff
git add --update
git add arch/arm/configs/armv7_fpga_defconfig
git add arch/arm/boot/dts/zynq-pynqz1.dts
git add arch/arm/boot/dts/zynq-zybo-z7.dts
git commit -m "patch for armv7-fpga"

### Patch for usb chipidea driver
patch -p1 < ../files/linux-4.16.18-armv7-fpga-patch-usb-chipidea.diff
git add --update
git commit -m "patch for usb chipidea driver for issue #3"

### Patch for build debian package script

patch -p1 < ../files/linux-4.16.18-armv7-fpga-patch-builddeb.diff
git add --update
git commit -m "patch for scripts/package/builddeb to add tools/include and postinst script to header package"

### Create tag and .version
git tag -a v4.16.18-armv7-fpga -m "release v4.16.18-armv7-fpga"
echo 0 > .version

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
make socfpga_cyclone5_de0_sockit.dtb
 
### Copy zImage and devicetree to tareget/zybo-zynq/boot/
cp arch/arm/boot/zImage            ../target/zynq-zybo/boot/vmlinuz-4.16.18-armv7-fpga
cp arch/arm/boot/dts/zynq-zybo.dtb ../target/zynq-zybo/boot/devicetree-4.16.18-zynq-zybo.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/zynq-zybo/boot/devicetree-4.16.18-zynq-zybo.dts arch/arm/boot/dts/zynq-zybo.dtb

### Copy zImage and devicetree to tareget/zybo-zynq-z7/boot/
cp arch/arm/boot/zImage               ../target/zynq-zybo-z7/boot/vmlinuz-4.16.18-armv7-fpga
cp arch/arm/boot/dts/zynq-zybo-z7.dtb ../target/zynq-zybo-z7/boot/devicetree-4.16.18-zynq-zybo-z7.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/zynq-zybo-z7/boot/devicetree-4.16.18-zynq-zybo-z7.dts arch/arm/boot/dts/zynq-zybo-z7.dtb

### Copy zImage and devicetree to tareget/zybo-pynqz1/boot/
cp arch/arm/boot/zImage              ../target/zynq-pynqz1/boot/vmlinuz-4.16.18-armv7-fpga
cp arch/arm/boot/dts/zynq-pynqz1.dtb ../target/zynq-pynqz1/boot/devicetree-4.16.18-zynq-pynqz1.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/zynq-pynqz1/boot/devicetree-4.16.18-zynq-pynqz1.dts arch/arm/boot/dts/zynq-pynqz1.dtb

### Copy zImage and devicetree to tareget/de0-nano-soc/boot/
cp arch/arm/boot/zImage                              ../target/de0-nano-soc/boot/vmlinuz-4.16.18-armv7-fpga
cp arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb ../target/de0-nano-soc/boot/devicetree-4.16.18-socfpga.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/de0-nano-soc/boot/devicetree-4.16.18-socfpga.dts arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb

### Copy zImage and devicetree to tareget/de10-nano/boot/
cp arch/arm/boot/zImage                              ../target/de10-nano/boot/vmlinuz-4.16.18-armv7-fpga
cp arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb ../target/de10-nano/boot/devicetree-4.16.18-socfpga.dtb
./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/de10-nano/boot/devicetree-4.16.18-socfpga.dts arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb

cd ..
