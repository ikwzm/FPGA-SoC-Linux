### Build U-boot for ZYBO

#### Repository

* https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO

#### Download

```console
shell$ git clone --depth=1 -b v2016.03-1 https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO.git
```

#### Build u-boot-spl.sfp and u-boot.img

Pleade refer to the Readme.md of https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO

#### Copy boot.bin and u-boot.img to target/zynq-zybo/boot/

```console
shell$ cd FPGA-SoC-U-Boot-ZYBO
shell$ cp boot.bin   ../target/zynq-zybo/boot/
shell$ cp u-boot.img ../target/zynq-zybo/boot/
```

