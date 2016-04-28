
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
	install ../scripts/fpgacfg_load_overlay.rb  $(prefix)/usr/bin/
	install dtbocfg/dtbocfg.rb                  $(prefix)/usr/bin/
	install systemd/device-tree-overlay.service $(prefix)/etc/systemd/system/
	install systemd/fpga-manager.service        $(prefix)/etc/systemd/system/
	install systemd/udmabuf.service             $(prefix)/etc/systemd/system/
	install systemd/zptty.service               $(prefix)/etc/systemd/system/
	for ko in $(kmod_objects); do install $$ko $(lib_dir) ; done
