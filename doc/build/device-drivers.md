### Build Device Drivers and Services Package

#### dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v0.0.9 https://github.com/ikwzm/dtbocfg-kmod-dpkg
shell$ cd dtbocfg-kmod-dpkg
```
##### Cross Compile for linux-5.10.109-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=5.10.109-armv7-fpga kernel_src_dir=$PWD/../linux-5.10.109-armv7-fpga binary
    :
    :
    :
shell$ file ../dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb 
../dtbocfg-5.10.109-armv7-fpga_0.0.9-1_armhf.deb: Debian binary package (format 2.0)
```

#### u-dma-buf-5.10.109-armv7-fpga_3.2.5-0_armhf.deb 

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v3.2.5 https://github.com/ikwzm/u-dma-buf-kmod-dpkg
shell$ cd u-dma-buf-kmod-dpkg
```

##### Cross Compile for linux-5.10.109-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=5.10.109-armv7-fpga kernel_src_dir=$PWD/../linux-5.10.109-armv7-fpga binary
    :
    :
    :
shell$ file ../u-dma-buf-5.10.109-armv7-fpga_3.2.5-0_armhf.deb 
../u-dma-buf-5.10.109-armv7-fpga_3.2.4-0_armhf.deb: Debian binary package (format 2.0)
```

#### fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v1.7.2 https://github.com/ikwzm/fclkcfg-kmod-dpkg
shell$ cd fclkcfg-kmod-dpkg
```

##### Cross Compile for linux-5.10.109-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=5.10.109-armv7-fpga kernel_src_dir=$PWD/../linux-5.10.109-armv7-fpga binary
    :
    :
    :
shell$ file ../fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb 
../fclkcfg-5.10.109-armv7-fpga_1.7.2-1_armhf.deb: Debian binary package (format 2.0)
```

#### zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v1.1.0 https://github.com/ikwzm/zptty-kmod-dpkg
shell$ cd zptty-kmod-dpkg
```

##### Cross Compile for linux-5.10.109-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=5.10.109-armv7-fpga kernel_src_dir=$PWD/../linux-5.10.109-armv7-fpga binary
    :
    :
    :
shell$ file ../zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb
.../zptty-5.10.109-armv7-fpga_1.1.0-1_armhf.deb: Debian binary package (format 2.0)
```

#### zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb

##### Download repository

```console
shell$ git clone --recursive --depth=1 -b v0.0.1 https://github.com/ikwzm/zynq-afi-kmod-dpkg
shell$ cd zynq-afi-kmod-dpkg
```
##### Cross Compile for linux-5.10.109-armv7-fpga

```console
shell$ sudo debian/rules arch=arm deb_arch=armhf kernel_release=5.10.109-armv7-fpga kernel_src_dir=$PWD/../linux-5.10.109-armv7-fpga binary
    :
    :
    :
shell$ file ../zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb 
../zynq-afi-5.10.109-armv7-fpga_0.0.1-0_armhf.deb: Debian binary package (format 2.0)
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

