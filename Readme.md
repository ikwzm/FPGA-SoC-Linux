FPGA-SoC-Linux
====================================================================================

Overview
------------------------------------------------------------------------------------

### Introduction

This Repository provides a Linux Boot Image(U-boot, Kernel, Root-fs) for FPGA-SoC.

### Notice

This repository is currently no longer being updated.
The reason is that this repository contains many binary files and has become difficult to maintain.
We have decided to provide a separate repository for each distribution from now on.
Please refer to the following repositories

 * Debian12
   - https://github.com/ikwzm/FPGA-SoC-Debian12

### Features

* Hardware
  + ZYBO    : Xilinx Zynq-7000 ARM/FPGA SoC Trainer Board by Digilent
  + ZYBO-Z7 : Xilinx Zynq-7020 Development Board by Digilent
  + PYNQ-Z1 : Python Productive for Zynq by Digilent
  + DE0-Nano-SoC : Altera SoC FPGA Development Kit by Terasic
  + DE10-Nano    : Altera SoC FPGA Development Kit by Terasic
* U-Boot v2016.03 or v2017.11
  + Build U-Boot v2016.03 for ZYBO, PYNQ-Z1
  + Build U-Boot v2017.11 for ZYBO-Z7, DE0-Nano-SoC, DE10-Nano
  + Customized boot by uEnv.txt
  + Customized boot by boot.scr
  + Enable bootmenu
* Linux Kernel 
  + Available in both Xilinx-Zynq-7000 and Altera-SoC in a single image
  + Enable Device Tree Overlay
  + Enable FPGA Manager
  + Enable FPGA Bridge
  + Enable FPGA Reagion
  + Patch for issue #3(USB-HOST does not work with PYNQ-Z1)
* Debian Root File System
  + Installed build-essential
  + Installed device-tree-compiler
  + Installed ruby ruby-msgpack ruby-serialport
  + Installed python python3 python3-numpy msgpack-rpc-python
  + Installed u-boot-tools
  + Installed Other package list -> [files/debian11-dpkg-list.txt](files/debian11-dpkg-list.txt)
* FPGA Device Drivers and Services
  + [dtbocfg    (Device Tree Blob Overlay Configuration File System)](https://github.com/ikwzm/dtbocfg)
  + [fclkcfg    (FPGA Clock Configuration Device Driver)](https://github.com/ikwzm/fclkcfg)
  + [u-dma-buf  (User space mappable DMA Buffer)](https://github.com/ikwzm/udmabuf)
  + [zptty      (Pseudo TeleTYpewriter for FPGA Device)](https://github.com/ikwzm/PTTY_AXI4)
  + zynq-afi   (Xilinx ZYNQ AFI Kernel Module)

Release History
------------------------------------------------------------------------------------

**Note: Downloading the entire repository takes time, so download the source code from https://github.com/ikwzm/FPGS-SoC-Linux/releases.**

| Release | Released   | Debian Version | Linux Kernel Version  | Release Tag |
|:--------|:-----------|:---------------|:----------------------|:------------|
| v2.2.0  | 2023-2-3   | Debian 11.6    | 5.10.165-armv7-fpga   | [v2.2.0](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v2.2.0)  |
| v2.1.1  | 2022-4-7   | Debian 11.3    | 5.10.109-armv7-fpga   | [v2.1.1](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v2.1.1)  |
| v2.0.1  | 2022-4-2   | Debian 11      | 5.10.69-armv7-fpga    | [v2.0.1](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v2.0.1)  |
| v1.3.0  | 2021-3-12  | Debian 10      | 5.4.105-armv7-fpga    | [v1.3.0](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v1.3.0)  | 
| v1.2.1  | 2020-8-31  | Debian 10      | 5.4.59-armv7-fpga     | [v1.2.1](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v1.2.1)  | 
| v1.1.0  | 2020-1-26  | Debian 10      | 5.4.47-armv7-fpga     | [v1.1.0](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v1.1.0)  | 
| v1.0.1  | 2019-8-8   | Debian 10      | 4.19.57-armv7-fpga    | [v1.0.1](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v1.0.1)  | 
| v0.9.0  | 2019-6-8   | Debian 9       | 4.14.123-armv7-fpga   | [v0.9.0](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v0.9.0)  | 
| v0.8.2  | 2018-8-18  | Debian 9       | 4.14.34-armv7-fpga    | [v0.8.2](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v0.8.2)  | 
| v0.7.2  | 2018-3-14  | Debian 9       | 4.14.21-armv7-fpga    | [v0.7.2](https://github.com/ikwzm/FPGA-SoC-Linux/tree/v0.7.2)  | 
