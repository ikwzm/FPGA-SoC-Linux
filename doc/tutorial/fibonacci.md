### fibonacci

- [https://github.com/ikwzm/msgpack-vhdl-examples](https://github.com/ikwzm/msgpack-vhdl-examples)
- [https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/fibonacci](https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/fibonacci)

#### File Description

##### ZYBO

 * examples/fibonacci
   + Rakefile                : rake(make for ruby)'s version of Makefile
   + fibonacci_server.bin    : fibonacci server for ZYBO
   + fibonacci_server.dts    : device tree overlay source for fibonacci server
   + fibonacci_server.rb     : fibonacci server library
   + test.rb                 : fibonacci server test script

##### DE0-Nano-SoC

 * examples/fibonacci
   + Rakefile                : rake(make for ruby)'s version of Makefile
   + fibonacci_server.rbf    : fibonacci server for DE0-Nano-SoC
   + fibonacci_server.dts    : device tree overlay source for fibonacci server
   + fibonacci_server.rb     : fibonacci server library
   + test.rb                 : fibonacci server test script

#### Rake Task Description

use rake (make for ruby) script.

```console
fpga@debian-fpga:~/examples/fibonacci$ rake -T
rake install    # Install  fibonacci_server
rake test       # Test     fibonacci_server
rake uninstall  # Unnstall fibonacci_server
```

#### Install FPGA and Device Tree

##### ZYBO

```console
fpga@debian-fpga:~/examples/fibonacci$ sudo rake install
dtbocfg.rb --install fibonacci_server --dts fibonacci_server.dts
/config/device-tree/overlays/fibonacci_server/dtbo: Warning (unit[  348.053645] fpga_manager fpga0: writing fibonacci_server.bin to Xilinx Zynq FPGA Manager
_address_vs_reg): Node /fragment@1 has a unit name, but no reg property
[  348.191036] zptty 43c10000.zptty: ZPTTY Driver probe start
[  348.196815] zptty 43c10000.zptty: driver installed
[  348.201532] zptty 43c10000.zptty: device name    = zptty0
[  348.206973] zptty 43c10000.zptty: private record = dde6a200 (328bytes)
[  348.213424] zptty 43c10000.zptty: major number   = 244
[  348.218582] zptty 43c10000.zptty: minor number   = 0
[  348.223495] zptty 43c10000.zptty: regs resource  = [mem 0x43c10000-0x43c10fff flags 0x200]
[  348.231774] zptty 43c10000.zptty: regs address   = e1100000
[  348.237325] zptty 43c10000.zptty: irq resource   = [irq 162 flags 0x404]
[  348.243976] zptty 43c10000.zptty: tx buf size    = 128
[  348.249132] zptty 43c10000.zptty: rx buf size    = 128
```

##### DE0-Nano-SoC

```console
fpga@debian-fpga:~/examples/fibonacci$ sudo rake install
dtbocfg.rb --install fibonacci_server --dts fibonacci_server.dts
/config/device-tree/overlays/fibonacci_server/dtbo: Warning (unit_address_vs_reg): [   40.131192] fpga_manager fpga0: writing fibonacci_server.rbf to Altera SOCFPGA FPGA Manager
Node /fragment@1 has a unit name, but no reg property
[   40.358668] zptty ff202000.zptty: ZPTTY Driver probe start
[   40.364460] zptty ff202000.zptty: driver installed
[   40.370437] zptty ff202000.zptty: device name    = zptty0
[   40.375821] zptty ff202000.zptty: private record = ee441e00 (328bytes)
[   40.383370] zptty ff202000.zptty: major number   = 244
[   40.389099] zptty ff202000.zptty: minor number   = 0
[   40.394052] zptty ff202000.zptty: regs resource  = [mem 0xff202000-0xff202fff flags 0x200]
[   40.403333] zptty ff202000.zptty: regs address   = f0ce3000
[   40.409536] zptty ff202000.zptty: irq resource   = [irq 129 flags 0x404]
[   40.416237] zptty ff202000.zptty: tx buf size    = 128
[   40.422507] zptty ff202000.zptty: rx buf size    = 128
```


#### Run sample script

```console
fpga@debian-fpga:~/examples/fibonacci$ ruby test.rb
0 => 0
1 => 1
2 => 1
3 => 2
4 => 3
5 => 5
6 => 8
7 => 13
8 => 21
9 => 34
10 => 55
11 => 89
12 => 144
13 => 233
14 => 377
15 => 610
16 => 987
17 => 1597
18 => 2584
19 => 4181
20 => 6765
21 => 10946
22 => 17711
23 => 28657
24 => 46368
25 => 75025
26 => 121393
27 => 196418
28 => 317811
29 => 514229
30 => 832040
31 => 1346269
32 => 2178309
33 => 3524578
34 => 5702887
35 => 9227465
36 => 14930352
37 => 24157817
38 => 39088169
39 => 63245986
40 => 102334155
41 => 165580141
42 => 267914296
43 => 433494437
44 => 701408733
45 => 1134903170
46 => 1836311903
47 => 2971215073
48 => 4807526976
49 => 7778742049
50 => 12586269025
51 => 20365011074
52 => 32951280099
53 => 53316291173
54 => 86267571272
55 => 139583862445
56 => 225851433717
57 => 365435296162
58 => 591286729879
59 => 956722026041
60 => 1548008755920
61 => 2504730781961
62 => 4052739537881
63 => 6557470319842
64 => 10610209857723
65 => 17167680177565
66 => 27777890035288
67 => 44945570212853
68 => 72723460248141
69 => 117669030460994
70 => 190392490709135
71 => 308061521170129
72 => 498454011879264
73 => 806515533049393
74 => 1304969544928657
75 => 2111485077978050
76 => 3416454622906707
77 => 5527939700884757
78 => 8944394323791464
79 => 14472334024676221
80 => 23416728348467685
81 => 37889062373143906
82 => 61305790721611591
83 => 99194853094755497
84 => 160500643816367088
85 => 259695496911122585
86 => 420196140727489673
87 => 679891637638612258
88 => 1100087778366101931
89 => 1779979416004714189
90 => 2880067194370816120
```

#### Uninstall Device Tree

```console
fpga@debian-fpga:~/examples/accumulator$ sudo rake uninstall
dtbocfg.rb --remove fibonacci_server
[  418.672324] zptty 43c10000.zptty: driver removed
```


