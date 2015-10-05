require 'rinda/rinda'
require 'rinda/ring'

DRb.start_service

ts = Rinda::RingFinger.primary
_, _, hello, _ = ts.read([:name, :Hello, DRbObject, nil])
puts hello.greeting
