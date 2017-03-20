### Build Device Drivers and Services Package

There are two ways

1. run build-fpga-linux-driver-package.sh (easy)
2. run this chapter step-by-step (annoying)

#### Donwload Sources from github

```
shell$ git clone https://github.com/ikwzm/dtbocfg
shell$ git clone https://github.com/ikwzm/fpgacfg
shell$ git clone https://github.com/ikwzm/fclkcfg
shell$ git clone https://github.com/ikwzm/udmabuf
shell$ git clone https://github.com/ikwzm/PTTY_AXI4
```

#### Copy Source Files to drivers/

```
shell$ git archive --remote dtbocfg   --prefix=dtbocfg/  --format=tar v0.0.3 | tar xf - -C drivers
shell$ git archive --remote fpgacfg   --prefix=fpgacfg/  --format=tar v0.0.1 | tar xf - -C drivers
shell$ git archive --remote fclkcfg   --prefix=fclkcfg/  --format=tar v0.0.1 | tar xf - -C drivers
shell$ git archive --remote udmabuf   --prefix=udmabuf/  --format=tar v0.6.0 | tar xf - -C drivers
shell$ cd PTTY_AXI4; git checkout v1.0.0; cp -r src/drivers/zptty ../drivers; cd ..
```

#### Build Device Driver debian package

```
shell$ cd drivers
shell$ sudo debian/rules binary
```

#### Build Device Services debian package

```
shell$ cd services
shell$ sudo debian/rules binary
```
