### Build U-boot for PYNQ-Z1

There are two ways

1. run scripts/build-u-boot-zynq-pynqz1.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download U-boot Source

##### Clone from git.denx.de/u-boot.git

```console
shell$ git clone git://git.denx.de/u-boot.git u-boot-zynq-pynqz1
```

##### Checkout v2016.03

```console
shell$ cd u-boot-zynq-pynqz1
shell$ git checkout -b u-boot-2016.03-zynq-pynqz1 refs/tags/v2016.03
```

#### Patch for zynq-zybo

```console
shell$ patch -p0 < ../files/u-boot-2016.03-zynq-pynqz1.diff
shell$ git add --update
shell$ git add arch/arm/dts/zynq-pynqz1.dts
shell$ git add board/xilinx/zynq/pynqz1_hw_platform/*
shell$ git add configs/zynq_pynqz1_defconfig
shell$ git add include/configs/zynq_pynqz1.h
shell$ git commit -m "patch for zynq-pynqz1"
```

#### Setup for Build 

```console
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make zynq_pynqz1_defconfig
```

#### Build u-boot

```console
shell$ make
```

#### Copy boot.bin and u-boot.img to target/zybo-pynqz1/boot/

```console
shell$ cp spl/boot.bin  ../target/zynq-pynqz1/boot/
shell$ cp u-boot.img    ../target/zynq-pynqz1/boot/
```

