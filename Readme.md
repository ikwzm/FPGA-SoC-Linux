FPGA-SoC-Linux
====================================================================================

Overview
------------------------------------------------------------------------------------

### Introduction

This Repository provides a Linux Boot Image(U-boot, Kernel, Root-fs) for FPGA-SoC.

### Features

* Hardware
  + ZYBO : Xilinx Zynq-7000 ARM/FPGA SoC Trainer Board by Digilent
  + PYNQ-Z1 : Python Productive for Zynq by Digilent
  + DE0-Nano-SoC : Altera SoC FPGA Development Kit by terasic
* U-Boot v2016.03 (customized)
  + Build for ZYBO, PYNQ-Z1 and DE0-Nano-SoC
  + Customized boot by uEnv.txt
  + Customized boot by boot.scr
* Linux Kernel Version v4.12.13
  + Available in both Xilinx-Zynq-7000 and Altera-SoC in a single image
  + Enable Device Tree Overlay
  + Enable FPGA Manager
  + Enable FPGA Bridge
  + Enable FPGA Reagion
* Debian8(jessie) Root File System
  + Installed build-essential
  + Installed device-tree-compiler
  + Installed ruby ruby-msgpack ruby-serialport
  + Installed python python3 msgpack-rpc-python
  + Installed u-boot-tools
* FPGA Device Drivers and Services
  + [dtbocfg    (Device Tree Blob Overlay Configuration File System)](https://github.com/ikwzm/dtbocfg)
  + [fclkcfg    (FPGA Clock Configuration Device Driver)](https://github.com/ikwzm/fclkcfg)
  + [udmabuf    (User space mappable DMA Buffer)](https://github.com/ikwzm/udmabuf)
  + [zptty      (Pseudo TeleTYpewriter for FPGA Device)](https://github.com/ikwzm/PTTY_AXI4)

Install
------------------------------------------------------------------------------------

* Install U-Boot and Linux to SD-Card
  + [ZYBO](doc/install/zynq-zybo.md)
  + [PYNQ-Z1](doc/install/zynq-pynqz1.md)
  + [DE0-Nano-SoC](doc/install/de0-nano-soc.md)
  + [Dual Boot(ZYBO and DE0-Nano-SoC)](doc/install/zynq-zybo-de0-nano-soc.md)
* [Install Device Drivers](doc/install/device-drivers.md)

Tutorial
------------------------------------------------------------------------------------

* [uio_irq_sample](doc/tutorial/uio_irq_sample.md)
* [accumulator](doc/tutorial/accumulator.md)
* [fibonacci](doc/tutorial/fibonacci.md)

Build 
------------------------------------------------------------------------------------

* [Build U-boot for ZYBO](doc/build/u-boot-zynq-zybo.md)
* [Build U-boot for PYNQ-Z1](doc/build/u-boot-zynq-pynqz1.md)
* [Build U-boot for DE0-Nano-SoC](doc/build/u-boot-de0-nano-soc.md)
* [Build Linux Kernel](doc/build/linux-kernel-4.12.13.md)
* [Build Debian8 RootFS](doc/build/debian8-rootfs.md)
* [Build Device Drivers and Services Package](doc/build/device-drivers.md)

