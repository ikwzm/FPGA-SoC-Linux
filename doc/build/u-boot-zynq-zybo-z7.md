### Build U-boot for ZYBO Z7

There are two ways

1. run scripts/build-u-boot-zynq-zybo-z7.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download U-boot Source

##### Clone from git.denx.de/u-boot.git

```
shell$ git clone git://git.denx.de/u-boot.git u-boot-zynq-zybo-z7
````

##### Checkout v2016.03

```
shell$ cd u-boot-zynq-zybo-z7
shell$ git checkout -b u-boot-2016.03-zynq-zybo refs/tags/v2016.03
```

#### Patch for zynq-zybo

```
shell$ patch -p0 < ../files/u-boot-2016.03-zynq-zybo-z7.diff
shell$ git add --update
shell$ git add arch/arm/dts/zynq-zybo-z7.dts
shell$ git add board/xilinx/zynq/zybo_z7_hw_platform/*
shell$ git add configs/zynq_zybo_z7_defconfig
shell$ git add include/configs/zynq_zybo_z7.h
shell$ git commit -m "patch for zynq-zybo-z7"
```

#### Setup for Build 

```
shell$ cd u-boot-zynq-zybo-z7
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make zynq_zybo_z7_defconfig
```

#### Build u-boot

```
shell$ make
```

#### Copy boot.bin and u-boot.img to target/zybo-zynq/boot/

```
shell$ cp spl/boot.bin  ../target/zynq-zybo-z7/boot/
shell$ cp u-boot.img    ../target/zynq-zybo-z7/boot/
```

