### Build U-boot for ZYBO Z7

#### Download FPGA-SoC-U-Boot-ZYBO-Z7

```console
shell$ git clone https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO-Z7.git
```

#### Checkout v2017.11-1

```console
shell$ cd FPGA-SoC-U-Boot-ZYBO-Z7
shell$ git checkout v2017.11-1
```

#### Copy boot.bin and u-boot.img to target/zybo-zynq/boot/

```console
shell$ cp boot.bin   ../target/zynq-zybo-z7/boot/
shell$ cp u-boot.img ../target/zynq-zybo-z7/boot/
```

