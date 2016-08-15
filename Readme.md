FPGA-SoC-Linux
====================================================================================

Overview
------------------------------------------------------------------------------------

### Introduction

This Repository provides a Linux Boot Image(U-boot, Kernel, Root-fs) for FPGA-SoC.

### Features

* Hardware
  + ZYBO : Xilinx Zynq-7000 ARM/FPGA SoC Trainer Board by Digilent
  + DE0-Nano-SoC : Altera SoC FPGA Development Kit by terasic
* U-Boot v2016.03 (customized)
  + Build for ZYBO and DE0-Nano-SoC
  + Customized boot by uEnv.txt
  + Customized boot by boot.scr
* Linux Kernel Version v4.4.7
  + Available in both Xilinx-Zynq-7000 and Altera-SoC in a single image
  + Enable Device Tree Overlay
  + Enable FPGA Manager
* Debian8(jessie) Root File System
  + Installed build-essential
  + Installed device-tree-compiler
  + Installed ruby ruby-msgpack ruby-serialport
  + Installed u-boot-tools
* FPGA Device Drivers
  + [dtbocfg    (Device Tree Blob Overlay Configuration File System)](https://github.com/ikwzm/dtbocfg)
  + [fpgacfg    (FPGA Configuration Interface for Linux FPGA Manager Framework)](https://github.com/ikwzm/fpgacfg)
  + [fclkcfg    (FPGA Clock Configuration Device Driver)](https://github.com/ikwzm/fclkcfg)
  + [udmabuf    (User space mappable DMA Buffer)](https://github.com/ikwzm/udmabuf)
  + [zptty      (Pseudo TeleTYpewriter for FPGA Device)](https://github.com/ikwzm/PTTY_AXI4)
  + fpga-bridge (FPGA to/from HPS Bridge Driver for Altera SoCFPGA Devices)

Install
------------------------------------------------------------------------------------

### ZYBO

#### Downlowd from github

```
shell$ git clone git://github.com/ikwzm/FPGA-SoC-Linux
shell$ cd FPGA-SoC-Linux
shell$ git lfs pull origin master
```

#### File Description

 * tareget/zynq-zybo/
   + boot/
     - boot.bin                                              : Stage 1 Boot Loader(U-boot-spl)
     - design_1_wrapper.bit                                  : FPGA configuration file (Xilinx Bitstream Format)
     - u-boot.img                                            : Stage 2 Boot Loader(U-boot)
     - uEnv.txt                                              : U-Boot environment variables for linux boot
     - zImage-4.4.7-armv7-fpga                               : Linux Kernel Image
     - devicetree-4.4.7-zynq-zybo.dtb                        : Linux Device Tree Blob
     - devicetree-4.4.7-zynq-zybo.dts                        : Linux Device Tree Source
   + examples-001.tgz                                        : Examples Programs        (use Git LFS)
 * debian8-rootfs-vanilla.tgz                                : Debian8 Root File System (use Git LFS)
 * fpga-soc-linux-drivers-4.4.7-armv7-fpga_0.0.2-1_armhf.deb : Device Drivers Package   (use Git LFS)

#### Format SD-Card

````
shell# fdisk /dev/sdc
   :
   :
   :
shell# mkfs-vfat /dev/sdc1
shell# mkfs.ext3 /dev/sdc2
````

#### Write to SD-Card

````
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/zynq-zybo/boot/*                                   /mnt/usb1
shell# tar xfz debian8-rootfs-vanilla.tgz -C                        /mnt/usb2
shell# cp fpga-soc-linux-drivers-4.4.7-armv7-fpga_0.0.2-1_armhf.deb /mnt/usb2/home/fpga
shell# tar xfz target/zynq-zybo/examples-001.tgz -C                 /mnt/usb2/home/fpga
shell# umount mnt/usb1
shell# umount mnt/usb2
````

### DE0-Nano-SoC

#### Downlowd from github

```
shell$ git clone git://github.com/ikwzm/FPGA-SoC-Linux
shell$ cd FPGA-SoC-Linux
shell$ git lfs pull origin master
```

#### File Description

 * target/de0-nano-soc/
   + boot/
     - DE0_NANO_SOC.rbf                                      : FPGA configuration file (Raw Binary Format)
     - uEnv.txt                                              : U-Boot environment variables for linux boot
     - zImage-4.4.7-armv7-fpga                               : Linux Kernel Image
     - devicetree-4.4.7-socfpga.dtb                          : Linux Device Tree Blob
     - devicetree-4.4.7-socfpga.dts                          : Linux Device Tree Source
   + u-boot/
     - u-boot-spl.sfp                                        : Stage 1 Boot Loader(U-boot-spl)
     - u-boot.img                                            : Stage 2 Boot Loader(U-boot)
 * debian8-rootfs-vanilla.tgz                                : Debian8 Root File System (use Git LFS)
 * fpga-soc-linux-drivers-4.4.7-armv7-fpga_0.0.2-1_armhf.deb : Device Drivers Package   (use Git LFS)

#### Format SD-Card

````
shell# fdisk /dev/sdc
   :
   :
   :
shell# mkfs-vfat /dev/sdc1
shell# mkfs.ext3 /dev/sdc2
````

#### Write to SD-Card

````
shell# mount /dev/sdc1 /mnt/usb1
shell# mount /dev/sdc2 /mnt/usb2
shell# cp target/de0-nano-soc/boot/* /mnt/usb1
shell# dd if=target/de0-nano-soc/u-boot/u-boot-spl.sfp of=/dev/sdc3 bs=64k seek=0
shell# dd if=target/de0-nano-soc/u-boot/u-boot.img     of=/dev/sdc3 bs=64k seek=4
shell# tar xfz debian8-rootfs-vanilla.tgz -C                        /mnt/usb2
shell# cp fpga-soc-linux-drivers-4.4.7-armv7-fpga_0.0.2-1_armhf.deb /mnt/usb2/home/fpga
shell# umount mnt/usb1
shell# umount mnt/usb2
````

### Install Device Drivers 

#### Boot ZYBO or DE0-Nano-SoC and login fpga or root user

fpga'password is "fpga".

```
debian-fpga login: fpga
Password:
fpga@debian-fpga:~$
```

root'password is "admin".

```
debian-fpga login: root
Password:
root@debian-fpga:~#
```

#### Install Debian Package

```
fpga@debian-fpga:~$ sudo dpkg -i fpga-soc-linux-drivers-4.4.7-armv7-fpga_0.0.2-1_armhf.deb
Selecting previously unselected package fpga-soc-linux-drivers.
(Reading database ... 17830 files and directories currently installed.)
Preparing to unpack fpga-soc-linux-drivers_0.0.2-1_armhf.deb ...
Unpacking fpga-soc-linux-drivers (0.0.2-1) ...
Setting up fpga-soc-linux-drivers (0.0.2-1) ...
Created symlink from /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service to /etc/systemd/system/device-tree-overlay.service.
Created symlink from /etc/systemd/system/multi-user.target.wants/fpga-manager.service to /etc/systemd/system/fpga-manager.service.
Created symlink from /etc/systemd/system/multi-user.target.wants/udmabuf.service to /etc/systemd/system/udmabuf.service.
Created symlink from /etc/systemd/system/multi-user.target.wants/zptty.service to /etc/systemd/system/zptty.service.
```

#### Check Installed Package

```
fpga@debian-fpga:~$ sudo lsmod
Module                  Size  Used by
zptty                   8529  0
udmabuf                10177  0
fpgacfg                12287  0
dtbocfg                 3200  2
fpga@debian-fpga:~$ sudo systemctl status device-tree-overlay.service
● device-tree-overlay.service - Device Tree Overlay Service.
   Loaded: loaded (/etc/systemd/system/device-tree-overlay.service; enabled)
   Active: active (exited) since Sat 2016-04-30 07:50:08 JST; 1min 22s ago
  Process: 1461 ExecStart=/sbin/modprobe dtbocfg (code=exited, status=0/SUCCESS)
 Main PID: 1461 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/device-tree-overlay.service

Apr 30 07:50:08 debian-fpga systemd[1]: Started Device Tree Overlay Service..
fpga@debian-fpga:~$ sudo systemctl status fpga-manager.service
● fpga-manager.service - FPGA Manager Service.
   Loaded: loaded (/etc/systemd/system/fpga-manager.service; enabled)
   Active: active (exited) since Sat 2016-04-30 07:50:09 JST; 2min 46s ago
  Process: 1477 ExecStart=/sbin/modprobe fpgacfg (code=exited, status=0/SUCCESS)
  Process: 1467 ExecStartPre=/usr/bin/fpgacfg_load_overlay.rb (code=exited, status=0/SUCCESS)
 Main PID: 1477 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/fpga-manager.service

Apr 30 07:50:09 debian-fpga systemd[1]: Started FPGA Manager Service..
fpga@debian-fpga:~$ sudo systemctl status udmabuf.service
● udmabuf.service - User space mappable DMA Buffer Service.
   Loaded: loaded (/etc/systemd/system/udmabuf.service; enabled)
   Active: active (exited) since Sat 2016-04-30 07:50:09 JST; 3min 50s ago
  Process: 1484 ExecStart=/sbin/modprobe udmabuf (code=exited, status=0/SUCCESS)
 Main PID: 1484 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/udmabuf.service

Apr 30 07:50:09 debian-fpga systemd[1]: Started User space mappable DMA Buff....
Hint: Some lines were ellipsized, use -l to show in full.
fpga@debian-fpga:~$ sudo systemctl status zptty.service
● zptty.service - Pseudo TTY Driver for communication with FPGA.
   Loaded: loaded (/etc/systemd/system/zptty.service; enabled)
   Active: active (exited) since Sat 2016-04-30 07:50:09 JST; 4min 40s ago
  Process: 1491 ExecStart=/sbin/modprobe zptty (code=exited, status=0/SUCCESS)
 Main PID: 1491 (code=exited, status=0/SUCCESS)
```

Tutorial
------------------------------------------------------------------------------------

### uio_irq_sample

- [https://github.com/ikwzm/ZYBO_UIO_IRQ_SAMPLE](https://github.com/ikwzm/ZYBO_UIO_IRQ_SAMPLE)


#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/uio_irq_sample$ rake -T
rake devicetree:install    # Install device tree
rake devicetree:uninstall  # Uninstall device tree
rake fpga:install          # Install fpga
rake install               # Install fpga and devicetrees
rake uninstall             # Uninstall fpga and devicetrees
```

#### Install FPGA and Device Tree

##### ZYBO

```
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dd if=design_1_wrapper.bit of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
2083852 bytes (2.1 MB) copied, 0.0518765 s, 40.2 MB/s
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
[ 5257.752033] udmabuf amba:pump-udmabuf4: driver probe start.
[ 5257.771542] udmabuf udmabuf4: driver installed
[ 5257.775914] udmabuf udmabuf4: major number   = 245
[ 5257.780743] udmabuf udmabuf4: minor number   = 0
[ 5257.785287] udmabuf udmabuf4: phys address   = 0x1f100000
[ 5257.790707] udmabuf udmabuf4: buffer size    = 4194304
[ 5257.795790] udmabuf amba:pump-udmabuf4: driver installed.
[ 5257.801731] udmabuf amba:pump-udmabuf5: driver probe start.
[ 5257.819306] udmabuf udmabuf5: driver installed
[ 5257.823698] udmabuf udmabuf5: major number   = 245
[ 5257.828442] udmabuf udmabuf5: minor number   = 1
[ 5257.833085] udmabuf udmabuf5: phys address   = 0x1f500000
[ 5257.838424] udmabuf udmabuf5: buffer size    = 4194304
[ 5257.843584] udmabuf amba:pump-udmabuf5: driver installed.
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dd if=DE0_NANO_SOC.rbf of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
1365784 bytes (1.4 MB) copied, 0.202703 s, 6.7 MB/s
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
[  561.659154] udmabuf soc:amba:pump-udmabuf4: driver probe start.
[  561.676785] udmabuf udmabuf4: driver installed
[  561.681221] udmabuf udmabuf4: major number   = 241
[  561.687117] udmabuf udmabuf4: minor number   = 0
[  561.691721] udmabuf udmabuf4: phys address   = 0x3f100000
[  561.698038] udmabuf udmabuf4: buffer size    = 4194304
[  561.703728] udmabuf soc:amba:pump-udmabuf4: driver installed.
[  561.709867] udmabuf soc:amba:pump-udmabuf5: driver probe start.
[  561.727397] udmabuf udmabuf5: driver installed
[  561.731833] udmabuf udmabuf5: major number   = 241
[  561.737816] udmabuf udmabuf5: minor number   = 1
[  561.742420] udmabuf udmabuf5: phys address   = 0x3f500000
[  561.748747] udmabuf udmabuf5: buffer size    = 4194304
[  561.754385] udmabuf soc:amba:pump-udmabuf5: driver installed.
```

#### Compile sample programs

```
fpga@debian-fpga:~/examples/uio_irq_sample$ rake
gcc  -o sample1 sample1.c
gcc  -o sample2 sample2.c
```

#### Run sample programs

```
fpga@debian-fpga:~/examples/uio_irq_sample$ ./sample1
time = 0.022111 sec
time = 0.022158 sec
time = 0.022040 sec
time = 0.022147 sec
time = 0.022094 sec
time = 0.022021 sec
time = 0.022118 sec
time = 0.022119 sec
time = 0.022078 sec
time = 0.022076 sec
```

```
fpga@debian-fpga:~/examples/uio_irq_sample$ ./sample2
time = 0.022132 sec
time = 0.022015 sec
time = 0.022190 sec
time = 0.022070 sec
time = 0.022135 sec
time = 0.022116 sec
time = 0.022134 sec
time = 0.022103 sec
time = 0.022103 sec
time = 0.022095 sec
```

#### Uninstall Device Tree

```
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake uninstall
dtbocfg.rb --remove uio_irq_sample
[ 5559.550963] udmabuf udmabuf5: driver uninstalled
[ 5559.556676] udmabuf amba:pump-udmabuf5: driver unloaded
[ 5559.563018] udmabuf udmabuf4: driver uninstalled
[ 5559.569580] udmabuf amba:pump-udmabuf4: driver unloaded
```

### accumulator

- [https://github.com/ikwzm/msgpack-vhdl-examples](https://github.com/ikwzm/msgpack-vhdl-examples)
- [https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/accumulator](https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/accumulator)

#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/accumulator$ rake -T
rake fpga:install     # Install fpga
rake install          # Install fpga and devicetrees
rake run              # run
rake uninstall        # Uninstall fpga and devicetrees
rake zptty:install    # Install zptty device driver
rake zptty:uninstall  # Unnstall zptty device driver
```

#### Install FPGA and Device Tree

##### ZYBO

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake install
dd if=design_1_wrapper.bit of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
2083852 bytes (2.1 MB) copied, 0.0528286 s, 39.4 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-zynq-zybo.dts
[ 6032.783171] zptty 43c10000.zptty: ZPTTY Driver probe start
[ 6032.788851] zptty 43c10000.zptty: driver installed
[ 6032.793622] zptty 43c10000.zptty: device name    = zptty0
[ 6032.798945] zptty 43c10000.zptty: private record = ddfffc00 (332bytes)
[ 6032.805495] zptty 43c10000.zptty: major number   = 246
[ 6032.810574] zptty 43c10000.zptty: minor number   = 0
[ 6032.815567] zptty 43c10000.zptty: regs resource  = [mem 0x43c10000-0x43c10fff flags 0x200]
[ 6032.823806] zptty 43c10000.zptty: regs address   = e15b8000
[ 6032.829325] zptty 43c10000.zptty: irq resource   = [irq 161 flags 0x404]
[ 6032.836047] zptty 43c10000.zptty: tx buf size    = 128
[ 6032.841166] zptty 43c10000.zptty: rx buf size    = 128
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake install
dd if=DE0_NANO_SOC.rbf of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
1312432 bytes (1.3 MB) copied, 0.185027 s, 7.1 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-de0-nano-soc.dts
[  896.483534] zptty ff202000.zptty: ZPTTY Driver probe start
[  896.489281] zptty ff202000.zptty: driver installed
[  896.494062] zptty ff202000.zptty: device name    = zptty0
[  896.499496] zptty ff202000.zptty: private record = eebbc400 (332bytes)
[  896.506001] zptty ff202000.zptty: major number   = 240
[  896.511161] zptty ff202000.zptty: minor number   = 0
[  896.516112] zptty ff202000.zptty: regs resource  = [mem 0xff202000-0xff202fff flags 0x200]
[  896.524390] zptty ff202000.zptty: regs address   = f203a000
[  896.529985] zptty ff202000.zptty: irq resource   = [irq 67 flags 0x404]
[  896.536574] zptty ff202000.zptty: tx buf size    = 128
[  896.541718] zptty ff202000.zptty: rx buf size    = 128
```

#### Run sample script

```
fpga@debian-fpga:~/examples/accumulator$ ruby test.rb
OK : reg = 1; add(6625) => 6626; reg = 6626
OK : reg = 6626; add(9833) => 16459; reg = 16459
OK : reg = 16459; add(7280) => 23739; reg = 23739
OK : reg = 23739; add(3535) => 27274; reg = 27274
OK : reg = 27274; add(5848) => 33122; reg = 33122
OK : reg = 33122; add(9770) => 42892; reg = 42892
OK : reg = 42892; add(2771) => 45663; reg = 45663
      :
      :
      :
OK : reg = -4997637; add(-9940) => -5007577; reg = -5007577
OK : reg = -5007577; add(-3887) => -5011464; reg = -5011464
NoMethodError
ArgumentError
ArgumentError
```

#### Uninstall Device Tree

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake uninstall
dtbocfg.rb --remove zptty0
[ 6258.046383] zptty 43c10000.zptty: driver removed
```

### fibonacci

- [https://github.com/ikwzm/msgpack-vhdl-examples](https://github.com/ikwzm/msgpack-vhdl-examples)
- [https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/fibonacci](https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/fibonacci)

#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/fibonacci$ rake -T
rake fpga:install     # Install fpga
rake install          # Install fpga and devicetrees
rake run              # run
rake uninstall        # Uninstall fpga and devicetrees
rake zptty:install    # Install zptty device driver
rake zptty:uninstall  # Unnstall zptty device driver
```

#### Install FPGA and Device Tree

##### ZYBO

```
fpga@debian-fpga:~/examples/fibonacci$ sudo rake install
dd if=design_1_wrapper.bit of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
2083852 bytes (2.1 MB) copied, 0.140482 s, 14.8 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-zynq-zybo.dts
[ 6688.904316] zptty 43c10000.zptty: ZPTTY Driver probe start
[ 6688.909991] zptty 43c10000.zptty: driver installed
[ 6688.914806] zptty 43c10000.zptty: device name    = zptty0
[ 6688.920124] zptty 43c10000.zptty: private record = ddffac00 (332bytes)
[ 6688.926729] zptty 43c10000.zptty: major number   = 246
[ 6688.931787] zptty 43c10000.zptty: minor number   = 0
[ 6688.936792] zptty 43c10000.zptty: regs resource  = [mem 0x43c10000-0x43c10fff flags 0x200]
[ 6688.945022] zptty 43c10000.zptty: regs address   = e17bc000
[ 6688.950538] zptty 43c10000.zptty: irq resource   = [irq 161 flags 0x404]
[ 6688.957255] zptty 43c10000.zptty: tx buf size    = 128
[ 6688.962341] zptty 43c10000.zptty: rx buf size    = 128
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/fibonacci$ sudo rake install
dd if=DE0_NANO_SOC.rbf of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
1290712 bytes (1.3 MB) copied, 0.186531 s, 6.9 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-de0-nano-soc.dts
[ 1124.141145] zptty ff202000.zptty: ZPTTY Driver probe start
[ 1124.146987] zptty ff202000.zptty: driver installed
[ 1124.151768] zptty ff202000.zptty: device name    = zptty0
[ 1124.158807] zptty ff202000.zptty: private record = ee9e3200 (332bytes)
[ 1124.165893] zptty ff202000.zptty: major number   = 240
[ 1124.171015] zptty ff202000.zptty: minor number   = 0
[ 1124.177007] zptty ff202000.zptty: regs resource  = [mem 0xff202000-0xff202fff flags 0x200]
[ 1124.185780] zptty ff202000.zptty: regs address   = f217e000
[ 1124.191336] zptty ff202000.zptty: irq resource   = [irq 67 flags 0x404]
[ 1124.198906] zptty ff202000.zptty: tx buf size    = 128
[ 1124.204554] zptty ff202000.zptty: rx buf size    = 128
```


#### Run sample script

```
fpga@debian-fpga:~/examples/fibonacci$ ruby test.rb
0 => 0
1 => 1
2 => 1
3 => 2
4 => 3
5 => 5
6 => 8
7 => 13
8 => 21
9 => 34
10 => 55
11 => 89
12 => 144
13 => 233
14 => 377
15 => 610
16 => 987
17 => 1597
18 => 2584
19 => 4181
20 => 6765
21 => 10946
22 => 17711
23 => 28657
24 => 46368
25 => 75025
26 => 121393
27 => 196418
28 => 317811
29 => 514229
30 => 832040
31 => 1346269
32 => 2178309
33 => 3524578
34 => 5702887
35 => 9227465
36 => 14930352
37 => 24157817
38 => 39088169
39 => 63245986
40 => 102334155
41 => 165580141
42 => 267914296
43 => 433494437
44 => 701408733
45 => 1134903170
46 => 1836311903
47 => 2971215073
48 => 4807526976
49 => 7778742049
50 => 12586269025
51 => 20365011074
52 => 32951280099
53 => 53316291173
54 => 86267571272
55 => 139583862445
56 => 225851433717
57 => 365435296162
58 => 591286729879
59 => 956722026041
60 => 1548008755920
61 => 2504730781961
62 => 4052739537881
63 => 6557470319842
64 => 10610209857723
65 => 17167680177565
66 => 27777890035288
67 => 44945570212853
68 => 72723460248141
69 => 117669030460994
70 => 190392490709135
71 => 308061521170129
72 => 498454011879264
73 => 806515533049393
74 => 1304969544928657
75 => 2111485077978050
76 => 3416454622906707
77 => 5527939700884757
78 => 8944394323791464
79 => 14472334024676221
80 => 23416728348467685
81 => 37889062373143906
82 => 61305790721611591
83 => 99194853094755497
84 => 160500643816367088
85 => 259695496911122585
86 => 420196140727489673
87 => 679891637638612258
88 => 1100087778366101931
89 => 1779979416004714189
90 => 2880067194370816120
```

#### Uninstall Device Tree

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake uninstall
dtbocfg.rb --remove zptty0
[ 6813.229984] zptty 43c10000.zptty: driver removed
```


Build 
------------------------------------------------------------------------------------

### Build U-boot for ZYBO

There are two ways

1. run scripts/build-u-boot-zynq-zybo.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download U-boot Source

##### Clone from git.denx.de/u-boot.git

```
shell$ git clone git://git.denx.de/u-boot.git u-boot-zynq-zybo
````

##### Checkout v2016.03

```
shell$ cd u-boot-zynq-zybo
shell$ git checkout -b u-boot-2016.03-zynq-zybo refs/tags/v2016.03
```

#### Patch for zynq-zybo

```
shell$ patch -p0 < ../files/u-boot-2016.03-zynq-zybo.diff
shell$ git add --update
shell$ git commit -m "patch for zynq-zybo"
```

#### Setup for Build 

```
shell$ cd u-boot-zynq-zybo
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make zynq_zybo_defconfig
```

#### Build u-boot

```
shell$ make
```

#### Copy boot.bin and u-boot.img to zybo-zynq/boot/

```
shell$ cp spl/boot.bin  ../zynq-zybo/boot/
shell$ cp u-boot.img    ../zynq-zybo/boot/
```

### Build U-boot for DE0-Nano-SoC

There are two ways

1. run scripts/build-u-boot-de0-nano-soc.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download U-boot Source

##### Clone from git.denx.de/u-boot.git

```
shell$ git clone git://git.denx.de/u-boot.git u-boot-de0-nano-soc
````

##### Checkout v2016.03

```
shell$ cd u-boot-de0-nano-soc
shell$ git checkout -b u-boot-2016.03-de0-nano-soc refs/tags/v2016.03
```

#### Patch for de0-nano-soc

```
shell$ patch -p0 < ../files/u-boot-2016.03-de0-nano-soc.diff
shell$ git add --update
shell$ git commit -m "patch for de0-nano-soc"
```

#### Setup for Build 

```
shell$ cd u-boot-de0-nano-soc
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make socfpga_de0_nano_soc_defconfig
```

#### Build u-boot

```
shell$ make
```

#### Copy u-boot-spl.sfp and u-boot.img de0-nano-soc/u-boot/

```
shell$ cp spl/u-boot-spl.sfp ../de0-nano-soc/u-boot/u-boot-spl.sfp
shell$ cp u-boot.img         ../de0-nano-soc/u-boot/u-boot.img
```

### Build Linux Kernel

There are two ways

1. run scripts/build-linux-kernel.sh (easy)
2. run this chapter step-by-step (annoying)

#### Download Linux Kernel Source

##### Clone from linux-stable.git

```
shell$ git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux-4.4.7-armv7-fpga
```

##### Checkout v4.4.7

```
shell$ cd linux-4.4.7-armv7-fpga
shell$ git checkout -b linux-4.4.7-armv7-fpga refs/tags/v4.4.7
```

#### Patch for armv7-fpga

```
shell$ patch -p0 < ../files/linux-4.4.7-armv7-fpga.diff
shell$ git add --update
shell$ git add arch/arm/configs/armv7_fpga_defconfig
shell$ git commit -m "patch for armv7-fpga"
shell$ git tag -a v4.4.7-armv7-fpga -m "relase v4.4.7-armv7-fpga"
```

#### Setup for Build 

````
shell$ cd linux-4.4.7-armv7-fpga
shell$ export ARCH=arm
shell$ export CROSS_COMPILE=arm-linux-gnueabihf-
shell$ make armv7_fpga_defconfig
````

#### Build Linux Kernel and device tree

````
shell$ make deb-pkg
shell$ make zynq-zybo.dtb
shell$ make socfpga_cyclone5_de0_sockit.dtb
````

#### Copy zImage and devicetree to target/zybo-zynq/boot/

```
shell$ cp arch/arm/boot/zImage            ../target/zynq-zybo/boot/zImage-4.4.7-armv7-fpga
shell$ cp arch/arm/boot/dts/zynq-zybo.dtb ../target/zynq-zybo/boot/devicetree-4.4.7-zynq-zybo.dtb
shell$ dtc -I dtb -O dts -o ../target/zynq-zybo/boot/devicetree-4.4.7-zynq-zybo.dts arch/arm/boot/dts/zynq-zybo.dtb
```

#### Copy zImage and devicetree to target/de0-nano-soc/boot/

```
shell$ cp arch/arm/boot/zImage                              ../target/de0-nano-soc/boot/zImage-4.4.7-armv7-fpga
shell$ cp arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb ../target/de0-nano-soc/boot/devicetree-4.4.7-socfpga.dtb
shell$ dtc -I dtb -O dts -o ../target/de0-nano-soc/boot/devicetree-4.4.7-socfpga.dts arch/arm/boot/dts/socfpga_cyclone5_de0_sockit.dtb
```

### Build Debian8 RootFS

#### Setup parameters 

```
shell$ apt-get install qemu-user-static debootstrap binfmt-support
shell$ export targetdir=debian8-rootfs
shell$ export distro=jessie
```

#### Build the root file system in $targetdir(=debian8-rootfs)

```
shell$ mkdir $targetdir
shell$ sudo debootstrap --arch=armhf --foreign $distro                     $targetdir
shell$ sudo cp /usr/bin/qemu-arm-static                                    $targetdir/usr/bin
shell$ sudo cp /etc/resolv.conf                                            $targetdir/etc
shell$ sudo cp scripts/build-debian8-rootfs-with-qemu.sh                   $targetdir
shell$ sudo cp linux-image-4.4.7-armv7-fpga_4.4.7-armv7-fpga-1_armhf.deb   $targetdir
shell$ sudo cp linux-headers-4.4.7-armv7-fpga_4.4.7-armv7-fpga-1_armhf.deb $targetdir
````

#### Build debian8-rootfs with QEMU

##### Change Root to debian8-rootfs

```
shell$ sudo chroot $targetdir
```

There are two ways

1. run build-debian8-rootfs-with-qemu.sh (easy)
2. run this chapter step-by-step (annoying)

##### Setup APT

````
debian8-rootfs# distro=jessie
debian8-rootfs# export LANG=C
debian8-rootfs# /debootstrap/debootstrap --second-stage
````

```
debian8-rootfs# cat <<EOT > /etc/apt/sources.list
deb     http://ftp.jp.debian.org/debian            jessie         main contrib non-free
deb-src http://ftp.jp.debian.org/debian            jessie         main contrib non-free
deb     http://ftp.jp.debian.org/debian            jessie-updates main contrib non-free
deb-src http://ftp.jp.debian.org/debian            jessie-updates main contrib non-free
deb     http://security.debian.org/debian-security jessie/updates main contrib non-free
deb-src http://security.debian.org/debian-security jessie/updates main contrib non-free
EOT
```

```
debian8-rootfs# cat <<EOT > /etc/apt/apt.conf.d/71-no-recommends
APT::Install-Recommends "0";
APT::Install-Suggests   "0";
EOT
```

```
debian8-rootfs# apt-get update
```

##### Install applications

```
debian8-rootfs# apt-get install -y locales dialog
debian8-rootfs# dpkg-reconfigure locales
debian8-rootfs# apt-get install -y openssh-server ntpdate resolvconf sudo less hwinfo ntp tcsh zsh
```

##### Setup hostname

```
debian8-rootfs# echo debian-fpga > /etc/hostname
```

##### Setup root password

```
debian8-rootfs# passwd
```

This time, we set the "admin" at the root' password.

To be able to login as root from Zynq serial port.

```
debian8-rootfs# cat <<EOT >> /etc/securetty
# Seral Port for Xilinx Zynq
ttyPS0
EOT
```

##### Add a new guest user

```
debian8-rootfs# adduser fpga
```

This time, we set the "fpga" at the fpga'password.

```
debian8-rootfs# echo "fpga ALL=(ALL:ALL) ALL" > /etc/sudoers.d/fpga
```

##### Setup sshd config

```
debian8-rootfs# sed -i -e 's/#PasswordAuthentication/PasswordAuthentication/g' /etc/ssh/sshd_config
```

##### Setup Time Zone

```
debian8-rootfs# dpkg-reconfigure tzdata
```

or if noninteractive set to Asia/Tokyo

```
debian8-rootfs# echo "Asia/Tokyo" > /etc/timezone
debian8-rootfs# dpkg-reconfigure -f noninteractive tzdata
```


##### Setup fstab

```
debian8-rootfs# cat <<EOT > /etc/fstab
/dev/mmcblk0p1	/boot	auto		defaults	0	0
none		/config	configfs	defaults	0	0
EOT
````

##### Setup Network Interface

```
debian8-rootfs# cat <<EOT > /etc/network/interfaces.d/eth0
allow-hotplug eth0
iface eth0 inet dhcp
EOT
````

##### Install Development applications

```
debian8-rootfs# apt-get install -y build-essential
debian8-rootfs# apt-get install -y device-tree-compiler
debian8-rootfs# apt-get install -y u-boot-tools
debian8-rootfs# apt-get install -y ruby ruby-msgpack ruby-serialport
debian8-rootfs# gem install rake
```

##### Install Linux Header and Modules

```
debian8-rootfs# mv    boot boot.org
debian8-rootfs# mkdir boot
debian8-rootfs# dpkg -i linux-image-4.4.7-armv7-fpga_4.4.7-armv7-fpga-1_armhf.deb
debian8-rootfs# dpkg -i linux-headers-4.4.7-armv7-fpga_4.4.7-armv7-fpga-1_armhf.deb
debian8-rootfs# rm    boot/*
debian8-rootfs# rmdir boot
debian8-rootfs# mv    boot.org boot
```

##### Finish

```
debian8-rootfs# exit
shell$ sudo rm -f $targetdir/usr/bin/qemu-arm-static
shell$ sudo rm -f $targetdir/build-debian8-rootfs-with-qemu.sh
shell$ sudo rm -f $targetdir/linux-image-4.4.7-armv7-fpga_4.4.7-armv7-fpga-1_armhf.deb
shell$ sudo rm -f $targetdir/linux-headers-4.4.7-armv7-fpga_4.4.7-armv7-fpga-1_armhf.deb
```

#### Build debian8-rootfs-vanilla.tgz

```
shell$ cd $targetdir
shell$ sudo tar cfz ../debian8-rootfs-vanilla.tgz *
```

### Build Device Drivers Package

There are two ways

1. run build-fpga-linux-driver-package.sh (easy)
2. run this chapter step-by-step (annoying)

#### Donwload Sources from github

```
shell$ git clone https://github.com/ikwzm/dtbocfg
shell$ git clone https://github.com/ikwzm/fpgacfg
shell$ git clone https://github.com/ikwzm/fclkcfg
shell$ git clone https://github.com/ikwzm/udmabuf
shell$ git clone https://github.com/ikwzm/PTTY_AXI4
```

#### Copy Source Files to drivers/

```
shell$ git archive --remote dtbocfg   --prefix=dtbocfg/  --format=tar v0.0.2 | tar xf - -C drivers
shell$ git archive --remote fpgacfg   --prefix=fpgacfg/  --format=tar v0.0.1 | tar xf - -C drivers
shell$ git archive --remote fclkcfg   --prefix=fclkcfg/  --format=tar v0.0.1 | tar xf - -C drivers
shell$ git archive --remote udmabuf   --prefix=udmabuf/  --format=tar v0.5.0 | tar xf - -C drivers
shell$ cd PTTY_AXI4; git checkout v1.0.0; cp -r src/drivers/zptty ../drivers; cd ..
```

#### Build debian package

```
shell$ cd drivers
shell$ sudo debian/rule binary
```
