### uio_irq_sample

- [https://github.com/ikwzm/ZYBO_UIO_IRQ_SAMPLE](https://github.com/ikwzm/ZYBO_UIO_IRQ_SAMPLE)


#### File Description

##### ZYBO

 * examples/uio_irq_sample
   + Rakefile               : rake(make for ruby)'s version of Makefile
   + devicetree.dts         : device tree overlay source for uio and udmabuf
   + sample_common.h        : sample programs common header file
   + sample1.c              : sample1 program source
   + sample2.c              : sample2 program source
   + design_1_wrapper.bit   : memory to memory copy dma for ZYBO

##### DE0-Nano-SoC

 * examples/uio_irq_sample
   + Rakefile               : rake(make for ruby)'s version of Makefile
   + devicetree.dts         : device tree overlay source for uio and udmabuf
   + sample_common.h        : sample programs common header file
   + sample1.c              : sample1 program source
   + sample2.c              : sample2 program source
   + DE0_NANO_SOC.rbf       : memory to memory copy dma for DE0-Nano-SoC

#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/uio_irq_sample$ rake -T
rake devicetree:install    # Install device tree
rake devicetree:uninstall  # Uninstall device tree
rake fpga:install          # Install fpga
rake install               # Install fpga and devicetrees
rake uninstall             # Uninstall fpga and devicetrees
```

#### Install FPGA and Device Tree

##### ZYBO

```
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dd if=design_1_wrapper.bit of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
2083852 bytes (2.1 MB) copied, 0.0518765 s, 40.2 MB/s
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
[ 5257.752033] udmabuf amba:pump-udmabuf4: driver probe start.
[ 5257.771542] udmabuf udmabuf4: driver installed
[ 5257.775914] udmabuf udmabuf4: major number   = 245
[ 5257.780743] udmabuf udmabuf4: minor number   = 0
[ 5257.785287] udmabuf udmabuf4: phys address   = 0x1f100000
[ 5257.790707] udmabuf udmabuf4: buffer size    = 4194304
[ 5257.795790] udmabuf amba:pump-udmabuf4: driver installed.
[ 5257.801731] udmabuf amba:pump-udmabuf5: driver probe start.
[ 5257.819306] udmabuf udmabuf5: driver installed
[ 5257.823698] udmabuf udmabuf5: major number   = 245
[ 5257.828442] udmabuf udmabuf5: minor number   = 1
[ 5257.833085] udmabuf udmabuf5: phys address   = 0x1f500000
[ 5257.838424] udmabuf udmabuf5: buffer size    = 4194304
[ 5257.843584] udmabuf amba:pump-udmabuf5: driver installed.
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake install
dd if=DE0_NANO_SOC.rbf of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
1365784 bytes (1.4 MB) copied, 0.202703 s, 6.7 MB/s
dtbocfg.rb --install uio_irq_sample --dts devicetree.dts
[  561.659154] udmabuf soc:amba:pump-udmabuf4: driver probe start.
[  561.676785] udmabuf udmabuf4: driver installed
[  561.681221] udmabuf udmabuf4: major number   = 241
[  561.687117] udmabuf udmabuf4: minor number   = 0
[  561.691721] udmabuf udmabuf4: phys address   = 0x3f100000
[  561.698038] udmabuf udmabuf4: buffer size    = 4194304
[  561.703728] udmabuf soc:amba:pump-udmabuf4: driver installed.
[  561.709867] udmabuf soc:amba:pump-udmabuf5: driver probe start.
[  561.727397] udmabuf udmabuf5: driver installed
[  561.731833] udmabuf udmabuf5: major number   = 241
[  561.737816] udmabuf udmabuf5: minor number   = 1
[  561.742420] udmabuf udmabuf5: phys address   = 0x3f500000
[  561.748747] udmabuf udmabuf5: buffer size    = 4194304
[  561.754385] udmabuf soc:amba:pump-udmabuf5: driver installed.
```

#### Compile sample programs

```
fpga@debian-fpga:~/examples/uio_irq_sample$ rake
gcc  -o sample1 sample1.c
gcc  -o sample2 sample2.c
```

#### Run sample programs

```
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

```
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

```
fpga@debian-fpga:~/examples/uio_irq_sample$ sudo rake uninstall
dtbocfg.rb --remove uio_irq_sample
[ 5559.550963] udmabuf udmabuf5: driver uninstalled
[ 5559.556676] udmabuf amba:pump-udmabuf5: driver unloaded
[ 5559.563018] udmabuf udmabuf4: driver uninstalled
[ 5559.569580] udmabuf amba:pump-udmabuf4: driver unloaded
```

