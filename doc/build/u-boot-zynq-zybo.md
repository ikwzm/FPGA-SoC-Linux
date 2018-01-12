### Build U-boot for ZYBO

There are two ways

1. run scripts/build-u-boot-zynq-zybo.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download U-boot Source

##### Clone from git.denx.de/u-boot.git

```console
shell$ git clone git://git.denx.de/u-boot.git u-boot-zynq-zybo
```

##### Checkout v2016.03

```console
shell$ cd u-boot-zynq-zybo
shell$ git checkout -b u-boot-2016.03-zynq-zybo refs/tags/v2016.03
```

#### Patch for zynq-zybo

```console
shell$ patch -p0 < ../files/u-boot-2016.03-zynq-zybo.diff
shell$ git add --update
shell$ git commit -m "patch for zynq-zybo"
```

#### Setup for Build 

```console
shell$ cd u-boot-zynq-zybo
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make zynq_zybo_defconfig
```

#### Build u-boot

```console
shell$ make
```

#### Copy boot.bin and u-boot.img to target/zybo-zynq/boot/

```console
shell$ cp spl/boot.bin  ../target/zynq-zybo/boot/
shell$ cp u-boot.img    ../target/zynq-zybo/boot/
```

