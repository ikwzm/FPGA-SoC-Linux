#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#---------------------------------------------------------------------------------
#
#       Version     :   0.0.1
#       Created     :   2016/5/12
#       File name   :   altera-hps2fpga.rb
#       Author      :   Ichiro Kawazome <ichiro_k@ca2.so-net.ne.jp>
#       Description :   altera-hps2fpga service management script.
#
#---------------------------------------------------------------------------------
#
#       Copyright (C) 2016 Ichiro Kawazome
#       All rights reserved.
# 
#       Redistribution and use in source and binary forms, with or without
#       modification, are permitted provided that the following conditions
#       are met:
# 
#         1. Redistributions of source code must retain the above copyright
#            notice, this list of conditions and the following disclaimer.
# 
#         2. Redistributions in binary form must reproduce the above copyright
#            notice, this list of conditions and the following disclaimer in
#            the documentation and/or other materials provided with the
#            distribution.
# 
#       THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#       "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#       LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#       A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
#       OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#       SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#       LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#       DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#       THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
#       (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#       OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
#---------------------------------------------------------------------------------
require 'optparse'
require 'stringio'

class DeviceTreeOverlayConfiguration

  CONFIG_OF_OVERLAY_PATH = "/config/device-tree/overlays/"
  attr_reader   :device_name
  attr_reader   :device_tree_overlay_path
  attr_accessor :debug
  
  def initialize(device_name)
    @device_name              = device_name
    @device_tree_overlay_path = CONFIG_OF_OVERLAY_PATH + device_name
    @debug                    = false
  end

  def create
    begin
      Dir.mkdir(@device_tree_overlay_path)
    rescue => e
      print "error raised:"
      p e
      abort
    end
  end

  def start
    begin 
      File.write("#{@device_tree_overlay_path}/status", "1")
    rescue => e
      print "error raised:"
      p e
      Dir.rmdir(@device_tree_overlay_path)
      abort
    end
  end
  
  def stop
    begin 
      File.write("#{@device_tree_overlay_path}/status", "0")
    rescue => e
      print "error raised:"
      p e
      Dir.rmdir(@device_tree_overlay_path)
      abort
    end
  end

  def load_dts(filename, input_stream)
    puts "load_dts(#{filename}, #{input_stream})" if (@debug)
    begin
      IO.popen("dtc -I dts -O dtb -o #{@device_tree_overlay_path}/dtbo", "r+") do |dtbo|
        dtbo.write(input_stream.read)
      end
    rescue => e
      print "error raised:"
      p e
      Dir.rmdir(@device_tree_overlay_path)
      abort
    end
  end

  def load_dtb(filename, input_stream)
    puts "load_dtb(#{filename}, #{input_stream})" if (@debug)
    begin
      open("#{@device_tree_overlay_path}/dtbo", "w") do |dtbo|
        dtbo.write(input_stream.read)
      end
    rescue => e
      print "error raised:"
      p e
      Dir.rmdir(@device_tree_overlay_path)
      abort
    end
  end

  def load(format, filename, input_stream)
    puts "load(#{format}, #{filename}, #{input_stream})" if (@debug)
    load_dts(filename, input_stream) if (format == :dts)
    load_dtb(filename, input_stream) if (format == :dtb)
  end
    
  def install(format, filename, input_stream)
    puts "install(#{format}, #{filename}, #{input_stream})" if (@debug)
    create
    load(format, filename, input_stream)
    start
  end

  def remove
    begin
      Dir.rmdir(@device_tree_overlay_path)
    rescue => e
      print "error raised:"
      p e
      abort
    end
  end
end

