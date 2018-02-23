
prefix   ?= ./
curr_dir ?= $(shell pwd)
lib_dir  ?= $(prefix)/lib/modules/4.14.21-armv7-fpga/ikwzm

kmod_objects += dtbocfg/dtbocfg.ko
kmod_objects += fclkcfg/fclkcfg.ko
kmod_objects += udmabuf/udmabuf.ko
kmod_objects += zptty/zptty.ko
kmod_subdirs  = $(dir $(kmod_objects))


.PHONY: all install

all:
	for dir in $(kmod_subdirs); do \
		cd $$dir ; $(MAKE) ARCH=arm KERNEL_SRC_DIR=$(curr_dir)/../linux-4.14.21-armv7-fpga all   ; cd $(curr_dir) ;\
	done

clean:
	for dir in $(kmod_subdirs); do \
		cd $$dir ; $(MAKE) ARCH=arm KERNEL_SRC_DIR=$(curr_dir)/../linux-4.14.21-armv7-fpga clean ; cd $(curr_dir) ;\
	done

install: all
	install -d $(lib_dir)
	for ko in $(kmod_objects); do install -m 0644 $$ko $(lib_dir) ; done
