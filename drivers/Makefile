
prefix   ?= ./
curr_dir ?= $(shell pwd)
lib_dir  ?= $(prefix)/lib/modules/4.4.7-armv7-fpga/ikwzm

kmod_objects += dtbocfg/dtbocfg.ko
kmod_objects += fpgacfg/fpgacfg.ko
kmod_objects += fclkcfg/fclkcfg.ko
kmod_objects += udmabuf/udmabuf.ko
kmod_objects += zptty/zptty.ko
kmod_subdirs  = $(dir $(kmod_objects))


.PHONY: all install

all:
	for dir in $(kmod_subdirs); do \
		cd $$dir ; $(MAKE) KERNEL_SRC_DIR=$(curr_dir)/../linux-4.4.7-armv7-fpga all   ; cd $(curr_dir) ;\
	done

clean:
	for dir in $(kmod_subdirs); do \
		cd $$dir ; $(MAKE) KERNEL_SRC_DIR=$(curr_dir)/../linux-4.4.7-armv7-fpga clean ; cd $(curr_dir) ;\
	done

install: all
	install -d $(lib_dir)
	install -d $(prefix)/usr/bin
	install -d $(prefix)/etc/systemd/system
	install -m 0755 ../scripts/fpgacfg-service.rb       $(prefix)/usr/bin/
	install -m 0755 dtbocfg/dtbocfg.rb                  $(prefix)/usr/bin/
	install -m 0644 systemd/device-tree-overlay.service $(prefix)/etc/systemd/system/
	install -m 0644 systemd/fpga-manager.service        $(prefix)/etc/systemd/system/
	install -m 0644 systemd/udmabuf.service             $(prefix)/etc/systemd/system/
	install -m 0644 systemd/zptty.service               $(prefix)/etc/systemd/system/
	for ko in $(kmod_objects); do install -m 0644 $$ko $(lib_dir) ; done
