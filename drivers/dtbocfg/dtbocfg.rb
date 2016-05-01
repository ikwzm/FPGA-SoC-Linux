#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#---------------------------------------------------------------------------------
#
#       Version     :   0.0.1
#       Created     :   2016/4/28
#       File name   :   dtbocfg.rb
#       Author      :   Ichiro Kawazome <ichiro_k@ca2.so-net.ne.jp>
#       Description :   dtbocfg(Device Tree Overlay Blob Configuration) 
#                       management script.
#
#---------------------------------------------------------------------------------
#
#       Copyright (C) 2014-2015 Ichiro Kawazome
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

class Dtbocfg
  def initialize
    @program_name      = "dtbocfg"
    @program_version   = "0.0.2"
    @program_id        = @program_name + " " + @program_version
    @verbose           = false
    @debug             = false
    @command           = Array.new
    @input             = Array.new
    @name              = Array.new
    @opt               = OptionParser.new do |opt|
      opt.program_name = @program_name
      opt.version      = @program_version
      opt.summary_width= 20
      opt.banner       = "Usage: dtbocfg [command] [options] device_name"
      opt.on('command')
      opt.on('-i', '--install', "Install (Create, Load, Start)"                   ){|val| @command << :install}
      opt.on('-s', '--start'  , "Append Device Tree Blob on ConfigFS to   System" ){|val| @command << :start  }
      opt.on('-t', '--stop'   , "Remove Device Tree Blob on ConfigFS from System" ){|val| @command << :stop   }
      opt.on('-l', '--load'   , "Load   Device Tree Overlay File to ConfigFS"     ){|val| @command << :load   }
      opt.on('-c', '--create' , "Create Device Tree Overlay Directory to ConfigFS"){|val| @command << :create }
      opt.on('-r', '--remove' , "Remove Device Tree Overlay Directory to ConfigFS"){|val| @command << :remove }
      opt.on('options')
      opt.on('--dts FILE_NAME', "Device Tree Source File" ){|val| @input << {:format => :dts, :filename => val}}
      opt.on('--dtb FILE_NAME', "Device Tree Blob File"   ){|val| @input << {:format => :dtb, :filename => val}}
      opt.on('-v', '--verbose'){|val| @verbose = true}
      opt.on('-d', '--debug'  ){|val| @debug   = true}
    end
  end

  def parse_options(argv)
    @opt.order(argv) do |name|
      @name << name
    end
  end

  def execute
    def device_tree_file_to_stream
      if @input.length == 0 then
        puts "error: Device Tree Overlay File must always be one without."
        puts @opt
        abort
      end
      if @input.length >  1 then
        puts "error: Device Tree Overlay File must not be specified only one."
        puts @opt
        abort
      end
      format   = @input[0][:format]
      filename = @input[0][:filename]
      ## puts "file = #{format} #{filename}"
      if filename == "-" then
        return {:format => format, :filename => filename, :stream => STDIN}
      else
        return {:format => format, :filename => filename, :stream => open(filename)}
      end
    end
    if @command.length == 0 then
      puts @opt
      exit
    end
    if @name.length == 0 then
      puts "error: device_name must always be one without."
      puts @opt
      abort
    end
    if @name.length >  1 then
      puts "error: device_name must not be specified only one."
      puts @opt
      abort
    end
    dev = DeviceTreeOverlayConfiguration.new(@name.first)
    dev.debug = @debug
    @command.each do |command|
      case command
      when :stop    then dev.stop
      when :start   then dev.start
      when :create  then dev.create
      when :remove  then dev.remove
      when :load    then
        file_info = device_tree_file_to_stream
        dev.load(   file_info[:format], file_info[:filename], file_info[:stream])
      when :install then
        file_info = device_tree_file_to_stream
        dev.install(file_info[:format], file_info[:filename], file_info[:stream])
      end 
    end
  end
end

dtbocfg = Dtbocfg.new
dtbocfg.parse_options(ARGV)
dtbocfg.execute
