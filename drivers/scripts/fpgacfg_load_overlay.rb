#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

SYS_DEVICE_TREE_PATH   = "/sys/firmware/devicetree/base/"
CONFIG_OF_OVERLAY_PATH = "/config/device-tree/overlays/"

def find_fpga_manager(name)
  device_list = Array.new
  path_list   = `find #{SYS_DEVICE_TREE_PATH} -name #{name} -print`.split("\n")
  path_list.each do |path|
    fpga_manager_path = path.gsub(/^#{SYS_DEVICE_TREE_PATH}/, "")
    target_path       = fpga_manager_path.split("/").first
    device_list << {:fpga_manager_path => "/" + fpga_manager_path, :target_path => "/" + target_path}
  end 
  return device_list
end

def make_device_tree_source(device_name, target_path, fpga_manager_path)
  return <<"EOT"
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

def load_device_tree_overlay(device_name, target_path, fpga_manager_path)
  device_tree_overlay_path = CONFIG_OF_OVERLAY_PATH + device_name
  begin
    Dir.mkdir(device_tree_overlay_path)
  rescue => e
    print "error raised:"
    p e
    abort
  end
  begin 
    IO.popen("dtc -I dts -O dtb -o #{device_tree_overlay_path}/dtbo", "r+") do |io|
      io.puts make_device_tree_source(device_name, target_path, fpga_manager_path)
    end
    File.write("#{device_tree_overlay_path}/status", "1")
  rescue => e
    print "error raised:"
    p e
    Dir.rmdir(device_tree_overlay_path)
    abort
  end
end

device_list = Array.new
device_list.concat(find_fpga_manager("devcfg*" ))
device_list.concat(find_fpga_manager("fpgamgr*"))

device_list.each_index do |device_num|
  device_name = "fpgacfg#{device_num}"
  device_info = device_list[device_num]
  load_device_tree_overlay(device_name, device_info[:target_path], device_info[:fpga_manager_path])
end
