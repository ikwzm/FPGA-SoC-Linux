### Upgrade to v0.5.4 from v0.5.3

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

#### Remove Old Services Package

```
fpga@debian-fpga:~$ sudo dpkg --remove fpga-soc-linux-services
(Reading database ... 42754 files and directories currently installed.)
Removing fpga-soc-linux-services (0.0.7-1) ...
Removed /etc/systemd/system/multi-user.target.wants/zptty.service.
[   53.753171] systemd[1]: apt-daily-upgrade.timer: Adding 11min 43.270095s random time.
[   53.765507] systemd[1]: apt-daily.timer: Adding 36min 25.436252s random time.
Removed /etc/systemd/system/multi-user.target.wants/udmabuf.service.
[   54.235643] systemd[1]: apt-daily-upgrade.timer: Adding 55.242551s random time.
[   54.247159] systemd[1]: apt-daily.timer: Adding 9h 13min 49.218879s random time.
Removed /etc/systemd/system/multi-user.target.wants/device-tree-overlay.service.
[   54.676455] systemd[1]: apt-daily-upgrade.timer: Adding 52min 48.054844s random time.
[   54.688334] systemd[1]: apt-daily.timer: Adding 6h 36min 45.912649s random time.
```

#### Remove Old Device Drivers

```
fpga@debian-fpga:~$ sudo dpkg --remove fpga-soc-linux-drivers-4.12.14-armv7-fpga
(Reading database ... 42746 files and directories currently installed.)
Removing fpga-soc-linux-drivers-4.12.14-armv7-fpga (0.0.8-1) ...
```

#### Install New Device Drivers

```
fpga@debian-fpga:~$ cd /home/fpga/debian
fpga@debian-fpga:~$ sudo dpkg -i fpga-soc-linux-drivers-4.12.14-armv7-fpga_0.0.9-1_armhf.deb
Selecting previously unselected package fpga-soc-linux-drivers-4.12.14-armv7-fpga.
(Reading database ... 39197 files and directories currently installed.)
Preparing to unpack fpga-soc-linux-drivers-4.12.14-armv7-fpga_0.0.9-1_armhf.deb ...
Unpacking fpga-soc-linux-drivers-4.12.14-armv7-fpga (0.0.9-1) ...
Setting up fpga-soc-linux-drivers-4.12.14-armv7-fpga (0.0.9-1) ...
```

#### Install New Services Package


```
fpga@debian-fpga:~$ cd /home/fpga/debian
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

