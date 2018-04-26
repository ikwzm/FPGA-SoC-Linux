### Build U-boot for ZYBO Z7

#### Repository

* https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO-Z7

#### Download

```console
shell$ git clone --depth=1 -b v2017.11-1 https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO-Z7.git
```

#### Build u-boot-spl.sfp and u-boot.img

Pleade refer to the Readme.md of https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO-Z7

#### Copy boot.bin and u-boot.img to target/zynq-zybo-z7/boot/

```console
shell$ cd FPGA-SoC-U-Boot-ZYBO-Z7
shell$ cp boot.bin   ../target/zynq-zybo-z7/boot/
shell$ cp u-boot.img ../target/zynq-zybo-z7/boot/
```

