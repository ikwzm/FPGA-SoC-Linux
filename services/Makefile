
prefix   ?= ./
curr_dir ?= $(shell pwd)

.PHONY: install

clean:

all:

install: all
	install -d $(prefix)/usr/bin
	install -d $(prefix)/etc/systemd/system
	install -m 0755 ../scripts/fpgacfg-service.rb             $(prefix)/usr/bin/
	install -m 0755 ../drivers/dtbocfg/dtbocfg.rb             $(prefix)/usr/bin/
	install -m 0755 ../drivers/fpga-bridge/altera-hps2fpga.rb $(prefix)/usr/bin/
	install -m 0644 systemd/device-tree-overlay.service       $(prefix)/etc/systemd/system/
	install -m 0644 systemd/fpga-manager.service              $(prefix)/etc/systemd/system/
	install -m 0644 systemd/udmabuf.service                   $(prefix)/etc/systemd/system/
	install -m 0644 systemd/zptty.service                     $(prefix)/etc/systemd/system/
	install -m 0644 systemd/altera-hps2fpga.service           $(prefix)/etc/systemd/system/

