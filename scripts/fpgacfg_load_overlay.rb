#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

SYS_DEVICE_TREE_PATH   = "/sys/firmware/devicetree/base/"

class Dtbocfg

  CONFIG_OF_OVERLAY_PATH = "/config/device-tree/overlays/"
  attr_reader :device_name
  
  def initialize(device_name)
    @device_name = device_name
  end

  def create(device_tree_source)
    device_tree_overlay_path = CONFIG_OF_OVERLAY_PATH + @device_name
    begin
      Dir.mkdir(device_tree_overlay_path)
    rescue => e
      print "error raised:"
      p e
      abort
    end
    begin 
      IO.popen("dtc -I dts -O dtb -o #{device_tree_overlay_path}/dtbo", "r+") do |io|
        io.puts device_tree_source
      end
      File.write("#{device_tree_overlay_path}/status", "1")
    rescue => e
      print "error raised:"
      p e
      Dir.rmdir(device_tree_overlay_path)
      abort
    end
  end

  def release
    device_tree_overlay_path = CONFIG_OF_OVERLAY_PATH + @device_name
    begin
      Dir.rmdir(device_tree_overlay_path)
    rescue => e
      print "error raised:"
      p e
      abort
    end
  end
end

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

device_list = Array.new
device_list.concat(find_fpga_manager("devcfg*" ))
device_list.concat(find_fpga_manager("fpgamgr*"))

device_list.each_index do |device_num|
  device_name        = "fpgacfg#{device_num}"
  target_path        = device_list[device_num][:target_path]
  fpga_manager_path  = device_list[device_num][:fpga_manager_path]
  device_tree_config = Dtbocfg.new(device_name)
  device_tree_source = <<"EOT"
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
  device_tree_config.create(device_tree_source)
end
