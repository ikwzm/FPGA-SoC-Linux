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
shell$ sudo debootstrap --arch=armhf --foreign $distro                         $targetdir
shell$ sudo cp /usr/bin/qemu-arm-static                                        $targetdir/usr/bin
shell$ sudo cp /etc/resolv.conf                                                $targetdir/etc
shell$ sudo cp scripts/build-debian8-rootfs-with-qemu.sh                       $targetdir
shell$ sudo cp linux-image-4.12.13-armv7-fpga_4.12.13-armv7-fpga-1_armhf.deb   $targetdir
shell$ sudo cp linux-headers-4.12.13-armv7-fpga_4.12.13-armv7-fpga-1_armhf.deb $targetdir
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
debian8-rootfs# apt-get install -y avahi-daemon
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

##### Setup /lib/firmware

debian8-rootfs# mkdir /lib/firmware

##### Install Development applications

```
debian8-rootfs# apt-get install -y build-essential
debian8-rootfs# apt-get install -y git
debian8-rootfs# apt-get install -y u-boot-tools
debian8-rootfs# apt-get install -y socat
debian8-rootfs# apt-get install -y ruby ruby-msgpack ruby-serialport
debian8-rootfs# gem install rake
debian8-rootfs# apt-get install -y python  python-dev  python-pip
debian8-rootfs# apt-get install -y python3 python3-dev python3-pip
debian8-rootfs# pip3 install msgpack-rpc-python
debian8-rootfs# pip3 install jupyter
```

##### Install Device Tree Compiler (supported symbol version)

```
debian8-rootfs# apt-get install -y flex bison
debian8-rootfs# cd root
debian8-rootfs# mkdir src
debian8-rootfs# cd src
debian8-rootfs# git clone https://git.kernel.org/pub/scm/utils/dtc/dtc.git dtc
debian8-rootfs# cd dtc
debian8-rootfs# make
debian8-rootfs# make HOME=/usr/local install-bin
debian8-rootfs# cd /
```

##### Install Other applications

```
debian8-rootfs# apt-get install -y samba
debian8-rootfs# apt-get install -y avahi-daemon
```

##### Install Linux Header and Modules

```
debian8-rootfs# mv    boot boot.org
debian8-rootfs# mkdir boot
debian8-rootfs# dpkg -i linux-image-4.12.13-armv7-fpga_4.12.13-armv7-fpga-1_armhf.deb
debian8-rootfs# dpkg -i linux-headers-4.12.13-armv7-fpga_4.12.13-armv7-fpga-1_armhf.deb
debian8-rootfs# rm    boot/*
debian8-rootfs# rmdir boot
debian8-rootfs# mv    boot.org boot
```

##### Finish

```
debian8-rootfs# exit
shell$ sudo rm -f $targetdir/usr/bin/qemu-arm-static
shell$ sudo rm -f $targetdir/build-debian8-rootfs-with-qemu.sh
shell$ sudo rm -f $targetdir/linux-image-4.12.13-armv7-fpga_4.12.13-armv7-fpga-1_armhf.deb
shell$ sudo rm -f $targetdir/linux-headers-4.12.13-armv7-fpga_4.12.13-armv7-fpga-1_armhf.deb
```

#### Build debian8-rootfs-vanilla.tgz

```
shell$ cd $targetdir
shell$ sudo tar cfz ../debian8-rootfs-vanilla.tgz *
```

