### uio_irq_sample

- [https://github.com/ikwzm/ZYBO_UIO_IRQ_SAMPLE](https://github.com/ikwzm/ZYBO_UIO_IRQ_SAMPLE)
- [https://github.com/ikwzm/ZYBO_PUMP](https://github.com/ikwzm/ZYBO_PUMP)
- [https://github.com/ikwzm/PYNQ_PUMP](https://github.com/ikwzm/PYNQ_PUMP)

#### File Description

##### ZYBO

 * examples/uio_irq_sample
   + Rakefile               : rake(make for ruby)'s version of Makefile
   + devicetree.dts         : device tree overlay source for uio and udmabuf
   + pump_axi4.bin          : memory to memory copy dma for ZYBO
   + sample_common.h        : sample programs common header file
   + sample1.c              : sample1 program source
   + sample2.c              : sample2 program source

##### PYNQ-Z1

 * examples/uio_irq_sample
   + Rakefile               : rake(make for ruby)'s version of Makefile
   + devicetree.dts         : device tree overlay source for uio and udmabuf
   + pump_axi4.bin          : memory to memory copy dma for PYNQ-Z1
   + sample_common.h        : sample programs common header file
   + sample1.c              : sample1 program source
   + sample2.c              : sample2 program source

##### DE0-Nano-SoC

 * examples/uio_irq_sample
   + Rakefile               : rake(make for ruby)'s version of Makefile
   + devicetree.dts         : device tree overlay source for uio and udmabuf
   + pump_axi4.rbf          : memory to memory copy dma for DE0-Nano-SoC
   + sample_common.h        : sample programs common header file
   + sample1.c              : sample1 program source
   + sample2.c              : sample2 program source

#### Rake Task Description

use rake (make for ruby) script.

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ rake -T
rake install    # Install fpga and devicetrees
rake uninstall  # Uninstall fpga and devicetrees
```

#### Install FPGA and Device Tree

##### ZYBO

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
/config/device-tree/overlays/uio_irq_sample/dtbo: Warning (unit_a[  547.564512] fpga_manager fpga0: writing pump_axi4.bin to Xilinx Zynq FPGA Manager
ddress_vs_reg): Node /fragment@0 has a unit name, but no reg property
[  547.702887] udmabuf amba:fpga-region0:pump-udmabuf4: driver probe start.
[  547.722962] udmabuf udmabuf4: driver installed
[  547.727389] udmabuf udmabuf4: major number   = 245
[  547.732099] udmabuf udmabuf4: minor number   = 0
[  547.736772] udmabuf udmabuf4: phys address   = 0x1f100000
[  547.742098] udmabuf udmabuf4: buffer size    = 4194304
[  547.747258] udmabuf amba:fpga-region0:pump-udmabuf4: driver installed.
[  547.754353] udmabuf amba:fpga-region0:pump-udmabuf5: driver probe start.
[  547.773847] udmabuf udmabuf5: driver installed
[  547.778247] udmabuf udmabuf5: major number   = 245
[  547.782990] udmabuf udmabuf5: minor number   = 1
[  547.789777] udmabuf udmabuf5: phys address   = 0x1f500000
[  547.795099] udmabuf udmabuf5: buffer size    = 4194304
[  547.801525] udmabuf amba:fpga-region0:pump-udmabuf5: driver installed.
```

##### PYNQ-Z1

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
/config/device-tree/overlays/uio_irq_sample/dtbo: Warning (unit_a[  547.564512] fpga_manager fpga0: writing pump_axi4.bin to Xilinx Zynq FPGA Manager
ddress_vs_reg): Node /fragment@0 has a unit name, but no reg property
[  547.702887] udmabuf amba:fpga-region0:pump-udmabuf4: driver probe start.
[  547.722962] udmabuf udmabuf4: driver installed
[  547.727389] udmabuf udmabuf4: major number   = 245
[  547.732099] udmabuf udmabuf4: minor number   = 0
[  547.736772] udmabuf udmabuf4: phys address   = 0x1f100000
[  547.742098] udmabuf udmabuf4: buffer size    = 4194304
[  547.747258] udmabuf amba:fpga-region0:pump-udmabuf4: driver installed.
[  547.754353] udmabuf amba:fpga-region0:pump-udmabuf5: driver probe start.
[  547.773847] udmabuf udmabuf5: driver installed
[  547.778247] udmabuf udmabuf5: major number   = 245
[  547.782990] udmabuf udmabuf5: minor number   = 1
[  547.789777] udmabuf udmabuf5: phys address   = 0x1f500000
[  547.795099] udmabuf udmabuf5: buffer size    = 4194304
[  547.801525] udmabuf amba:fpga-region0:pump-udmabuf5: driver installed.
```

##### DE0-Nano-SoC

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
/config/device-tree/overlays/uio_irq_sample/dtbo: Warning (unit_a[  567.830702] fpga_manager fpga0: writing pump_axi4.bin to Xilinx Zynq FPGA Manager
ddress_vs_reg): Node /fragment@0 has a unit name, but no reg property
[  567.910646] udmabuf amba:fpga-region0:pump-udmabuf4: driver probe start.
[  567.936709] udmabuf udmabuf4: driver installed
[  567.941107] udmabuf udmabuf4: major number   = 244
[  567.945854] udmabuf udmabuf4: minor number   = 0
[  567.951038] udmabuf udmabuf4: phys address   = 0x1f100000
[  567.956358] udmabuf udmabuf4: buffer size    = 4194304
[  567.962719] udmabuf amba:fpga-region0:pump-udmabuf4: driver installed.
[  567.971234] udmabuf amba:fpga-region0:pump-udmabuf5: driver probe start.
[  567.995225] udmabuf udmabuf5: driver installed
[  567.999595] udmabuf udmabuf5: major number   = 244
[  568.006350] udmabuf udmabuf5: minor number   = 1
[  568.011784] udmabuf udmabuf5: phys address   = 0x1f500000
[  568.017101] udmabuf udmabuf5: buffer size    = 4194304
[  568.023830] udmabuf amba:fpga-region0:pump-udmabuf5: driver installed.
```

#### Compile sample programs

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ rake
gcc  -o sample1 sample1.c
gcc  -o sample2 sample2.c
```

#### Run sample programs

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ ./sample1
time = 0.022111 sec
time = 0.022158 sec
time = 0.022040 sec
time = 0.022147 sec
time = 0.022094 sec
time = 0.022021 sec
time = 0.022118 sec
time = 0.022119 sec
time = 0.022078 sec
time = 0.022076 sec
```

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ ./sample2
time = 0.022132 sec
time = 0.022015 sec
time = 0.022190 sec
time = 0.022070 sec
time = 0.022135 sec
time = 0.022116 sec
time = 0.022134 sec
time = 0.022103 sec
time = 0.022103 sec
time = 0.022095 sec
```

#### Uninstall Device Tree

```console
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake uninstall
dtbocfg.rb --remove uio_irq_sample
[  611.940358] udmabuf udmabuf5: driver uninstalled
[  611.946074] udmabuf amba:fpga-region0:pump-udmabuf5: driver unloaded
[  611.952663] udmabuf udmabuf4: driver uninstalled
[  611.960029] udmabuf amba:fpga-region0:pump-udmabuf4: driver unloaded
```

