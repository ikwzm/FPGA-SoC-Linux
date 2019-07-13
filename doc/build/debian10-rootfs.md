### Build Debian10 RootFS

#### Setup parameters 

```console
shell$ apt-get install qemu-user-static debootstrap binfmt-support
shell$ export targetdir=debian10-rootfs
shell$ export distro=buster
```

#### Build the root file system in $targetdir(=debian10-rootfs)

```console
shell$ mkdir $targetdir
shell$ sudo debootstrap --arch=armhf --foreign $distro                         $targetdir
shell$ sudo cp /usr/bin/qemu-arm-static                                        $targetdir/usr/bin
shell$ sudo cp /etc/resolv.conf                                                $targetdir/etc
shell$ sudo cp scripts/build-debian10-rootfs-with-qemu.sh                      $targetdir
shell$ sudo cp linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb   $targetdir
````

#### Build debian10-rootfs with QEMU

##### Change Root to debian10-rootfs

```console
shell$ sudo chroot $targetdir
```

There are two ways

1. run build-debian10-rootfs-with-qemu.sh (easy)
2. run this chapter step-by-step (annoying)

##### Setup APT

````console
debian10-rootfs# distro=buster
debian10-rootfs# export LANG=C
debian10-rootfs# /debootstrap/debootstrap --second-stage
````

```console
debian10-rootfs# cat <<EOT > /etc/apt/sources.list
deb     http://ftp.jp.debian.org/debian            buster         main contrib non-free
deb-src http://ftp.jp.debian.org/debian            buster         main contrib non-free
deb     http://ftp.jp.debian.org/debian            buster-updates main contrib non-free
deb-src http://ftp.jp.debian.org/debian            buster-updates main contrib non-free
deb     http://security.debian.org/debian-security buster/updates main contrib non-free
deb-src http://security.debian.org/debian-security buster/updates main contrib non-free
EOT
```

```console
debian10-rootfs# cat <<EOT > /etc/apt/apt.conf.d/71-no-recommends
APT::Install-Recommends "0";
APT::Install-Suggests   "0";
EOT
```

```console
debian10-rootfs# apt-get update
```

##### Install applications

```console
debian10-rootfs# apt-get install -y locales dialog
debian10-rootfs# dpkg-reconfigure locales
debian10-rootfs# apt-get install -y net-tools openssh-server ntpdate resolvconf sudo less hwinfo ntp tcsh zsh file
```

##### Setup hostname

```console
debian10-rootfs# echo debian-fpga > /etc/hostname
```

##### Setup root password

```console
debian10-rootfs# passwd
```

This time, we set the "admin" at the root' password.

To be able to login as root from Zynq serial port.

```console
debian10-rootfs# cat <<EOT >> /etc/securetty
# Seral Port for Xilinx Zynq
ttyPS0
EOT
```

##### Add a new guest user

```console
debian10-rootfs# adduser fpga
```

This time, we set the "fpga" at the fpga'password.

```console
debian10-rootfs# echo "fpga ALL=(ALL:ALL) ALL" > /etc/sudoers.d/fpga
```

##### Setup sshd config

```console
debian10-rootfs# sed -i -e 's/#PasswordAuthentication/PasswordAuthentication/g' /etc/ssh/sshd_config
```

##### Setup Time Zone

```console
debian10-rootfs# dpkg-reconfigure tzdata
```

or if noninteractive set to Asia/Tokyo

```console
debian10-rootfs# echo "Asia/Tokyo" > /etc/timezone
debian10-rootfs# dpkg-reconfigure -f noninteractive tzdata
```


##### Setup fstab

```console
debian10-rootfs# cat <<EOT > /etc/fstab
/dev/mmcblk0p1	/mnt/boot	auto		defaults	0	0
none		/config		configfs	defaults	0	0
EOT
````

##### Setup Network Interface

```console
debian10-rootfs# cat <<EOT > /etc/network/interfaces.d/eth0
allow-hotplug eth0
iface eth0 inet dhcp
EOT
````

##### Setup /lib/firmware

```console
debian10-rootfs# mkdir /lib/firmware
```

##### Install Wireless tools and firmware

```console
debian10-rootfs# apt-get install -y wireless-tools
debian10-rootfs# apt-get install -y wpasupplicant
debian10-rootfs# apt-get install -y firmware-realtek
debian10-rootfs# apt-get install -y firmware-ralink
```

##### Install Development applications

```console
debian10-rootfs# apt-get install -y build-essential
debian10-rootfs# apt-get install -y git
debian10-rootfs# apt-get install -y u-boot-tools
debian10-rootfs# apt-get install -y libssl-dev
debian10-rootfs# apt-get install -y socat
debian10-rootfs# apt-get install -y ruby rake ruby-msgpack ruby-serialport 
debian10-rootfs# apt-get install -y python  python-dev  python-setuptools  python-wheel  python-pip
debian10-rootfs# apt-get install -y python3 python3-dev python3-setuptools python3-wheel python3-pip python3-numpy
debian10-rootfs# pip3 install msgpack-rpc-python
```

##### Install Device Tree Compiler (supported symbol version)

```console
debian10-rootfs# apt-get install -y flex bison pkg-config
debian10-rootfs# cd root
debian10-rootfs# mkdir src
debian10-rootfs# cd src
debian10-rootfs# git clone https://git.kernel.org/pub/scm/utils/dtc/dtc.git dtc
debian10-rootfs# cd dtc
debian10-rootfs# make
debian10-rootfs# make HOME=/usr/local install-bin
debian10-rootfs# cd /
```

##### Install Other applications

```console
debian10-rootfs# apt-get install -y samba
debian10-rootfs# apt-get install -y avahi-daemon
```

##### Install haveged for Linux Kernel 4.19

```console
debian10-rootfs# apt-get install -y haveged
```

##### Install Linux Modules

```console
debian10-rootfs# mkdir /mnt/boot
debian10-rootfs# dpkg -i linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb
```

##### Clean Cache

```console
debian10-rootfs# apt-get clean
```

##### Create Debian Package List

```console
debian10-rootfs# dpkg -l > dpkg-list.txt
```

##### Finish

```console
debian10-rootfs# exit
shell$ sudo rm -f $targetdir/usr/bin/qemu-arm-static
shell$ sudo rm -f $targetdir/build-debian10-rootfs-with-qemu.sh
shell$ sudo rm -f $targetdir/linux-image-4.19.57-armv7-fpga_4.19.57-armv7-fpga-0_armhf.deb
shell$ sudo mv    $targetdir/dpkg-list.txt files/debian10-dpkg-list.txt
```

#### Build debian10-rootfs-vanilla.tgz

```console
shell$ cd $targetdir
shell$ sudo tar cfz ../debian10-rootfs-vanilla.tgz *
```

