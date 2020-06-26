### Install Device Drivers and Services

#### Boot ZYBO or DE0-Nano-SoC and login fpga or root user

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
fpga@debian-fpga:~/debian$ sudo dpkg -i linux-image-5.4.47-armv7-fpga_5.4.47-armv7-fpga-0_armhf.deb
Selecting previously unselected package linux-image-5.4.47-armv7-fpga.
(Reading database ... 64174 files and directories currently installed.)
Preparing to unpack linux-image-5.4.47-armv7-fpga_5.4.47-armv7-fpga-0_armhf.deb ...
Unpacking linux-image-5.4.47-armv7-fpga (5.4.47-armv7-fpga-0) ...
Setting up linux-image-5.4.47-armv7-fpga (5.4.47-armv7-fpga-0) ...
```

#### Install dtbocfg kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i dtbocfg-5.4.47-armv7-fpga_0.0.8-1_armhf.deb
Selecting previously unselected package dtbocfg-5.4.47-armv7-fpga.
(Reading database ... 64390 files and directories currently installed.)
Preparing to unpack dtbocfg-5.4.47-armv7-fpga_0.0.8-1_armhf.deb ...
Unpacking dtbocfg-5.4.47-armv7-fpga (0.0.8-1) ...
Setting up dtbocfg-5.4.47-armv7-fpga (0.0.8-1) ...
```

#### Install fclkcfg kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i fclkcfg-5.4.47-armv7-fpga_1.2.0-1_armhf.deb
Selecting previously unselected package fclkcfg-5.4.47-armv7-fpga.
(Reading database ... 64396 files and directories currently installed.)
Preparing to unpack fclkcfg-5.4.47-armv7-fpga_1.2.0-1_armhf.deb ...
Unpacking fclkcfg-5.4.47-armv7-fpga (1.2.0-1) ...
Setting up fclkcfg-5.4.47-armv7-fpga (1.2.0-1) ...
```

#### Install u-dma-buf kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ udo dpkg -i u-dma-buf-5.4.47-armv7-fpga_3.0.1-0_armhf.deb
Selecting previously unselected package u-dma-buf-5.4.47-armv7-fpga.
(Reading database ... 64401 files and directories currently installed.)
Preparing to unpack u-dma-buf-5.4.47-armv7-fpga_3.0.1-0_armhf.deb ...
Unpacking u-dma-buf-5.4.47-armv7-fpga (3.0.1-0) ...
Setting up u-dma-buf-5.4.47-armv7-fpga (3.0.1-0) ...
```

#### Install zptty kernel module package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i zptty-5.4.47-armv7-fpga_1.0.0-1_armhf.deb
Selecting previously unselected package zptty-5.4.47-armv7-fpga.
(Reading database ... 64406 files and directories currently installed.)
Preparing to unpack zptty-5.4.47-armv7-fpga_1.0.0-1_armhf.deb ...
Unpacking zptty-5.4.47-armv7-fpga (1.0.0-1) ...
Setting up zptty-5.4.47-armv7-fpga (1.0.0-1) ...
```

#### Install dtbocfg control package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i dtbocfg-ctrl_0.0.5-1_all.deb
(Reading database ... 94225 files and directories currently installed.)
Preparing to unpack dtbocfg-ctrl_0.0.5-1_all.deb ...
Removed /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service.
[ 2585.357805] systemd[1]: apt-daily-upgrade.timer: Adding 33min 33.391369s random time.
[ 2585.369573] systemd[1]: apt-daily.timer: Adding 3h 6min 23.779244s random time.
Unpacking dtbocfg-ctrl (0.0.5-1) over (0.0.5-1) ...
Setting up dtbocfg-ctrl (0.0.5-1) ...
Created symlink /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service → /etc/systemd/system/device-tree-overlay.service.
[ 2586.021204] systemd[1]: apt-daily-upgrade.timer: Adding 25min 37.588039s random time.
[ 2586.032858] systemd[1]: apt-daily.timer: Adding 1h 39min 25.182099s random time.
[ 2586.126863] dtbocfg: loading out-of-tree module taints kernel.
[ 2586.133337] dtbocfg_module_init
[ 2586.140904] dtbocfg_module_init: OK
```

#### Check Installed Device Drivers and Services Package

```console
fpga@debian-fpga:~$ sudo lsmod
Module                  Size  Used by
dtbocfg                16384  0
```

```console
fpga@debian-fpga:~/debian$ sudo systemctl status device-tree-overlay.service
● device-tree-overlay.service - Device Tree Overlay Service.
   Loaded: loaded (/etc/systemd/system/device-tree-overlay.service; enabled; ven
   Active: active (exited) since Fri 2018-04-13 15:29:12 JST; 2min 7s ago
  Process: 2863 ExecStart=/sbin/modprobe dtbocfg (code=exited, status=0/SUCCESS)
 Main PID: 2863 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/device-tree-overlay.service
Apr 13 15:29:12 debian-fpga systemd[1]: Starting Device Tree Overlay Service..
Apr 13 15:29:12 debian-fpga systemd[1]: Started Device Tree Overlay Service..
```

