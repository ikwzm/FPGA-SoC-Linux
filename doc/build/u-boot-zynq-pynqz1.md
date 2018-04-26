### Build U-boot for PYNQ-Z1

#### Repository

* https://github.com/ikwzm/FPGA-SoC-U-Boot-PYNQ-Z1

#### Download

```console
shell$ git clone --depth=1 -b v2016.03-1 https://github.com/ikwzm/FPGA-SoC-U-Boot-PYNQ-Z1.git
```

#### Build u-boot-spl.sfp and u-boot.img

Pleade refer to the Readme.md of https://github.com/ikwzm/FPGA-SoC-U-Boot-PYNQ-Z1

#### Copy boot.bin and u-boot.img to target/zynq-pynqz1/boot/

```console
shell$ cd FPGA-SoC-U-Boot-PYNQ-Z1
shell$ cp boot.bin   ../target/zynq-pynqz1/boot/
shell$ cp u-boot.img ../target/zynq-pynqz1/boot/
```

