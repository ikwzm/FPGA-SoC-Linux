### accumulator

- [https://github.com/ikwzm/msgpack-vhdl-examples](https://github.com/ikwzm/msgpack-vhdl-examples)
- [https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/accumulator](https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/accumulator)

#### File Description

##### ZYBO

 * examples/accumulator
   + Rakefile                : rake(make for ruby)'s version of Makefile
   + zptty0-zynq-zybo.dts    : device tree overlay source for zptty
   + accumulator_server.rb   : accumulator server library
   + test.rb                 : accumulator server test script
   + design_1_wrapper.bit    : accumulator server for ZYBO

##### DE0-Nano-SoC

 * examples/accumulator
   + Rakefile                : rake(make for ruby)'s version of Makefile
   + zptty0-de0-nano-soc.dts : device tree overlay source for zptty
   + accumulator_server.rb   : accumulator server library
   + test.rb                 : accumulator server test script
   + DE0_NANO_SOC.rbf        : accumulator server for DE0-Nano-SoC

#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/accumulator$ rake -T
rake fpga:install     # Install fpga
rake install          # Install fpga and devicetrees
rake run              # run
rake uninstall        # Uninstall fpga and devicetrees
rake zptty:install    # Install zptty device driver
rake zptty:uninstall  # Unnstall zptty device driver
```

#### Install FPGA and Device Tree

##### ZYBO

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake install
dd if=design_1_wrapper.bit of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
2083852 bytes (2.1 MB) copied, 0.0528286 s, 39.4 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-zynq-zybo.dts
[ 6032.783171] zptty 43c10000.zptty: ZPTTY Driver probe start
[ 6032.788851] zptty 43c10000.zptty: driver installed
[ 6032.793622] zptty 43c10000.zptty: device name    = zptty0
[ 6032.798945] zptty 43c10000.zptty: private record = ddfffc00 (332bytes)
[ 6032.805495] zptty 43c10000.zptty: major number   = 246
[ 6032.810574] zptty 43c10000.zptty: minor number   = 0
[ 6032.815567] zptty 43c10000.zptty: regs resource  = [mem 0x43c10000-0x43c10fff flags 0x200]
[ 6032.823806] zptty 43c10000.zptty: regs address   = e15b8000
[ 6032.829325] zptty 43c10000.zptty: irq resource   = [irq 161 flags 0x404]
[ 6032.836047] zptty 43c10000.zptty: tx buf size    = 128
[ 6032.841166] zptty 43c10000.zptty: rx buf size    = 128
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake install
dd if=DE0_NANO_SOC.rbf of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
1312432 bytes (1.3 MB) copied, 0.185027 s, 7.1 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-de0-nano-soc.dts
[  896.483534] zptty ff202000.zptty: ZPTTY Driver probe start
[  896.489281] zptty ff202000.zptty: driver installed
[  896.494062] zptty ff202000.zptty: device name    = zptty0
[  896.499496] zptty ff202000.zptty: private record = eebbc400 (332bytes)
[  896.506001] zptty ff202000.zptty: major number   = 240
[  896.511161] zptty ff202000.zptty: minor number   = 0
[  896.516112] zptty ff202000.zptty: regs resource  = [mem 0xff202000-0xff202fff flags 0x200]
[  896.524390] zptty ff202000.zptty: regs address   = f203a000
[  896.529985] zptty ff202000.zptty: irq resource   = [irq 67 flags 0x404]
[  896.536574] zptty ff202000.zptty: tx buf size    = 128
[  896.541718] zptty ff202000.zptty: rx buf size    = 128
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
dtbocfg.rb --remove zptty0
[ 6258.046383] zptty 43c10000.zptty: driver removed
```

