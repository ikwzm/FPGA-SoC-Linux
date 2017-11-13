### Install Device Drivers and Services

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

#### Install Linux Headers Package

```
fpga@debian-fpga:~$ sudo dpkg -i linux-image-4.12.14-armv7-fpga_4.12.14-armv7-fpga-3_armhf.deb
fpga@debian-fpga:~$ sudo dpkg -i linux-headers-4.12.14-armv7-fpga_4.12.14-armv7-fpga-3_armhf.deb
```

#### Install Device Drivers and Services Package

```
fpga@debian-fpga:~$ sudo dpkg -i fpga-soc-linux-drivers-4.12.14-armv7-fpga_0.0.7-1_armhf.deb
Selecting previously unselected package fpga-soc-linux-drivers-4.12.14-armv7-fpga.
(Reading database ... 39197 files and directories currently installed.)
Preparing to unpack fpga-soc-linux-drivers-4.12.14-armv7-fpga_0.0.7-1_armhf.deb ...
Unpacking fpga-soc-linux-drivers-4.12.14-armv7-fpga (0.0.7-1) ...
Setting up fpga-soc-linux-drivers-4.12.14-armv7-fpga (0.0.7-1) ...
```

```
fpga@debian-fpga:~$ sudo dpkg -i fpga-soc-linux-services_0.0.7-1_armhf.deb
Selecting previously unselected package fpga-soc-linux-services.
(Reading database ... 39210 files and directories currently installed.)
Preparing to unpack fpga-soc-linux-services_0.0.5-1_armhf.deb ...
Unpacking fpga-soc-linux-services (0.0.7-1) ...
Setting up fpga-soc-linux-services (0.0.7-1) ...
Created symlink from /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service to /etc/systemd/system/device-tree-overlay.service.
Created symlink from /etc/systemd/system/multi-user.target.wants/udmabuf.service to /etc/systemd/system/udmabuf.service.
Created symlink from /etc/systemd/system/multi-user.target.wants/zptty.service to /etc/systemd/system/zptty.service.
```

#### Check Installed Device Drivers and Services Package

```
fpga@debian-fpga:~$ sudo lsmod
Module                  Size  Used by
zptty                   8529  0
udmabuf                10177  0
dtbocfg                 3200  2
```

```
fpga@debian-fpga:~$ sudo systemctl status device-tree-overlay.service
● device-tree-overlay.service - Device Tree Overlay Service.
   Loaded: loaded (/etc/systemd/system/device-tree-overlay.service; enabled)
   Active: active (exited) since Tue 2017-02-21 23:03:05 JST; 1min 19s ago
  Process: 1665 ExecStart=/sbin/modprobe dtbocfg (code=exited, status=0/SUCCESS)
 Main PID: 1665 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/device-tree-overlay.service

Feb 21 23:03:05 debian-fpga systemd[1]: Started Device Tree Overlay Service..
```

```
fpga@debian-fpga:~$ sudo systemctl status udmabuf.service
● udmabuf.service - User space mappable DMA Buffer Service.
   Loaded: loaded (/etc/systemd/system/udmabuf.service; enabled)
   Active: active (exited) since Tue 2017-02-21 23:03:06 JST; 4min 26s ago
  Process: 1687 ExecStart=/sbin/modprobe udmabuf (code=exited, status=0/SUCCESS)
 Main PID: 1687 (code=exited, status=0/SUCCESS)
   CGroup: /system.slice/udmabuf.service

Feb 21 23:03:06 debian-fpga systemd[1]: Started User space mappable DMA Buff....
Hint: Some lines were ellipsized, use -l to show in full.
```

```
fpga@debian-fpga:~$ sudo systemctl status zptty.service
● zptty.service - Pseudo TTY Driver for communication with FPGA.
   Loaded: loaded (/etc/systemd/system/zptty.service; enabled)
   Active: active (exited) since Tue 2017-02-21 23:03:06 JST; 5min ago
  Process: 1694 ExecStart=/sbin/modprobe zptty (code=exited, status=0/SUCCESS)
 Main PID: 1694 (code=exited, status=0/SUCCESS)

Feb 21 23:03:06 debian-fpga systemd[1]: Started Pseudo TTY Driver for commun....
Hint: Some lines were ellipsized, use -l to show in full.
```

