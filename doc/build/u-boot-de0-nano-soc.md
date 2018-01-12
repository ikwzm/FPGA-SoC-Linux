### Build U-boot for DE0-Nano-SoC

There are two ways

1. run scripts/build-u-boot-de0-nano-soc.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download U-boot Source

##### Clone from git.denx.de/u-boot.git

```console
shell$ git clone git://git.denx.de/u-boot.git u-boot-de0-nano-soc
```

##### Checkout v2016.03

```console
shell$ cd u-boot-de0-nano-soc
shell$ git checkout -b u-boot-2016.03-de0-nano-soc refs/tags/v2016.03
```

#### Patch for de0-nano-soc

```console
shell$ patch -p0 < ../files/u-boot-2016.03-de0-nano-soc.diff
shell$ git add --update
shell$ git commit -m "patch for de0-nano-soc"
```

#### Setup for Build 

```console
shell$ cd u-boot-de0-nano-soc
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make socfpga_de0_nano_soc_defconfig
```

#### Build u-boot

```console
shell$ make
```

#### Copy u-boot-spl.sfp and u-boot.img target/de0-nano-soc/u-boot/

```console
shell$ cp spl/u-boot-spl.sfp ../target/de0-nano-soc/u-boot/u-boot-spl.sfp
shell$ cp u-boot.img         ../target/de0-nano-soc/u-boot/u-boot.img
```

