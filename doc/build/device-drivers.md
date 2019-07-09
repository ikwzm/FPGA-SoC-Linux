### Build Device Drivers and Services Package

#### dtbocfg-4.19.57-armv7-fpga_0.0.6-1_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v0.0.7 git://github.com/ikwzm/dtbocfg-kmod-dpkg
shell$ cd dtbocfg-kmod-dpkg
```
##### Cross Compile for linux-4.19.57-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=4.19.57-armv7-fpga kernel_src_dir=../../linux-4.19.57-armv7-fpga binary
    :
    :
    :
shell$ file ../dtbocfg-4.19.57-armv7-fpga_0.0.7-1_armhf.deb 
../dtbocfg-4.19.57-armv7-fpga_0.0.7-1_armhf.deb: Debian binary package (format 2.0)
```

#### udmabuf-4.19.57-armv7-fpga_1.4.1-1_armhf.deb 

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v1.4.1 git://github.com/ikwzm/udmabuf-kmod-dpkg
shell$ cd udmabuf-kmod-dpkg
```

##### Cross Compile for linux-4.19.57-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=4.19.57-armv7-fpga kernel_src_dir=../../linux-4.19.57-armv7-fpga binary
    :
    :
    :
shell$ file ../udmabuf-4.19.57-armv7-fpga_1.4.1-1_armhf.deb 
../udmabuf-4.19.57-armv7-fpga_1.4.1-1_armhf.deb: Debian binary package (format 2.0)
```

#### fclkcfg-4.19.57-armv7-fpga_1.1.0-1_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v1.1.0 git://github.com/ikwzm/fclkcfg-kmod-dpkg
shell$ cd fclkcfg-kmod-dpkg
```

##### Cross Compile for linux-4.19.57-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=4.19.57-armv7-fpga kernel_src_dir=../../linux-4.19.57-armv7-fpga binary
    :
    :
    :
shell$ file ../fclkcfg-4.19.57-armv7-fpga_1.1.0-1_armhf.deb 
../fclkcfg-4.19.57-armv7-fpga_1.1.0-1_armhf.deb: Debian binary package (format 2.0)
```

#### zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v1.0.0 git://github.com/ikwzm/zptty-kmod-dpkg
shell$ cd zptty-kmod-dpkg
```

##### Cross Compile for linux-4.19.57-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=4.19.57-armv7-fpga kernel_src_dir=../../../../../linux-4.19.57-armv7-fpga binary
    :
    :
    :
shell$ file ../zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb
../zptty-4.19.57-armv7-fpga_1.0.0-1_armhf.deb: Debian binary package (format 2.0)
```

#### dtbocfg-ctrl_0.0.5-1_all.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v0.0.5 git://github.com/ikwzm/dtbocfg-ctrl-dpkg
shell$ cd dtbocfg-ctrl-dpkg
```

##### Build

```console
shell$ sudo debian/rules binary
    :
    :
    :
shell$ file ../dtbocfg-ctrl_0.0.5-1_all.deb 
../dtbocfg-ctrl_0.0.5-1_all.deb: Debian binary package (format 2.0)
```