class AlteraHps2Fpga

  def initialize
    @program_name      = "altera-hps2fpga.rb"
    @program_version   = "0.0.1"
    @program_id        = @program_name + " " + @program_version
    @verbose           = false
    @debug             = false
    @command           = Array.new
    @name              = "fpga-bridge"
    @devcfg            = DeviceTreeOverlayConfiguration.new(@name)
    @opt               = OptionParser.new do |opt|
      opt.program_name = @program_name
      opt.version      = @program_version
      opt.summary_width= 20
      opt.banner       = "Usage: altera-hps2fpga.rb [command]"
      opt.on('command')
      opt.on('-i', '--install', "Install (Create, Load, Start)"                   ){|val| @command << :install}
      opt.on('-r', '--remove' , "Remove Device Tree Overlay Directory to ConfigFS"){|val| @command << :remove }
    end
  end

  def parse_options(argv)
    @opt.order(argv) do |name|
      @name << name
    end
  end

  HPS2FPGA_RESET        = 96
  LWHPS2FPGA_RESET      = 97
  FPGA2HPS_RESET        = 98
  SYS_DEVICE_TREE_PATH  = "/sys/firmware/devicetree/base/"

  def get_handle(name)
    path_list = Dir::glob(SYS_DEVICE_TREE_PATH + "**/" + name + "/phandle")
    if path_list.size > 0 then
      return File.binread(path_list[0]).unpack("N").first
    else
      return nil
    end
  end

  def check_compatible
    comp_file_name = SYS_DEVICE_TREE_PATH + "compatible"
    return false if (File.exist?(comp_file_name) == false)
    comp_name_list = IO.read(comp_file_name).split(/\0/)
    return (comp_name_list.select{|name| name =~ /altr,socfpga/}.size > 0)
  end

  def device_tree_source(rst, l4_main_clk)
    return <<"  EOF"
/dts-v1/;
/ {
	#{@name}@0 {
		target-path = "/soc";
		__overlay__ {
			#address-cells = <0x1>;
			#size-cells = <0x1>;
			hps_fpgabridge0: fpgabridge@0 {
				compatible = "altr,socfpga-hps2fpga-bridge";
				label = "hps2fpga";
				resets = <#{rst} #{HPS2FPGA_RESET}>;
				reset-names = "hps2fpga";
				clocks = <#{l4_main_clk}>;
			};
		};
	};
	#{@name}@1 {
		target-path = "/soc";
		__overlay__ {
			#address-cells = <0x1>;
			#size-cells = <0x1>;
			hps_fpgabridge1: fpgabridge@1 {
				compatible = "altr,socfpga-lwhps2fpga-bridge";
				label = "lwhps2fpga";
				resets = <#{rst} #{LWHPS2FPGA_RESET}>;
				reset-names = "lwhps2fpga";
				clocks = <#{l4_main_clk}>;
			};
		};
	};
	#{@name}@2 {
		target-path = "/soc";
		__overlay__ {
			#address-cells = <0x1>;
			#size-cells = <0x1>;
			hps_fpgabridge2: fpgabridge@2 {
				compatible = "altr,socfpga-fpga2hps-bridge";
				label = "fpga2hps";
				resets = <#{rst} #{FPGA2HPS_RESET}>;
				reset-names = "fpga2hps";
				clocks = <#{l4_main_clk}>;
			};
		};
        };
	#{@name}@3 {
		target-path = "/soc";
		__overlay__ {
			#address-cells = <0x1>;
			#size-cells = <0x1>;
                        l3regs@0xff800000 {
                                compatible = "altr,l3regs", "syscon";
                                reg = <0xff800000 0x1000>;
        		};
                };
	};
};
  EOF
  end
  
  def devtree_install
    @devcfg.debug = @debug
    rst           = get_handle("rstmgr*")
    l4_main_clk   = get_handle("l4_main_clk*")
    dts           = device_tree_source(rst, l4_main_clk)
    @devcfg.install(:dts, "-", StringIO.new(dts));
  end

  def devtree_remove
    @devcfg.debug = @debug
    @devcfg.remove
  end
  
  def execute
    if @command.length == 0 then
      puts @opt
      exit
    end
    if check_compatible == false then
      puts "Not suport target"
      exit
    end
    @command.each do |command|
      case command
      when :install then
        devtree_install
        system("modprobe fpga-bridge")
        system("modprobe altera-hps2fpga")
      when :remove  then
        system("rmmod    altera-hps2fpga")
        system("rmmod    fpga-bridge")
        devtree_remove
      end
    end
  end
end

main = AlteraHps2Fpga.new
main.parse_options(ARGV)
main.execute
exit
