VERSION=4.19.57
XILINX_TARGET_PATH=../zynq-zybo
ALTERA_TARGET_PATH=../de0-nano-soc

TARGET = boot/boot.scr \
         boot/vmlinuz-$(VERSION)-armv7-fpga \
         boot/boot.bin \
         boot/design_1_wrapper.bit \
         boot/devicetree-$(VERSION)-zynq-zybo.dtb \
         boot/devicetree-$(VERSION)-zynq-zybo.dts \
         boot/u-boot.img \
         boot/devicetree-$(VERSION)-socfpga.dtb \
         boot/devicetree-$(VERSION)-socfpga.dts \
         boot/DE0_NANO_SOC.rbf \
         u-boot/u-boot-spl.sfp \
         u-boot/u-boot.img \
         $(END_LIST)

COPY   = cp
REMOVE = rm
MKDIR  = mkdir

target : $(TARGET)

clean  :
	-$(REMOVE) $(TARGET)

boot/boot.scr : boot/boot.script
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "linux boot script" -d boot/boot.script boot/boot.scr

boot/vmlinuz-$(VERSION)-armv7-fpga       : $(XILINX_TARGET_PATH)/boot/vmlinuz-$(VERSION)-armv7-fpga
	$(COPY) $< $@

boot/boot.bin                            : $(XILINX_TARGET_PATH)/boot/boot.bin
	$(COPY) $< $@

boot/design_1_wrapper.bit                : $(XILINX_TARGET_PATH)/boot/design_1_wrapper.bit
	$(COPY) $< $@

boot/devicetree-$(VERSION)-zynq-zybo.dtb : $(XILINX_TARGET_PATH)/boot/devicetree-$(VERSION)-zynq-zybo.dtb
	$(COPY) $< $@

boot/devicetree-$(VERSION)-zynq-zybo.dts : $(XILINX_TARGET_PATH)/boot/devicetree-$(VERSION)-zynq-zybo.dts
	$(COPY) $< $@

boot/u-boot.img                          : $(XILINX_TARGET_PATH)/boot/u-boot.img
	$(COPY) $< $@

boot/devicetree-$(VERSION)-socfpga.dtb   : $(ALTERA_TARGET_PATH)/boot/devicetree-$(VERSION)-socfpga.dtb
	$(COPY) $< $@

boot/devicetree-$(VERSION)-socfpga.dts   : $(ALTERA_TARGET_PATH)/boot/devicetree-$(VERSION)-socfpga.dts
	$(COPY) $< $@

boot/DE0_NANO_SOC.rbf                    : $(ALTERA_TARGET_PATH)/boot/DE0_NANO_SOC.rbf
	$(COPY) $< $@

u-boot/u-boot-spl.sfp                    : $(ALTERA_TARGET_PATH)/u-boot/u-boot-spl.sfp
	@if [ ! -d u-boot ] ; then $(MKDIR) -p u-boot; fi
	$(COPY) $< $@

u-boot/u-boot.img                        : $(ALTERA_TARGET_PATH)/u-boot/u-boot.img
	@if [ ! -d u-boot ] ; then $(MKDIR) -p u-boot; fi
	$(COPY) $< $@

