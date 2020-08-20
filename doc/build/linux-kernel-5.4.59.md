### Build Linux Kernel

There are two ways

1. run scripts/build-linux-kernel-5.4.59.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download Linux Kernel Source

##### Clone from linux-stable.git

```console
shell$ git clone --depth 1 -b v5.4.59 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux-5.4.59-armv7-fpga
```

##### Checkout v5.4.59

```console
shell$ cd linux-5.4.59-armv7-fpga
shell$ git checkout -b linux-5.4.59-armv7-fpga refs/tags/v5.4.59
```

#### Patch for armv7-fpga

##### Patch for armv7-fpga

```console
shell$ patch -p1 < ../files/linux-5.4.59-armv7-fpga.diff
shell$ git add --update
shell$ git add arch/arm/configs/armv7_fpga_defconfig
shell$ git add arch/arm/boot/dts/zynq-pynqz1.dts
shell$ git commit -m "patch for armv7-fpga"
```

##### Patch for usb chipidea driver

```console
shell$ patch -p1 < ../files/linux-5.4.59-armv7-fpga-patch-usb-chipidea.diff
shell$ git add --update
shell$ git commit -m "patch for usb chipidea driver for issue #3"
```

##### Patch for build debian package script

```console
shell$ patch -p1 < ../files/linux-5.4.59-armv7-fpga-patch-builddeb.diff
shell$ git add --update
shell$ git commit -m "patch for scripts/package/builddeb to add tools/include and postinst script to header package"
```

##### Create tag and .version

```console
shell$ git tag -a v5.4.59-armv7-fpga -m "release v5.4.59-armv7-fpga"
shell$ echo 0 > .version
```

#### Setup for Build 

````console
shell$ cd linux-5.4.59-armv7-fpga
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

#### Copy zImage and devicetree to target/zybo-zynq/boot/

```console
shell$ cp arch/arm/boot/zImage            ../target/zynq-zybo/boot/vmlinuz-5.4.59-armv7-fpga
shell$ cp arch/arm/boot/dts/zynq-zybo.dtb ../target/zynq-zybo/boot/devicetree-5.4.59-zynq-zybo.dtb
shell$ ./scripts/dtc/dtc -I dtb -O dts -o ../target/zynq-zybo/boot/devicetree-5.4.59-zynq-zybo.dts arch/arm/boot/dts/zynq-zybo.dtb
```

#### Copy zImage and devicetree to tareget/zybo-zynq-z7/boot/

```console
shell$ cp arch/arm/boot/zImage               ../target/zynq-zybo-z7/boot/vmlinuz-5.4.59-armv7-fpga
shell$ cp arch/arm/boot/dts/zynq-zybo-z7.dtb ../target/zynq-zybo-z7/boot/devicetree-5.4.59-zynq-zybo-z7.dtb
shell$ ./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/zynq-zybo-z7/boot/devicetree-5.4.59-zynq-zybo-z7.dts arch/arm/boot/dts/zynq-zybo-z7.dtb
```


#### Copy zImage and devicetree to target/zybo-pynqz1/boot/

```console
shell$ cp arch/arm/boot/zImage              ../target/zynq-pynqz1/boot/vmlinuz-5.4.59-armv7-fpga
shell$ cp arch/arm/boot/dts/zynq-pynqz1.dtb ../target/zynq-pynqz1/boot/devicetree-5.4.59-zynq-pynqz1.dtb
shell$ ./scripts/dtc/dtc -I dtb -O dts -o ../target/zynq-pynqz1/boot/devicetree-5.4.59-zynq-pynqz1.dts arch/arm/boot/dts/zynq-pynqz1.dtb
```

#### Copy zImage and devicetree to target/de0-nano-soc/boot/

```console
shell$ cp arch/arm/boot/zImage                                ../target/de0-nano-soc/boot/vmlinuz-5.4.59-armv7-fpga
shell$ cp arch/arm/boot/dts/socfpga_cyclone5_de0_nano_soc.dtb ../target/de0-nano-soc/boot/devicetree-5.4.59-socfpga.dtb
shell$ ./scripts/dtc/dtc -I dtb -O dts -o ../target/de0-nano-soc/boot/devicetree-5.4.59-socfpga.dts arch/arm/boot/dts/socfpga_cyclone5_de0_nano_soc.dtb
```

#### Copy zImage and devicetree to tareget/de10-nano/boot/

```console
shell$ cp arch/arm/boot/zImage                                ../target/de10-nano/boot/vmlinuz-5.4.59-armv7-fpga
shell$ cp arch/arm/boot/dts/socfpga_cyclone5_de0_nano_soc.dtb ../target/de10-nano/boot/devicetree-5.4.59-socfpga.dtb
shell$ ./scripts/dtc/dtc -I dtb -O dts --symbols -o ../target/de10-nano/boot/devicetree-5.4.59-socfpga.dts arch/arm/boot/dts/socfpga_cyclone5_de0_nano_soc.dtb
```



