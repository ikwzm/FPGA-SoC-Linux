FPGA Clock Configuration Device Driver
======================================

# はじめに

## fclkcfg とは

fclkcfg は FPGA Clock Configuration Device Driver で、ユーザー空間から Zynq の PL のクロックの周波数を変更したり出力を制御したりするデバイスドライバです。
Linux カーネルが本来持っている clk ドライバを、ユーザー空間から制御できるようにします。

## 対応プラットフォーム

* OS: Linux Kernel Version 4.4.4
* CPU: ARM(ZYNQ)

現在(2016年4月8日)、Altera-SoC で動作確認中ですがまだ動いていません。

# 使い方

## 準備

### ダウンロード

````shell
shell$ git clone https://github.com/ikwzm/fclkcfg
shell$ cd fclkcfg
`````

### コンパイル

Makefile を用意しています。環境にあわせて適当に修正してください。

### インストール

insmod で fclkcfg のカーネルドライバをロードします。その際 Device Tree の設定に従いデバイスドライバができます。Device Tree に関しては後述します。

````shell
zynq# insmod fclkcfg.ko
[  102.044387] fclkcfg amba:fclk0: driver installed.
[  102.049016] fclkcfg amba:fclk0: device name : fclk0
[  102.053949] fclkcfg amba:fclk0: clock  name : fclk0
[  102.058748] fclkcfg amba:fclk0: clock  rate : 100000000
````

アンインストールするには rmmod を使います。

````shell
zynq# rmmod fclkcfg
[  261.514039] fclkcfg amba:fclk0: driver unloaded
````

## デバイスツリー

### ZYBO での例1

ZYBO+linux(v4.4.4) で、デバイスツリーに次のような項目を追加します。

````devicetree:devicetree.dts
/dts-v1/;
		:
	      (中略)
		:
		slcr: slcr@f8000000 {
			#address-cells = <1>;
			#size-cells = <1>;
			compatible = "xlnx,zynq-slcr", "syscon", "simple-bus";
			reg = <0xF8000000 0x1000>;
			ranges;
			clkc: clkc@100 {
				#clock-cells = <1>;
				compatible = "xlnx,ps7-clkc";
				fclk-enable = <0>;
				clock-output-names = "armpll", "ddrpll", "iopll", "cpu_6or4x",
						"cpu_3or2x", "cpu_2x", "cpu_1x", "ddr2x", "ddr3x",
						"dci", "lqspi", "smc", "pcap", "gem0", "gem1",
						"fclk0", "fclk1", "fclk2", "fclk3", "can0", "can1",
						"sdio0", "sdio1", "uart0", "uart1", "spi0", "spi1",
						"dma", "usb0_aper", "usb1_aper", "gem0_aper",
						"gem1_aper", "sdio0_aper", "sdio1_aper",
						"spi0_aper", "spi1_aper", "can0_aper", "can1_aper",
						"i2c0_aper", "i2c1_aper", "uart0_aper", "uart1_aper",
						"gpio_aper", "lqspi_aper", "smc_aper", "swdt",
						"dbg_trc", "dbg_apb";
				reg = <0x100 0x100>;
			};
		:
	      (中略)
		:
		fclk0 {
			compatible  = "ikwzm,fclkcfg-0.10.a";
			clocks      = <&clkc 15>;
		};
````

これは fclk0 という名前のデバイスドライバは、ZYNQ の PL Clock 0 を制御することを示します。

clocks で PL のクロックを指定します。

このデバイスツリーではクロックの設定は slcr(System Level Control Register) の clkc で行うことを示しています。

clocks = \<\&clkc 15\> と記述することにより、fclk0 は clkc が管理しているクロックの15番目のクロック(これが PL Clock 0を指す)を制御することを指定します。

### ZYBO での例2

\&clkc の代わりに phandle を使って指定することもできます。

````devicetree:devicetree.dts
/dts-v1/;
		:
	      (中略)
		:
		slcr@f8000000 {
			#address-cells = <0x1>;
			#size-cells = <0x1>;
			compatible = "xlnx,zynq-slcr", "syscon", "simple-bus";
			reg = <0xf8000000 0x1000>;
			ranges;
			linux,phandle = <0x5>;
			phandle = <0x5>;

			clkc@100 {
				#clock-cells = <0x1>;
				compatible = "xlnx,ps7-clkc";
				fclk-enable = <0xf>;
				clock-output-names = "armpll", "ddrpll", "iopll", "cpu_6or4x", "cpu_3or2x", "cpu_2x", "cpu_1x", "ddr2x", "ddr3x", "dci", "lqspi", "smc", "pcap", "gem0", "gem1", "fclk0", "fclk1", "fclk2", "fclk3", "can0", "can1", "sdio0", "sdio1", "uart0", "uart1", "spi0", "spi1", "dma", "usb0_aper", "usb1_aper", "gem0_aper", "gem1_aper", "sdio0_aper", "sdio1_aper", "spi0_aper", "spi1_aper", "can0_aper", "can1_aper", "i2c0_aper", "i2c1_aper", "uart0_aper", "uart1_aper", "gpio_aper", "lqspi_aper", "smc_aper", "swdt", "dbg_trc", "dbg_apb";
				reg = <0x100 0x100>;
				ps-clk-frequency = <0x2faf080>;
				linux,phandle = <0x1>;
				phandle = <0x1>;
			};
		:
	      (中略)
		:
		fclk0 {
			compatible  = "ikwzm,fclkcfg-0.10.a";
			clocks      = <0x1 0xf>;
		};
````

この例では clkc は phandle = \<0x1\> に設定されています。したがって fclk0 の clocks の第一引数は 0x1 を指定します。

### ZYBO での例3

[「FPGA+SoC+LinuxでDevice Tree Overlayを試してみた」](http://qiita.com/ikwzm/items/ec514e955c16076327ce)で説明したように、Device Tree Overlay を使うこともできます。この場合は次のようなデバイスツリーを用意します。

````devicetree:fclk0-zynq-zybo.dts
/dts-v1/;
/ {
	fragment@0 {
		target-path = "/amba";
		__overlay__ {
			fclk0 {
				compatible  = "ikwzm,fclkcfg-0.10.a";
				clocks      = <1 15>;
			};
		};
	};
};
````

Device Tree Overlay の場合の問題は、例１で使ったような \&clkc のようなシンボルが使えないことです。例２のように phandle を使って指定しなければなりません。phandle の値は Device Tree Blob を作ったときに決まるので、この値が判らない時は、Linux を起動するときに使う Device Tree Blob を、一度 Device Tree Source に戻して確認したほうがよいでしょう。

[dtbocfg (Device Tree Blob Overlay Configuration System)](https://github.com/ikwzm/dtbocfg) を使う場合は次の様にします。

````shell
zynq# insmod fclkcfg.ko
zynq# mkdir /config/device-tree/overlay/fclk0
zynq# dtc -I dts -O dtb -o /config/device-tree/overlay/fclk0/dtbo fclk0-zynq-zybo.dts
zynq# echo 1 >/config/device-tree/overlays/fclk0/status
[ 3361.788836] fclkcfg amba:fclk0: driver installed.
[ 3361.794680] fclkcfg amba:fclk0: device name : fclk0
[ 3361.799542] fclkcfg amba:fclk0: clock  name : fclk0
[ 3361.804344] fclkcfg amba:fclk0: clock  rate : 100000000
````

## デバイスファイル

fclkcfg をロードすると、次のようなデバイスファイルが作成されます。

* /sys/class/fclkcfg/\<fclk0\>/enable
* /sys/class/fclkcfg/\<fclk0\>/rate
* /sys/class/fclkcfg/\<fclk0\>/round_rate

\<fclk0\> のところは、デバイスツリーに記述されたデバイス名が入ります。

### /sys/class/fclkcfg/\<fclk0\>/enable

このファイルに 1 を書くことで、クロックを出力するようにします。    
このファイルに 0 を書くことで、クロックを出力しないようにします。   
このファイルを読むことで、現在クロックを出力しているか否かが判ります。 1 なら出力中を示します。

````shell
zynq# echo 1 > /sys/class/fclkcfg/fclk0/enable
zynq# cat /sys/class/fclkcfg/fclk0/enable
1
zynq# echo 0 > /sys/class/fclkcfg/fclk0/enable
zynq# cat /sys/class/fclkcfg/fclk0/enable
0
````

### /sys/class/fclkcfg/\<fclk0\>/rate

このファイルに周波数を書くことで、クロックの周波数を変更することができます。例えば次のようにすることで周波数を 100MHz に変更します。


````shell
zynq# echo 100000000 > /sys/class/fclkcfg/fclk0/rate
zynq# cat /sys/class/fclkcfg/fclk0/rate
100000000
````

ただし、クロックによっては PLL の制限により希望した周波数に設定することが出来ない場合があります。
例えば [「U-Boot から Zynq の PLクロックとリセット信号を制御する」](http://qiita.com/ikwzm/items/3253940484591da84777)でも例をあげましたが ZYBO では 133 MHz を設定することが出来ません。強引に設定しようとすると次の様に125MHzに設定されます。

````shell
zynq# echo 133333333 > /sys/class/fclkcfg/fclk0/rate
zynq# cat /sys/class/fclkcfg/fclk0/rate
125000000
````

### /sys/class/fclkcfg/\<fclk0\>/round_rate

前節で説明した通り、クロックによっては PLL の制限により希望した周波数に設定することが出来ない場合があります。このファイルに周波数を書いて読むことにより、実際にどのような周波数になるかを知ることが出来ます。

````shell
zynq# echo 133333333 > /sys/class/fclkcfg/fclk0/round_rate
zynq# cat /sys/class/fclkcfg/fclk0/round_rate
133333333 => 125000000
zynq# echo  75000000 > /sys/class/fclkcfg/fclk0/round_rate
zynq# cat /sys/class/fclkcfg/fclk0/round_rate
75000000 => 71428572
````

# 参考

- [FPGA Clock Configuration Device Driver(https://github.com/ikwzm/fclkcfg)](https://github.com/ikwzm/fclkcfg)
- [「FPGA+SoC+Linuxのブートシーケンス(ZYNQ+U-Boot-SPL編)」 @Qiita](http://qiita.com/ikwzm/items/efacec8d8e0744e17d45)
- [「U-Boot から Zynq の PLクロックとリセット信号を制御する」 @Qiita](http://qiita.com/ikwzm/items/3253940484591da84777)
- [「FPGA+SoC+LinuxでDevice Tree Overlayを試してみた」 @Qiita](http://qiita.com/ikwzm/items/ec514e955c16076327ce)

