require_relative 'accumulator_server'

acc = AccumulatorServer.new

rnd = Random.new
acc_reg=1
acc.set_regs(acc_reg)
(0..1000).to_a.each do |n|
  num      = rnd.rand(0..10000)
  curr_reg = acc.get_regs
  add_reg  = acc.add(num)
  next_reg = acc.get_regs
  acc_reg  = acc_reg + num
  status   = ((acc_reg == next_reg) && (acc_reg == add_reg)) ? "OK" : "NG"
  puts "#{status} : reg = #{curr_reg}; add(#{num}) => #{add_reg}; reg = #{next_reg}"
end

acc_reg=1
acc.set_regs(acc_reg)
(0..1000).to_a.each do |n|
  num      = rnd.rand(-10000..0)
  curr_reg = acc.get_regs
  add_reg  = acc.add(num)
  next_reg = acc.get_regs
  acc_reg  = acc_reg + num
  status   = ((acc_reg == next_reg) && (acc_reg == add_reg)) ? "OK" : "NG"
  puts "#{status} : reg = #{curr_reg}; add(#{num}) => #{add_reg}; reg = #{next_reg}"
end

acc.call("sub", [1])
acc.call("add", 1)
acc.call("add", "a")
