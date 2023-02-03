Upgrade to v2.2.0 from v2.1.x
------------------------------------------------------------------------------------

### Boot and login root user

root'password is "admin".

```console
debian-fpga login: root
Password:
root@debian-fpga:~#
```

### Download FPGA-SoC-Linux v2.2.0

```console
root@debian-fpga:~# wget https://github.com/ikwzm/FPGA-SoC-Linux/archive/refs/tags/v2.2.0.tar.gz
root@debian-fpga:~# tar xfz v2.2.0.tar.gz
root@debian-fpga:~# cd FPGA-SoC-Linux-v2.2.0
```

### Backup /mnt/boot/uEnv.txt

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp /mnt/boot/uEnv.txt /mnt/boot/uEnv.txt.org
```

### Install files for Booting

#### ZYBO

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp vmlinuz-5.10.165-armv7-fpga /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp target/zynq-zybo/boot/*     /mnt/boot
```

#### PYNQ

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp vmlinuz-5.10.165-armv7-fpga /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp target/zynq-pynqzq/boot/*   /mnt/boot
```

#### ZYBO-Z7

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp vmlinuz-5.10.165-armv7-fpga /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp target/zynq-zybo-z7/boot/*  /mnt/boot
```

#### DE0-Nano-SoC

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp vmlinuz-5.10.165-armv7-fpga /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp target/de0-nano-soc/boot/*  /mnt/boot
```

#### DE10-Nano

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp vmlinuz-5.10.165-armv7-fpga /mnt/boot
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp target/de10-nano/boot/*     /mnt/boot
```

### Setup /mnt/boot/uEnv.txt

If /mnt/boot/uEnv.txt.org has its own settings, please reflect it in the new /mnt/boot/uEnv.txt.

### Copy Debian Packages to /home/fpga/debian

```console
root@debian-fpga:~/FPGA-SoC-Linux-v2.2.0# cp *.deb /home/fpga/debian
```

### Install Kernel Image and Device Drivers

[doc/install/device-drivers.md](device-drivers.md)

### Upgrade to Debian 11.6

```console
root@debian-fpga:~# apt update -y
root@debian-fpga:~# apt upgrade -y
```

