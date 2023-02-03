### Install Device Drivers and Services

#### Boot ZYBO/ZYBO-Z7/PYNQ-Z1/DE0-Nano-SoC/DE10-Nano and login fpga or root user

fpga'password is "fpga".

```console
debian-fpga login: fpga
Password:
fpga@debian-fpga:~$
```

root'password is "admin".

```console
debian-fpga login: root
Password:
root@debian-fpga:~#
```

#### Install Kernel Image Package

```console
fpga@debian-fpga:~/debian$ sudo apt install ./linux-image-5.10.165-armv7-fpga_5.10.165-armv7-fpga-1_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'linux-image-5.10.165-armv7-fpga' instead of './linux-image-5.10.165-armv7-fpga_5.10.165-armv7-fpga-1_armhf.deb'
linux-image-5.10.165-armv7-fpga is already the newest version (5.10.165-armv7-fpga-1).
0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.
```

#### Install dtbocfg kernel module package

```console
fpga@debian-fpga:~/debian$ sudo apt install ./dtbocfg-5.10.165-armv7-fpga_0.0.9-1_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'dtbocfg-5.10.165-armv7-fpga' instead of './dtbocfg-5.10.165-armv7-fpga_0.0.9-1_armhf.deb'
The following NEW packages will be installed:
  dtbocfg-5.10.165-armv7-fpga
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/36.0 kB of archives.
After this operation, 119 kB of additional disk space will be used.
Get:1 /home/fpga/debian/dtbocfg-5.10.165-armv7-fpga_0.0.9-1_armhf.deb dtbocfg-5.10.165-armv7-fpga armhf 0.0.9-1 [36.0 kB]
Selecting previously unselected package dtbocfg-5.10.165-armv7-fpga.
(Reading database ... 75888 files and directories currently installed.)
Preparing to unpack .../dtbocfg-5.10.165-armv7-fpga_0.0.9-1_armhf.deb ...
Unpacking dtbocfg-5.10.165-armv7-fpga (0.0.9-1) ...
Setting up dtbocfg-5.10.165-armv7-fpga (0.0.9-1) ...
```

#### Install fclkcfg kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo apt install ./fclkcfg-5.10.165-armv7-fpga_1.7.2-1_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'fclkcfg-5.10.165-armv7-fpga' instead of './fclkcfg-5.10.165-armv7-fpga_1.7.2-1_armhf.deb'
The following NEW packages will be installed:
  fclkcfg-5.10.165-armv7-fpga
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/78.2 kB of archives.
After this operation, 244 kB of additional disk space will be used.
Get:1 /home/fpga/debian/fclkcfg-5.10.165-armv7-fpga_1.7.2-1_armhf.deb fclkcfg-5.10.165-armv7-fpga armhf 1.7.2-1 [78.2 kB]
Selecting previously unselected package fclkcfg-5.10.165-armv7-fpga.
(Reading database ... 75894 files and directories currently installed.)
Preparing to unpack .../fclkcfg-5.10.165-armv7-fpga_1.7.2-1_armhf.deb ...
Unpacking fclkcfg-5.10.165-armv7-fpga (1.7.2-1) ...
Setting up fclkcfg-5.10.165-armv7-fpga (1.7.2-1) ...
```

#### Install u-dma-buf kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo apt install ./u-dma-buf-5.10.165-armv7-fpga_4.0.0-0_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'u-dma-buf-5.10.165-armv7-fpga' instead of './u-dma-buf-5.10.165-armv7-fpga_4.0.0-0_armhf.deb'
The following NEW packages will be installed:
  u-dma-buf-5.10.165-armv7-fpga
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/91.0 kB of archives.
After this operation, 285 kB of additional disk space will be used.
Get:1 /home/fpga/debian/u-dma-buf-5.10.165-armv7-fpga_4.0.0-0_armhf.deb u-dma-buf-5.10.165-armv7-fpga armhf 4.0.0-0 [91.0 kB]
Selecting previously unselected package u-dma-buf-5.10.165-armv7-fpga.
(Reading database ... 75899 files and directories currently installed.)
Preparing to unpack .../u-dma-buf-5.10.165-armv7-fpga_4.0.0-0_armhf.deb ...
Unpacking u-dma-buf-5.10.165-armv7-fpga (4.0.0-0) ...
Setting up u-dma-buf-5.10.165-armv7-fpga (4.0.0-0) ...
```

