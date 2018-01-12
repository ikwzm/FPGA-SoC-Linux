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
fpga@debian-fpga:~/debian$ sudo dpkg -i linux-image-4.14.13-armv7-fpga_4.14.13-armv7-fpga-1_armhf.deb
(Reading database ... 61992 files and directories currently installed.)
Preparing to unpack linux-image-4.14.13-armv7-fpga_4.14.13-armv7-fpga-1_armhf.deb ...
Unpacking linux-image-4.14.13-armv7-fpga (4.14.13-armv7-fpga-1) ...
Setting up linux-image-4.14.13-armv7-fpga (4.14.13-armv7-fpga-1) ...
```

#### Install Device Drivers and Services Package

```console
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i fpga-soc-linux-drivers-4.14.13-armv7-fpga_0.1.0-1_armhf.deb
Selecting previously unselected package fpga-soc-linux-drivers-4.14.13-armv7-fpga.
(Reading database ... 62097 files and directories currently installed.)
Preparing to unpack fpga-soc-linux-drivers-4.14.13-armv7-fpga_0.1.0-1_armhf.deb ...
Unpacking fpga-soc-linux-drivers-4.14.13-armv7-fpga (0.1.0-1) ...
Setting up fpga-soc-linux-drivers-4.14.13-armv7-fpga (0.1.0-1) ...
```

```console
fpga@debian-fpga:~/debian$ cd /home/fpga/debian
fpga@debian-fpga:~/debian$ sudo dpkg -i fpga-soc-linux-services_0.0.9-1_armhf.deb
Selecting previously unselected package fpga-soc-linux-services.
(Reading database ... 42746 files and directories currently installed.)
Preparing to unpack fpga-soc-linux-services_0.0.9-1_armhf.deb ...
Unpacking fpga-soc-linux-services (0.0.9-1) ...
Setting up fpga-soc-linux-services (0.0.9-1) ...
Created symlink /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service → /etc/systemd/system/device-tree-overlay.service.
[  403.906219] systemd[1]: apt-daily-upgrade.timer: Adding 33min 27.360172s random time.
[  403.918062] systemd[1]: apt-daily.timer: Adding 11h 12min 56.053554s random time.
Created symlink /etc/systemd/system/multi-user.target.wants/udmabuf.service → /etc/systemd/system/udmabuf.service.
[  404.327393] systemd[1]: apt-daily-upgrade.timer: Adding 42min 35.340818s random time.
[  404.339211] systemd[1]: apt-daily.timer: Adding 9h 23min 10.482115s random time.
Created symlink /etc/systemd/system/multi-user.target.wants/fpga-clock.service  → /etc/systemd/system/fpga-clock.service.
[  404.745385] systemd[1]: apt-daily-upgrade.timer: Adding 50min 4.974227s random time.
[  404.757136] systemd[1]: apt-daily.timer: Adding 3h 26min 46.127644s random time.
Created symlink /etc/systemd/system/multi-user.target.wants/zptty.service → /etc/systemd/system/zptty.service.
[  405.176330] systemd[1]: apt-daily-upgrade.timer: Adding 21min 31.965437s random time.
[  405.188405] systemd[1]: apt-daily.timer: Adding 20min 1.691993s random time.
[  405.279856] dtbocfg_module_init
[  405.283061] dtbocfg_module_init: OK
```

#### Check Installed Device Drivers and Services Package

```console
fpga@debian-fpga:~$ sudo lsmod
Module                  Size  Used by
zptty                  16384  0
fclkcfg                16384  0
udmabuf                20480  0
dtbocfg                16384  0
```

```console
fpga@debian-fpga:~/debian$ sudo systemctl status device-tree-overlay.service
● device-tree-overlay.service - Device Tree Overlay Service.
   Loaded: loaded (/etc/systemd/system/device-tree-overlay.service; enabled)
   Active: active (exited) since Tue 2017-02-21 23:03:05 JST; 1min 19s ago
  Process: 1665 ExecStart=/sbin/modprobe dtbocfg (code=exited, status=0/SUCCESS)
 Main PID: 1665 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/device-tree-overlay.service

Feb 21 23:03:05 debian-fpga systemd[1]: Started Device Tree Overlay Service..
```

```console
fpga@debian-fpga:~/debian$ sudo systemctl status udmabuf.service
● udmabuf.service - User space mappable DMA Buffer Service.
   Loaded: loaded (/etc/systemd/system/udmabuf.service; enabled)
   Active: active (exited) since Tue 2017-02-21 23:03:06 JST; 4min 26s ago
  Process: 1687 ExecStart=/sbin/modprobe udmabuf (code=exited, status=0/SUCCESS)
 Main PID: 1687 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/udmabuf.service

Feb 21 23:03:06 debian-fpga systemd[1]: Started User space mappable DMA Buff....
Hint: Some lines were ellipsized, use -l to show in full.
```

```console
fpga@debian-fpga:~/debian$ sudo systemctl status zptty.service
● zptty.service - Pseudo TTY Driver for communication with FPGA.
   Loaded: loaded (/etc/systemd/system/zptty.service; enabled)
   Active: active (exited) since Tue 2017-02-21 23:03:06 JST; 5min ago
  Process: 1694 ExecStart=/sbin/modprobe zptty (code=exited, status=0/SUCCESS)
 Main PID: 1694 (code=exited, status=0/SUCCESS)

Feb 21 23:03:06 debian-fpga systemd[1]: Started Pseudo TTY Driver for commun....
Hint: Some lines were ellipsized, use -l to show in full.
```

