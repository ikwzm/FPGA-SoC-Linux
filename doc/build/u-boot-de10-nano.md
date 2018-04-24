### Build U-boot for DE10-Nano

#### Download FPGA-SoC-U-Boot-DE10-Nano

```console
shell$ git clone https://github.com/ikwzm/FPGA-SoC-U-Boot-DE10-Nano.git
```

#### Checkout v2017.11-1

```console
shell$ cd FPGA-SoC-U-Boot-DE10-Nano
shell$ git checkout v2017.11-1
```
#### Copy u-boot-spl.sfp and u-boot.img target/de0-nano-soc/u-boot/

```console
shell$ cp u-boot-spl.sfp ../target/de10-nano/u-boot/u-boot-spl.sfp
shell$ cp u-boot.img     ../target/de10-nano/u-boot/u-boot.img
```

