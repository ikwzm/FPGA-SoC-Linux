
#### Setup APT

distro=bullseye
export LANG=C

/debootstrap/debootstrap --second-stage

cat <<EOT > /etc/apt/sources.list
deb     http://ftp.jp.debian.org/debian  bullseye           main contrib non-free
deb-src http://ftp.jp.debian.org/debian  bullseye           main contrib non-free
deb     http://ftp.jp.debian.org/debian  bullseye-updates   main contrib non-free
deb-src http://ftp.jp.debian.org/debian  bullseye-updates   main contrib non-free
deb     http://security.debian.org       bullseye-security  main contrib non-free
deb-src http://security.debian.org       bullseye-security  main contrib non-free
EOT

cat <<EOT > /etc/apt/apt.conf.d/71-no-recommends
APT::Install-Recommends "0";
APT::Install-Suggests   "0";
EOT

apt-get update  -y

#### Install Core applications

apt-get install -y locales dialog
dpkg-reconfigure locales
apt-get install -y net-tools openssh-server ntpdate resolvconf sudo less hwinfo ntp tcsh zsh file

#### Setup hostname

echo "debian-fpga" > /etc/hostname

#### Set root password

echo Set root password
passwd

cat <<EOT >> /etc/securetty
# Seral Port for Xilinx Zynq
ttyPS0
EOT

#### Add fpga user

echo Add fpga user
adduser fpga
echo "fpga ALL=(ALL:ALL) ALL" > /etc/sudoers.d/fpga

#### Setup sshd config

sed -i -e 's/#PasswordAuthentication/PasswordAuthentication/g' /etc/ssh/sshd_config

#### Setup Time Zone

dpkg-reconfigure tzdata

#### Setup fstab

cat <<EOT > /etc/fstab
/dev/mmcblk0p1	/mnt/boot	auto		defaults	0	0
none		/config		configfs	defaults	0	0
EOT

#### Setup Network

apt-get install -y ifupdown
cat <<EOT > /etc/network/interfaces.d/eth0
allow-hotplug eth0
iface eth0 inet dhcp
EOT

#### Setup /lib/firmware

mkdir /lib/firmware

#### Install Wireless tools and firmware

apt-get install -y wireless-tools
apt-get install -y wpasupplicant
apt-get install -y firmware-realtek
apt-get install -y firmware-ralink

#### Install Development applications

apt-get install -y build-essential
apt-get install -y git git-lfs
apt-get install -y u-boot-tools device-tree-compiler
apt-get install -y libssl-dev
apt-get install -y socat
apt-get install -y ruby ruby-msgpack ruby-serialport
apt-get install -y python3 python3-dev python3-setuptools python3-wheel python3-pip python3-numpy
pip3 install msgpack-rpc-python
apt-get install -y flex bison pkg-config

#### Install Other applications

apt-get install -y avahi-daemon
apt-get install -y samba

#### Install haveged for Linux Kernel 4.19

apt-get install -y haveged

#### Install Linux Modules

mkdir /mnt/boot
dpkg -i linux-image-5.10.69-armv7-fpga_5.10.69-armv7-fpga-0_armhf.deb

#### Clean Cache

apt-get clean

#### Create Debian Package List

dpkg -l > dpkg-list.txt
