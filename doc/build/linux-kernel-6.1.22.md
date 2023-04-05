### Build Linux Kernel

There are two ways

1. run scripts/build-linux-kernel-6.1.22.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download Linux Kernel Source

##### Clone from linux-stable.git

```console
shell$ git clone --depth 1 -b v6.1.22 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux-6.1.22-armv7-fpga
```

##### Make Build Branch

```console
shell$ cd linux-6.1.22-armv7-fpga
shell$ git checkout -b linux-6.1.22-armv7-fpga refs/tags/v6.1.22
```

#### Patch to Linux Kernel

##### Patch for armv7-fpga

```console
shell$ patch -p1 < ../files/linux-6.1.22-armv7-fpga.diff
shell$ git add --update
shell$ git add arch/arm/configs/armv7_fpga_defconfig
shell$ git add arch/arm/boot/dts/zynq-pynqz1.dts
shell$ git commit -m "patch for armv7-fpga"
```

##### Patch for usb chipidea driver

```console
shell$ patch -p1 < ../files/linux-6.1.22-armv7-fpga-patch-usb-chipidea.diff
shell$ git add --update
shell$ git commit -m "patch for usb chipidea driver for issue #3"
```

##### Patch for build debian package script

```console
shell$ patch -p1 < ../files/linux-6.1.22-armv7-fpga-patch-builddeb.diff
shell$ git add --update
shell$ git commit -m "patch for scripts/package/builddeb to add tools/include and postinst script to header package"
```

##### Create tag and .version

```console
shell$ git tag -a v6.1.22-armv7-fpga-3 -m "release v6.1.22-armv7-fpga-3"
shell$ echo 3 > .version
```

### Build

#### Setup for Build 

````console
shell$ cd linux-6.1.22-armv7-fpga
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make armv7_fpga_defconfig
````

#### Build Linux Kernel and device tree

````console
shell$ export DTC_FLAGS=--symbols
shell$ make deb-pkg
shell$ make zynq-zybo.dtb
shell$ make zynq-zybo-z7.dtb
shell$ make zynq-pynqz1.dtb
shell$ make socfpga_cyclone5_de0_nano_soc.dtb
````

### Install kernel image to this repository

```console
shell$ cp arch/arm/boot/zImage ../vmlinuz-6.1.22-armv7-fpga-3
shell$ cp .config              ../files/config-6.1.22-armv7-fpga-3
```

### Install devicetree to this repository

```console
shell$ install -d ../devicetrees/6.1.22-armv7-fpga-3
shell$ cp arch/arm/boot/dts/zynq*.dtsi    ../devicetrees/6.1.22-armv7-fpga-3
shell$ cp arch/arm/boot/dts/zynq*.dts     ../devicetrees/6.1.22-armv7-fpga-3
shell$ cp arch/arm/boot/dts/zynq*.dtb     ../devicetrees/6.1.22-armv7-fpga-3
shell$ cp arch/arm/boot/dts/socfpga*.dtsi ../devicetrees/6.1.22-armv7-fpga-3
shell$ cp arch/arm/boot/dts/socfpga*.dts  ../devicetrees/6.1.22-armv7-fpga-3
shell$ cp arch/arm/boot/dts/socfpga*.dtb  ../devicetrees/6.1.22-armv7-fpga-3
```


