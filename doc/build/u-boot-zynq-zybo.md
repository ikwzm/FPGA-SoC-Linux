### Build U-boot for ZYBO

#### Download FPGA-SoC-U-Boot-ZYBO

```console
shell$ git clone https://github.com/ikwzm/FPGA-SoC-U-Boot-ZYBO.git
```

#### Checkout v2016.03-1

```console
shell$ cd FPGA-SoC-U-Boot-ZYBO
shell$ git checkout v2016.03-1
```

#### Copy boot.bin and u-boot.img to target/zybo-zynq/boot/

```console
shell$ cp boot.bin   ../target/zynq-zybo/boot/
shell$ cp u-boot.img ../target/zynq-zybo/boot/
```

