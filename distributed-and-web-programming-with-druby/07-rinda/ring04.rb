require 'rinda/ring'

DRb.start_service

ts = Rinda::RingFinger.primary
array = ts.read_all([:name, :Hello, DRbObject, nil])
if array.empty?
  puts 'Hello: not found.'
  exit(1)
end
array.each do |_, _, hello, _|
  puts hello.greeting
end
