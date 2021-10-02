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
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i linux-image-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb
Selecting previously unselected package linux-image-5.10.69-armv7-fpga.
(Reading database ... 26040 files and directories currently installed.)
Preparing to unpack linux-image-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb ...
Unpacking linux-image-5.10.69-armv7-fpga (5.10.69-armv7-fpga-0) ...
Setting up linux-image-5.10.69-armv7-fpga (5.10.69-armv7-fpga-0) ...
```

#### Install dtbocfg kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i dtbocfg-5.10.69-armv7-fpga_0.0.9-1_armhf.deb
Selecting previously unselected package dtbocfg-5.10.69-armv7-fpga.
(Reading database ... 42610 files and directories currently installed.)
Preparing to unpack dtbocfg-5.10.69-armv7-fpga_0.0.9-1_armhf.deb ...
Unpacking dtbocfg-5.10.69-armv7-fpga (0.0.9-1) ...
Setting up dtbocfg-5.10.69-armv7-fpga (0.0.9-1) ...
```

#### Install fclkcfg kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i fclkcfg-5.10.69-armv7-fpga_1.7.2-1_armhf.deb
Selecting previously unselected package fclkcfg-5.10.69-armv7-fpga.
(Reading database ... 42616 files and directories currently installed.)
Preparing to unpack fclkcfg-5.10.69-armv7-fpga_1.7.2-1_armhf.deb ...
Unpacking fclkcfg-5.10.69-armv7-fpga (1.7.2-1) ...
Setting up fclkcfg-5.10.69-armv7-fpga (1.7.2-1) ...
```

#### Install u-dma-buf kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i u-dma-buf-5.10.69-armv7-fpga_3.2.4-0_armhf.deb
Selecting previously unselected package u-dma-buf-5.10.69-armv7-fpga.
(Reading database ... 42621 files and directories currently installed.)
Preparing to unpack u-dma-buf-5.10.69-armv7-fpga_3.2.4-0_armhf.deb ...
Unpacking u-dma-buf-5.10.69-armv7-fpga (3.2.4-0) ...
Setting up u-dma-buf-5.10.69-armv7-fpga (3.2.4-0) ...
```

#### Install zptty kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i zptty-5.10.69-armv7-fpga_1.0.0-1_armhf.deb
Selecting previously unselected package zptty-5.10.69-armv7-fpga.
(Reading database ... 42626 files and directories currently installed.)
Preparing to unpack zptty-5.10.69-armv7-fpga_1.0.0-1_armhf.deb ...
Unpacking zptty-5.10.69-armv7-fpga (1.0.0-1) ...
Setting up zptty-5.10.69-armv7-fpga (1.0.0-1) ...
```

#### Install zynq-afi kernel module package

This debian package only installs ZYNQ(ZYBO/ZYBO-Z7/PYNQ-Z1).

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i zynq-afi-5.10.69-armv7-fpga_0.0.1-0_armhf.deb
Selecting previously unselected package zynq-afi-5.10.69-armv7-fpga.
(Reading database ... 42631 files and directories currently installed.)
Preparing to unpack zynq-afi-5.10.69-armv7-fpga_0.0.1-0_armhf.deb ...
Unpacking zynq-afi-5.10.69-armv7-fpga (0.0.1-0) ...
Setting up zynq-afi-5.10.69-armv7-fpga (0.0.1-0) ...
```

#### Install dtbocfg control package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i dtbocfg-ctrl_0.0.5-1_all.deb
Selecting previously unselected package dtbocfg-ctrl.
(Reading database ... 42637 files and directories currently installed.)
Preparing to unpack dtbocfg-ctrl_0.0.5-1_all.deb ...
Unpacking dtbocfg-ctrl (0.0.5-1) ...
Setting up dtbocfg-ctrl (0.0.5-1) ...
Created symlink /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service → /etc/systemd/system/device-tree-overlay.service.
[   48.630237] dtbocfg: loading out-of-tree module taints kernel.
[   48.636735] dtbocfg_module_init
[   48.639940] dtbocfg_module_init: OK
```

#### Check Installed Device Drivers and Services Package

```console
fpga@debian-fpga:~$ sudo lsmod
Module                  Size  Used by
dtbocfg                16384  0
```

```console
fpga@debian-fpga:~/debian$ sudo systemctl status device-tree-overlay.service
sudo: unable to resolve host debian-fpga: Name or service not known
● device-tree-overlay.service - Device Tree Overlay Service.
     Loaded: loaded (/etc/systemd/system/device-tree-overlay.service; enabled; >
     Active: active (exited) since Wed 2021-07-14 02:30:10 JST; 2 months 19 day>
    Process: 1580 ExecStart=/sbin/modprobe dtbocfg (code=exited, status=0/SUCCE>
   Main PID: 1580 (code=exited, status=0/SUCCESS)
        CPU: 31ms

Jul 14 02:30:10 debian-fpga systemd[1]: Starting Device Tree Overlay Service....
Jul 14 02:30:10 debian-fpga systemd[1]: Finished Device Tree Overlay Service..
```

