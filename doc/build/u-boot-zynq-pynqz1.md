### Build U-boot for PYNQ-Z1

#### Download FPGA-SoC-U-Boot-PYNQ-Z1

```console
shell$ git clone https://github.com/ikwzm/FPGA-SoC-U-Boot-PYNQ-Z1.git
```

#### Checkout v2016.03-1

```console
shell$ cd FPGA-SoC-U-Boot-PYNQ-Z1
shell$ git checkout v2016.03-1
```

#### Copy boot.bin and u-boot.img to target/zybo-pynqz1/boot/

```console
shell$ cp boot.bin   ../target/zynq-pynqz1/boot/
shell$ cp u-boot.img ../target/zynq-pynqz1/boot/
```

