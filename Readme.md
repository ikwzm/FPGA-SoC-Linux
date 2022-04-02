FPGA-SoC-Linux
====================================================================================

Overview
------------------------------------------------------------------------------------

### Introduction

This Repository provides a Linux Boot Image(U-boot, Kernel, Root-fs) for FPGA-SoC.

**Note: Downloading the entire repository takes time, so download the source code from https://github.com/ikwzm/FPGA-SoC-Linux/releases.**

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
* Linux Kernel Version 5.10.69
  + Available in both Xilinx-Zynq-7000 and Altera-SoC in a single image
  + Enable Device Tree Overlay
  + Enable FPGA Manager
  + Enable FPGA Bridge
  + Enable FPGA Reagion
  + Patch for issue #3(USB-HOST does not work with PYNQ-Z1)
* Debian11(bullseye) Root File System
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

Install
------------------------------------------------------------------------------------

* Install U-Boot and Linux to SD-Card
  + [ZYBO](doc/install/zynq-zybo.md)
  + [ZYBO-Z7](doc/install/zynq-zybo-z7.md)
  + [PYNQ-Z1](doc/install/zynq-pynqz1.md)
  + [DE0-Nano-SoC](doc/install/de0-nano-soc.md)
  + [DE10-Nano](doc/install/de10-nano.md)
* [Install Device Drivers and Services](doc/install/device-drivers.md)
* [Upgrade to v1.3.0 from v1.0.x/v1.1.x/v1.2.x](doc/install/upgrade-v1.3.0.md)

Tutorial
------------------------------------------------------------------------------------

* FPGA-SoC-Linux-Example-1
  - [FPGA-SoC-Linux-Example-1-ZYBO](https://github.com/ikwzm/FPGA-SoC-Linux-Example-1-ZYBO)
  - [FPGA-SoC-Linux-Example-1-ZYBO-Z7](https://github.com/ikwzm/FPGA-SoC-Linux-Example-1-ZYBO-Z7)
  - [FPGA-SoC-Linux-Example-1-PYNQ-Z1](https://github.com/ikwzm/FPGA-SoC-Linux-Example-1-PYNQ-Z1)
  - [FPGA-SoC-Linux-Example-1-DE0-Nano-SoC](https://github.com/ikwzm/FPGA-SoC-Linux-Example-1-DE0-Nano-SoC)
  - [FPGA-SoC-Linux-Example-1-DE10-Nano](https://github.com/ikwzm/FPGA-SoC-Linux-Example-1-DE10-Nano)

Build 
------------------------------------------------------------------------------------

* [Build U-boot for ZYBO](doc/build/u-boot-zynq-zybo.md)
* [Build U-boot for ZYBO-Z7](doc/build/u-boot-zynq-zybo-z7.md)
* [Build U-boot for PYNQ-Z1](doc/build/u-boot-zynq-pynqz1.md)
* [Build U-boot for DE0-Nano-SoC](doc/build/u-boot-de0-nano-soc.md)
* [Build U-boot for DE10-Nano](doc/build/u-boot-de10-nano.md)
* [Build Linux Kernel](doc/build/linux-kernel-5.10.69.md)
* [Build Debian11 RootFS](doc/build/debian11-rootfs.md)
* [Build Device Drivers and Services Package](doc/build/device-drivers.md)

