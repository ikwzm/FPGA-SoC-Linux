#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#---------------------------------------------------------------------------------
#
#       Version     :   0.0.1
#       Created     :   2016/4/28
#       File name   :   fpgacfg-service.rb
#       Author      :   Ichiro Kawazome <ichiro_k@ca2.so-net.ne.jp>
#       Description :   fpgacfg(FPGA Configuration Interface for Linux FPGA
#                       Manager Framework) service management script.
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

class FpgacfgService
  def initialize
    @program_name      = "fpgacfg-service.rb"
    @program_version   = "0.0.2"
    @program_id        = @program_name + " " + @program_version
    @verbose           = false
    @debug             = false
    @command           = Array.new
    @name              = Array.new
    @device_list       = make_device_list
    @opt               = OptionParser.new do |opt|
      opt.program_name = @program_name
      opt.version      = @program_version
      opt.summary_width= 20
      opt.banner       = "Usage: dtbocfg [command] [options] [device_name]"
      opt.on('command')
      opt.on('-i', '--install', "Install (Create, Load, Start)"                   ){|val| @command << :install}
      opt.on('-s', '--start'  , "Append Device Tree Blob on ConfigFS to   System" ){|val| @command << :start  }
      opt.on('-t', '--stop'   , "Remove Device Tree Blob on ConfigFS from System" ){|val| @command << :stop   }
      opt.on('-l', '--load'   , "Load   Device Tree Overlay File to ConfigFS"     ){|val| @command << :load   }
      opt.on('-c', '--create' , "Create Device Tree Overlay Directory to ConfigFS"){|val| @command << :create }
      opt.on('-r', '--remove' , "Remove Device Tree Overlay Directory to ConfigFS"){|val| @command << :remove }
      opt.on('options')
      opt.on('-v', '--verbose'){|val| @verbose = true}
      opt.on('-d', '--debug'  ){|val| @debug   = true}
      opt.on('device_name')
      opt.on_tail("    " + @device_list.collect{|dev| dev[:name]}.join(", "))
    end
  end

  def parse_options(argv)
    @opt.order(argv) do |name|
      @name << name
    end
  end

  def device_tree_source(device_name, target_path, fpga_manager_path)
    return <<"  EOT"
/dts-v1/;
/ {
        fragment@0 {
                target-path = "#{target_path}";
                __overlay__ {
                        #{device_name} {
                                compatible        = "ikwzm,fpgacfg-0.10.a";
                                fpga-manager-path = "#{fpga_manager_path}";
                        };
                };
        };
};
  EOT
  end

  SYS_DEVICE_TREE_PATH  = "/sys/firmware/devicetree/base/"

  def find_fpga_manager(name)
    device_list = Array.new
    path_list   = Dir::glob(SYS_DEVICE_TREE_PATH + "**/" + name)
    path_list.each do |path|
      fpga_manager_path = "/" + path.gsub(/^#{SYS_DEVICE_TREE_PATH}/, "")
      target_path       = File::dirname(fpga_manager_path)
      device_list << {:fpga_manager_path => fpga_manager_path, :target_path => target_path}
    end 
    return device_list
  end

  def make_device_list
    device_list = Array.new
    device_list.concat(find_fpga_manager("devcfg*" ))
    device_list.concat(find_fpga_manager("fpgamgr*"))
    device_list.each_index do | device_num |
      device_list[device_num][:name] = "fpgacfg#{device_num}"
    end
    return device_list
  end

  def execute
    if @command.length == 0 then
      puts @opt
      exit
    end
    if @name.length == 0 then
      device_list = @device_list
    else
      device_list = Array.new
      @name.each do | name |
        found_list  =  @device_list.select{|dev| dev[:name] == name}
        if (found_list.length == 0)
          abort("can not found #{name}\n")
        end
        device_list.concat(found_list)
      end
    end
    device_list.each do |device|
      devcfg = DeviceTreeOverlayConfiguration.new(device[:name])
      devcfg.debug = @debug
      @command.each do |command|
        case command
        when :stop    then devcfg.stop
        when :start   then devcfg.start
        when :create  then devcfg.create
        when :remove  then devcfg.remove
        when :load    then
          dts = device_tree_source(device[:name], device[:target_path], device[:fpga_manager_path])
          devcfg.load(   :dts, "-", StringIO.new(dts));
        when :install then
          dts = device_tree_source(device[:name], device[:target_path], device[:fpga_manager_path])
          devcfg.install(:dts, "-", StringIO.new(dts));
        end
      end
    end
  end
end

main = FpgacfgService.new
main.parse_options(ARGV)
main.execute
exit
