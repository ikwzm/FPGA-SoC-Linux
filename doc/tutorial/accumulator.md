### accumulator

- [https://github.com/ikwzm/msgpack-vhdl-examples](https://github.com/ikwzm/msgpack-vhdl-examples)
- [https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/accumulator](https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/accumulator)

#### File Description

##### ZYBO

 * examples/accumulator
   + Rakefile                : rake(make for ruby)'s version of Makefile
   + accumulator_server.bin  : accumulator server for ZYBO
   + accumulator_server.dts  : device tree overlay source for accumulator server
   + accumulator_server.rb   : accumulator server library
   + test.rb                 : accumulator server test script

##### DE0-Nano-SoC

 * examples/accumulator
   + Rakefile                : rake(make for ruby)'s version of Makefile
   + accumulator_server.rbf  : accumulator server for DE0-Nano-SoC
   + accumulator_server.dts  : device tree overlay source for accumulator server
   + accumulator_server.rb   : accumulator server library
   + test.rb                 : accumulator server test script

#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/accumulator$ rake -T
rake install          # Install   accumulator_server
rake test             # Test      accumulator_server
rake uninstall        # Uninstall accumulator_server
```

#### Install FPGA and Device Tree

##### ZYBO

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake install
dtbocfg.rb --install accumulator_server --dts accumulator_server.dts
/config/device-tree/overlays/accumulator_server/dtbo: Warning (un[  102.230909] fpga_manager fpga0: writing accumulator_server.bin to Xilinx Zynq FPGA Manager
it_address_vs_reg): Node /fragment@1 has a unit name, but no reg property
[  102.370277] zptty 43c10000.zptty: ZPTTY Driver probe start
[  102.375955] zptty 43c10000.zptty: driver installed
[  102.382187] zptty 43c10000.zptty: device name    = zptty0
[  102.388238] zptty 43c10000.zptty: private record = ddf8fa00 (328bytes)
[  102.394683] zptty 43c10000.zptty: major number   = 244
[  102.401136] zptty 43c10000.zptty: minor number   = 0
[  102.406023] zptty 43c10000.zptty: regs resource  = [mem 0x43c10000-0x43c10fff flags 0x200]
[  102.415593] zptty 43c10000.zptty: regs address   = e0cfc000
[  102.421828] zptty 43c10000.zptty: irq resource   = [irq 162 flags 0x404]
[  102.429171] zptty 43c10000.zptty: tx buf size    = 128
[  102.434229] zptty 43c10000.zptty: rx buf size    = 128
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake install
dtbocfg.rb --install accumulator_server --dts accumulator_server.dts
/config/device-tree/overlays/accumulator_server/dtbo: Warning (unit_address_vs_reg): [  106.530451] fpga_manager fpga0: writing accumulator_server.rbf to Altera SOCFPGA FPGA Manager
Node /fragment@1 has a unit name, but no reg property
[  106.765546] zptty ff202000.zptty: ZPTTY Driver probe start
[  106.771333] zptty ff202000.zptty: driver installed
[  106.776910] zptty ff202000.zptty: device name    = zptty0
[  106.782299] zptty ff202000.zptty: private record = ef0e3200 (328bytes)
[  106.789117] zptty ff202000.zptty: major number   = 244
[  106.794547] zptty ff202000.zptty: minor number   = 0
[  106.799543] zptty ff202000.zptty: regs resource  = [mem 0xff202000-0xff202fff flags 0x200]
[  106.808931] zptty ff202000.zptty: regs address   = f0e2b000
[  106.815118] zptty ff202000.zptty: irq resource   = [irq 129 flags 0x404]
[  106.821797] zptty ff202000.zptty: tx buf size    = 128
[  106.827981] zptty ff202000.zptty: rx buf size    = 128
```

#### Run sample script

```
fpga@debian-fpga:~/examples/accumulator$ ruby test.rb
OK : reg = 1; add(6625) => 6626; reg = 6626
OK : reg = 6626; add(9833) => 16459; reg = 16459
OK : reg = 16459; add(7280) => 23739; reg = 23739
OK : reg = 23739; add(3535) => 27274; reg = 27274
OK : reg = 27274; add(5848) => 33122; reg = 33122
OK : reg = 33122; add(9770) => 42892; reg = 42892
OK : reg = 42892; add(2771) => 45663; reg = 45663
      :
      :
      :
OK : reg = -4997637; add(-9940) => -5007577; reg = -5007577
OK : reg = -5007577; add(-3887) => -5011464; reg = -5011464
NoMethodError
ArgumentError
ArgumentError
```

#### Uninstall Device Tree

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake uninstall
dtbocfg.rb --remove accumulator_server
[ 260.160451] zptty 43c10000.zptty: driver removed
```

