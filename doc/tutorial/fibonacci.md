### fibonacci

- [https://github.com/ikwzm/msgpack-vhdl-examples](https://github.com/ikwzm/msgpack-vhdl-examples)
- [https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/fibonacci](https://github.com/ikwzm/msgpack-vhdl-examples/tree/master/examples/fibonacci)

#### Rake Task Description

use rake (make for ruby) script.

```
fpga@debian-fpga:~/examples/fibonacci$ rake -T
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
fpga@debian-fpga:~/examples/fibonacci$ sudo rake install
dd if=design_1_wrapper.bit of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
2083852 bytes (2.1 MB) copied, 0.140482 s, 14.8 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-zynq-zybo.dts
[ 6688.904316] zptty 43c10000.zptty: ZPTTY Driver probe start
[ 6688.909991] zptty 43c10000.zptty: driver installed
[ 6688.914806] zptty 43c10000.zptty: device name    = zptty0
[ 6688.920124] zptty 43c10000.zptty: private record = ddffac00 (332bytes)
[ 6688.926729] zptty 43c10000.zptty: major number   = 246
[ 6688.931787] zptty 43c10000.zptty: minor number   = 0
[ 6688.936792] zptty 43c10000.zptty: regs resource  = [mem 0x43c10000-0x43c10fff flags 0x200]
[ 6688.945022] zptty 43c10000.zptty: regs address   = e17bc000
[ 6688.950538] zptty 43c10000.zptty: irq resource   = [irq 161 flags 0x404]
[ 6688.957255] zptty 43c10000.zptty: tx buf size    = 128
[ 6688.962341] zptty 43c10000.zptty: rx buf size    = 128
```

##### DE0-Nano-SoC

```
fpga@debian-fpga:~/examples/fibonacci$ sudo rake install
dd if=DE0_NANO_SOC.rbf of=/dev/fpgacfg0 bs=1M
1+1 records in
1+1 records out
1290712 bytes (1.3 MB) copied, 0.186531 s, 6.9 MB/s
dtbocfg.rb --install zptty0 --dts zptty0-de0-nano-soc.dts
[ 1124.141145] zptty ff202000.zptty: ZPTTY Driver probe start
[ 1124.146987] zptty ff202000.zptty: driver installed
[ 1124.151768] zptty ff202000.zptty: device name    = zptty0
[ 1124.158807] zptty ff202000.zptty: private record = ee9e3200 (332bytes)
[ 1124.165893] zptty ff202000.zptty: major number   = 240
[ 1124.171015] zptty ff202000.zptty: minor number   = 0
[ 1124.177007] zptty ff202000.zptty: regs resource  = [mem 0xff202000-0xff202fff flags 0x200]
[ 1124.185780] zptty ff202000.zptty: regs address   = f217e000
[ 1124.191336] zptty ff202000.zptty: irq resource   = [irq 67 flags 0x404]
[ 1124.198906] zptty ff202000.zptty: tx buf size    = 128
[ 1124.204554] zptty ff202000.zptty: rx buf size    = 128
```


#### Run sample script

```
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

```
fpga@debian-fpga:~/examples/accumulator$ sudo rake uninstall
dtbocfg.rb --remove zptty0
[ 6813.229984] zptty 43c10000.zptty: driver removed
```


