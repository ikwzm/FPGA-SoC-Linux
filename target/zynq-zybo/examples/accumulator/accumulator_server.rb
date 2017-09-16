require 'msgpack'
require 'serialport'

class AccumulatorServer

  def initialize
    @port     = SerialPort.new("/dev/zptty0", 38400)
    @port.read_timeout = 1000
    @port.flow_control = SerialPort::HARD
    @unpacker = MessagePack::Unpacker.new(@port)
    @msgid    = 0
  end

  def call(method, args)
    @msgid = (@msgid+1) % 256
    req = [0, @msgid, method, args].to_msgpack
    @port.write(req)
    @unpacker.each do |obj|
      type, resid, error, result = obj
      if (error == nil) then
        return result
      else
        puts error
        return nil
      end
      break
    end 
  end

  def get_regs
    result = call('$GET', [{"reg" => nil}])
    if result != nil
      return result[0]["reg"]
    else
      return nil
    end 
  end

  def set_regs(arg)
    result = call('$SET', [{"reg" => arg}])
  end

  def add(arg)
    return call('add', [arg])
  end
end