#### Install u-dma-buf-mgr kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo apt install ./u-dma-buf-mgr-5.10.165-armv7-fpga_4.0.0-0_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'u-dma-buf-mgr-5.10.165-armv7-fpga' instead of './u-dma-buf-mgr-5.10.165-armv7-fpga_4.0.0-0_armhf.deb'
The following NEW packages will be installed:
  u-dma-buf-mgr-5.10.165-armv7-fpga
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/60.3 kB of archives.
After this operation, 177 kB of additional disk space will be used.
Get:1 /home/fpga/debian/u-dma-buf-mgr-5.10.165-armv7-fpga_4.0.0-0_armhf.deb u-dma-buf-mgr-5.10.165-armv7-fpga armhf 4.0.0-0 [60.3 kB]
Selecting previously unselected package u-dma-buf-mgr-5.10.165-armv7-fpga.
(Reading database ... 75904 files and directories currently installed.)
Preparing to unpack .../u-dma-buf-mgr-5.10.165-armv7-fpga_4.0.0-0_armhf.deb ...
Unpacking u-dma-buf-mgr-5.10.165-armv7-fpga (4.0.0-0) ...
Setting up u-dma-buf-mgr-5.10.165-armv7-fpga (4.0.0-0) ...
```

#### Install zptty kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo apt install ./zptty-5.10.165-armv7-fpga_1.1.0-1_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'zptty-5.10.165-armv7-fpga' instead of './zptty-5.10.165-armv7-fpga_1.1.0-1_armhf.deb'
The following NEW packages will be installed:
  zptty-5.10.165-armv7-fpga
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/77.0 kB of archives.
After this operation, 230 kB of additional disk space will be used.
Get:1 /home/fpga/debian/zptty-5.10.165-armv7-fpga_1.1.0-1_armhf.deb zptty-5.10.165-armv7-fpga armhf 1.1.0-1 [77.0 kB]
Selecting previously unselected package zptty-5.10.165-armv7-fpga.
(Reading database ... 75909 files and directories currently installed.)
Preparing to unpack .../zptty-5.10.165-armv7-fpga_1.1.0-1_armhf.deb ...
Unpacking zptty-5.10.165-armv7-fpga (1.1.0-1) ...
Setting up zptty-5.10.165-armv7-fpga (1.1.0-1) ...
```

#### Install zynq-afi kernel module package

This debian package only installs ZYNQ(ZYBO/ZYBO-Z7/PYNQ-Z1).

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo apt install ./zynq-afi-5.10.165-armv7-fpga_0.0.1-0_armhf.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'zynq-afi-5.10.165-armv7-fpga' instead of './zynq-afi-5.10.165-armv7-fpga_0.0.1-0_armhf.deb'
The following NEW packages will be installed:
  zynq-afi-5.10.165-armv7-fpga
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/43.7 kB of archives.
After this operation, 137 kB of additional disk space will be used.
Get:1 /home/fpga/debian/zynq-afi-5.10.165-armv7-fpga_0.0.1-0_armhf.deb zynq-afi-5.10.165-armv7-fpga armhf 0.0.1-0 [43.7 kB]
Selecting previously unselected package zynq-afi-5.10.165-armv7-fpga.
(Reading database ... 75914 files and directories currently installed.)
Preparing to unpack .../zynq-afi-5.10.165-armv7-fpga_0.0.1-0_armhf.deb ...
Unpacking zynq-afi-5.10.165-armv7-fpga (0.0.1-0) ...
Setting up zynq-afi-5.10.165-armv7-fpga (0.0.1-0) ...
```

#### Install dtbocfg control package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo apt install ./dtbocfg-ctrl_0.0.5-1_all.deb
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
Note, selecting 'dtbocfg-ctrl' instead of './dtbocfg-ctrl_0.0.5-1_all.deb'
The following NEW packages will be installed:
  dtbocfg-ctrl
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 0 B/4664 B of archives.
After this operation, 24.6 kB of additional disk space will be used.
Get:1 /home/fpga/debian/dtbocfg-ctrl_0.0.5-1_all.deb dtbocfg-ctrl all 0.0.5-1 [4664 B]
Selecting previously unselected package dtbocfg-ctrl.
(Reading database ... 75920 files and directories currently installed.)
Preparing to unpack .../dtbocfg-ctrl_0.0.5-1_all.deb ...
Unpacking dtbocfg-ctrl (0.0.5-1) ...
Setting up dtbocfg-ctrl (0.0.5-1) ...
Created symlink /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service → /etc/systemd/system/device-tree-overlay.service.
[ 1158.307860] dtbocfg_module_init
[ 1158.311183] dtbocfg_module_init: OK
```

#### Check Installed Device Drivers and Services Package

```console
fpga@debian-fpga:~$ sudo lsmod
Module                  Size  Used by
dtbocfg                16384  0
```

```console
fpga@debian-fpga:~/debian$  sudo systemctl status device-tree-overlay.service
● device-tree-overlay.service - Device Tree Overlay Service.
     Loaded: loaded (/etc/systemd/system/device-tree-overlay.service; enabled; >
     Active: active (exited) since Fri 2023-02-03 10:36:00 JST; 1min 13s ago
    Process: 3729 ExecStart=/sbin/modprobe dtbocfg (code=exited, status=0/SUCCE>
   Main PID: 3729 (code=exited, status=0/SUCCESS)
        CPU: 25ms

Feb 03 10:36:00 debian-fpga systemd[1]: Starting Device Tree Overlay Service....
Feb 03 10:36:00 debian-fpga systemd[1]: Finished Device Tree Overlay Service..
```

