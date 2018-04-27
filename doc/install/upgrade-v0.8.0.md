Upgrade to v0.8.0 from previous version
------------------------------------------------------------------------------------

### Boot and login root user

root'password is "admin"

```console
debian-fpga login: root
Password:
root@debian-fpga:~#
```

### Move Boot Partition mount point from /boot to /mnt/boot

#### Move Boot Partition mount point

```console
root@debian-fpga:~# sudo unmount /boot
root@debian-fpga:~# sudo mkdir /mnt/boot
root@debian-fpga:~# sudo mount /dev/mmcblk0p1 /mnt/boot
```

#### Copy Boot Partition files to /boot

```console
root@debian-fpga:~# sudo cp /mnt/boot/* /boot
```

#### Change Boot Partition mount point of /etc/fstab

```text:/etc/fstab
/dev/mmcblk0p1	/mnt/boot	auto		defaults	0	0
none		/config		configfs	defaults	0	0
```

### Remove Old Services Package

```console
root@debian-fpga:~# dpkg --remove fpga-soc-linux-services
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

### Remove Old Device Drivers

#### Remove Old Device Drivers from Release 0.7.x

```console
root@debian-fpga:~# dpkg --remove fpga-soc-linux-drivers-4.14.21-armv7-fpga
```

#### Remove Old Device Drivers from Release 0.6.x

```console
root@debian-fpga:~# dpkg --remove fpga-soc-linux-drivers-4.14.13-armv7-fpga
```

#### Remove Old Device Drivers from Release 0.5.x

```console
root@debian-fpga:~# dpkg --remove fpga-soc-linux-drivers-4.12.14-armv7-fpga
```

#### Remove Old Device Drivers from Release 0.4.x

```console
root@debian-fpga:~# dpkg --remove fpga-soc-linux-drivers-4.12.13-armv7-fpga
```

#### Remove Old Device Drivers from Release 0.3.x

```console
root@debian-fpga:~# dpkg --remove fpga-soc-linux-drivers-4.8.17-armv7-fpga
```

### Download FPGA-SoC-Linux v0.8.0

```console
root@debian-fpga:~# git clone --depth=1 --branch v0.8.0 git://github.com/ikwzm/FPGA-SoC-Linux
root@debian-fpga:~# cd FPGA-SoC-Linux
root@debian-fpga:~/FPGA-SoC-Linux# git lfs pull
```

### Copy Debian Packages to /home/fpga/debian

```console
root@debian-fpga:~/FPGA-SoC-Linux# cp *.deb /home/fpga/debian
```

### Install files for Booting

#### ZYBO

```console
root@debian-fpga:~/FPGA-SoC-Linux# cp target/zynq-zybo/boot/*    /mnt/boot
```

#### PYNQ

```console
root@debian-fpga:~/FPGA-SoC-Linux# cp target/zynq-pynqzq/boot/*  /mnt/boot
```

#### ZYBO-Z7

```console
root@debian-fpga:~/FPGA-SoC-Linux# cp target/zynq-zybo-z7/boot/* /mnt/boot
```

#### DE0-Nano-SoC

```console
root@debian-fpga:~/FPGA-SoC-Linux# cp target/de0-nano-soc/boot/* /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux# dd if=target/de0-nano-soc/u-boot/u-boot-spl.sfp of=/dev/mmcblk0p3 bs=64k seek=0
root@debian-fpga:~/FPGA-SoC-Linux# dd if=target/de0-nano-soc/u-boot/u-boot.img     of=/dev/mmcblk0p3 bs=64k seek=4
```

#### DE10-Nano

```console
root@debian-fpga:~/FPGA-SoC-Linux# cp target/de10-nano/boot/* /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux# dd if=target/de10-nano/u-boot/u-boot-spl.sfp of=/dev/mmcblk0p3 bs=64k seek=0
root@debian-fpga:~/FPGA-SoC-Linux# dd if=target/de10-nano/u-boot/u-boot.img     of=/dev/mmcblk0p3 bs=64k seek=4
```

### Install Kernel Image and Device Drivers

[doc/install/device-drivers.md](device-drivers.md)

