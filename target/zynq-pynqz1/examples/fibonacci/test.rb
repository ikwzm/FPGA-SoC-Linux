require_relative 'fibonacci_server'

fib = FibonacciServer.new

(0..43).to_a.each do |n|
  f = fib.fib(n)
  puts "#{n} => #{f}"
end
