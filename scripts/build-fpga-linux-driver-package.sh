
### Donwload Sources from github

git clone https://github.com/ikwzm/dtbocfg
git clone https://github.com/ikwzm/fpgacfg
git clone https://github.com/ikwzm/fclkcfg
git clone https://github.com/ikwzm/udmabuf
git clone https://github.com/ikwzm/PTTY_AXI4

### Copy Source Files to drivers/

git archive --remote dtbocfg   --prefix=dtbocfg/  --format=tar v0.0.3 | tar xf - -C drivers
git archive --remote fpgacfg   --prefix=fpgacfg/  --format=tar v0.0.1 | tar xf - -C drivers
git archive --remote fclkcfg   --prefix=fclkcfg/  --format=tar v0.0.1 | tar xf - -C drivers
git archive --remote udmabuf   --prefix=udmabuf/  --format=tar v0.6.0 | tar xf - -C drivers
cd PTTY_AXI4; git checkout v1.0.0; cp -r src/drivers/zptty ../drivers; cd ..

### Build debian package

cd drivers
sudo debian/rule binary



