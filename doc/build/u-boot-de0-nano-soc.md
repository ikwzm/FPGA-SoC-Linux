### Build U-boot for DE0-Nano-SoC

#### Repository

* https://github.com/ikwzm/FPGA-SoC-U-Boot-DE0-Nano-SoC

#### Download

```console
shell$ git clone --depth=1 -b v2017.11-1 https://github.com/ikwzm/FPGA-SoC-U-Boot-DE0-Nano-SoC.git
```

#### Build u-boot-spl.sfp and u-boot.img

Pleade refer to the Readme.md of https://github.com/ikwzm/FPGA-SoC-U-Boot-DE0-Nano-SoC

#### Copy u-boot-spl.sfp and u-boot.img target/de0-nano-soc/u-boot/

```console
shell$ cd FPGA-SoC-U-Boot-DE0-Nano-SoC
shell$ cp u-boot-spl.sfp ../target/de0-nano-soc/u-boot/u-boot-spl.sfp
shell$ cp u-boot.img     ../target/de0-nano-soc/u-boot/u-boot.img
```

