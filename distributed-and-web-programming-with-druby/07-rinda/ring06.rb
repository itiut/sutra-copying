require 'rinda/ring'
require_relative 'ring_notify'

DRb.start_service

ts = Rinda::RingFinger.primary
ns = RingNotify.new(ts, :Hello)
ns.each do |_, _, hello, _|
  puts hello.greeting
end
