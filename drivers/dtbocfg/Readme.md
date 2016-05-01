Device Tree Blob Overlay Configuration File System
==================================================

# はじめに

## Device Tree Overlay とは

Linux には何時の頃からか(Version 4.0あたり？) Device Tree Overlay という機能が追加されています。
これは、Linux の動作中の Device Tree に、新たに Device Tree を追加したり削除したりする機能です。

## dtbocfg(Device Tree Overlay Configuration File System) とは

現時点(2016/4/4)の Linux Kernel Version 4.4.4 には Device Tree Overlay の機能は入っていますが、残念ながらこれらの機能はカーネル内部からしか使えません。ユーザーから使うにはなんらかのインターフェースが必要です。

例えば、[「Transactional Device Tree & Overlays」](http://events.linuxfoundation.org/sites/events/files/slides/dynamic-dt-elce14.pdf)には ConfigFS を使った方法が載っています。この方法が使えれば良いのですが、現状、この機能は Linux Kernel のメインラインには導入されていません。

そこで、用意したのがこの dtbocfg (Device Tree Blob Overlay Configuration File System) です。
あくまでも簡易版ですが、とりあえず試してみることは出来ます。


# 準備

## Linux カーネルのビルド

私が Device Tree Overlay を確認した Linux のバージョンは 4.4.4 です。   

また、Linux Kernel のビルド時に、Device Tree overlays オプションをオンにしておく必要があります。    
具体的には、make menu_config で　Device Drivers ---> Device Tree and Open Firmware support ---> Device Tree overlays をチェックするか、.config で CONFIG_OF_OVERLAY=y を追加するかしてカーネルをビルドしておく必要があります。

## dtbocfg の準備

下記のようにダウンロードして、Makefile を適当に修正してコンパイルしてください。

````shell
shell% git clone https://github.com/ikwzm/dtbocfg.git
shell% cd dtbocfg
shell% make
````

ターゲットシステムの Linux を起動したら、上記のデバイスドライバをロードしてください。

````shell
shell# insmod dtbocfg.ko
[ 1458.894102] dtbocfg_module_init
[ 1458.897231] dtbocfg_module_init: OK
````

もし ConfigFS がマウントされていない場合は次のように手動でマウントしてください。

````shell
shell# mount -t configfs none /config
````

これで /config/device-tree/overlays が見えれば準備完了です。

````shell
shell# ls -la /config/device-tree/overlays/
合計 0
drwxr-xr-x 2 root root 0  4月  4 18:54 .
drwxr-xr-x 3 root root 0  4月  4 18:54 ..
shell#
````

# 使用例

## uio のオーバーレイ

### Device Tree Source の用意

次のような Device Tree Source を用意します。
ただしレジスタや割り込み等は適当なので、まちがってもアクセスしないようにしてください。あくまでも例です。

````uio0.dts
/dts-v1/;
/ {
	fragment@0 {
		target-path = "/amba";
		__overlay__ {
			#address-cells = <0x1>;
			#size-cells = <0x1>;
			uio0@43c10000 {
				compatible = "generic-uio";
				reg = <0x43c10000 0x1000>;
				interrupts = <0x0 0x1d 0x4>;
			};
		};
	};
};
````

### ConfigFS にディレクトリを用意する

まず、/config/device-tree/overlays の下に適当に名前を付けてディレクトリを作ります。
ここでは Device Tree Source に対応した uio0 というディレクトリを作っています。

````
shell# mkdir /config/device-tree/overlays/uio0
````

すると、/config/device-tree/overlays/uio0 の下に status と dtbo というファイルが自動的に出来ます。

````
shell# ls -la /config/device-tree/overlays/uio0/
合計 0
drwxr-xr-x 2 root root    0  4月  4 20:08 .
drwxr-xr-x 3 root root    0  4月  4 20:08 ..
-rw-r--r-- 1 root root 4096  4月  4 20:09 dtbo
-rw-r--r-- 1 root root 4096  4月  4 20:09 status
````

これは一見ファイルのように見えますが、実はカーネル内のアートリビュートです。

### Device Tree Blob を書き込む

Device Tree Blob を /config/device-tree/overlays/uio0/dtbo に書き込みます。

````
shell# dtc -I dts -O dtb -o uio0.dtbo uio0.dts
shell# cp uio0.dtbo /config/device-tree/overlays/uio0/dtbo
````

### Device Tree に追加する

次のように /config/device-tree/overlays/uio0/status に 1 を書き込むことにより、dtbo に書き込まれている Device Tree Blob をDevice Tree に追加します。
これで /dev/uio0 が出来ていれば完了です。

````
shell# echo 1 > /config/device-tree/overlays/uio0/status
shell# ls -la /dev/uio*
crw------- 1 root root 247, 0  4月  4 20:17 /dev/uio0
````

### Device Tree から削除する

次のように /config/device-tree/overlays/uio0/status に 0 を書き込むことにより、Device Tree から削除します。

````
shell# echo 0 > /config/device-tree/overlays/uio0/status
````

または、/config/device-tree/overlays/uio0 ディレクトリを削除することで、Device Tree から削除することも出来ます。

````
shell# rmdir /config/device-tree/overlays/uio0
````

## udmabuf のオーバーレイ

もう一つ、udmabuf のオーバーレイの例もあげておきます。
udmabuf に関しては[https://github.com/ikwzm/udmabuf](https://github.com/ikwzm/udmabuf)を参照してください。

### Device Tree Source の用意

次のような Device Tree Source を用意します。

````udmabuf4.dts
/dts-v1/;

/ {
	fragment@0 {
		target-path = "/amba";
		__overlay__ {
			udmabuf4 {
				compatible = "ikwzm,udmabuf-0.10.a";
				minor-number = <4>;
				size = <0x00400000>;
			};
		};
	};
};
````

### ConfigFS にディレクトリを用意する

まず、/config/device-tree/overlays の下に udmabuf4 というディレクトリを作ります。

````
shell# mkdir /config/device-tree/overlays/udmabuf4
````

### udmabuf デバイスドライバをロード

詳細は[「Linuxでユーザー空間で動作するプログラムとハードウェアがメモリを共有するためのデバイスドライバ」](http://qiita.com/ikwzm/items/cc1bb33ff43a491440ea)を参照してください。

````
shell# insmod udmabuf.ko
````

### Device Tree Blob を書き込む

Device Tree Blob を /config/device-tree/overlays/udmabuf4/dtbo に書き込みます。
ここでは、Device Tree Compiler の出力を直接書いています。

````
shell# dtc -I dts -O dtb -o /config/device-tree/overlays/udmabuf4/dtbo udmabuf4.dts
````

### Device Tree に追加する

次のように /config/device-tree/overlays/udmabuf4/status に 1 を書き込むことにより、dtbo に書き込まれている Device Tree Blob をDevice Tree に追加します。
この際、udmabuf デバイスドライバがすでにロードされている場合、/dev/udmabuf4 ができます。

````
shell# echo 1 > /config/device-tree/overlays/udmabuf4/status
[ 7256.806725] udmabuf amba:udmabuf4: driver probe start.
[ 7256.827450] udmabuf udmabuf4: driver installed
[ 7256.831818] udmabuf udmabuf4: major number   = 246
[ 7256.836631] udmabuf udmabuf4: minor number   = 4
[ 7256.841192] udmabuf udmabuf4: phys address   = 0x1f500000
[ 7256.846604] udmabuf udmabuf4: buffer size    = 4194304
[ 7256.851694] udmabuf amba:udmabuf4: driver installed.
shell# ls -la /dev/udmabuf*
crw------- 1 root root 247, 0  4月  4 20:30 /dev/udmabuf4
````

### Device Tree から削除する

次のように /config/device-tree/overlays/udmabuf4/status に 0 を書き込むことにより、Device Tree から削除します。

````
shell# echo 0 > /config/device-tree/overlays/udmabuf4/status
[ 7440.383899] udmabuf udmabuf4: driver uninstalled
[ 7440.389533] udmabuf amba:udmabuf4: driver unloaded
````

または、/config/device-tree/overlays/udmabuf4 ディレクトリを削除することで、Device Tree から削除することも出来ます。

````
shell# rmdir /config/device-tree/overlays/udmabuf4/
[ 7473.117564] udmabuf udmabuf4: driver uninstalled
[ 7473.123364] udmabuf amba:udmabuf4: driver unloaded
````

