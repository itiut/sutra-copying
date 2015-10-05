require 'rinda/ring'
require_relative 'ring_notify'

DRb.start_service

ts = Rinda::RingFinger.primary
ns = RingNotify.new(ts, :Hello)
ns.each do |_, _, hello, _|
  begin
    puts hello.greeting
  rescue
  end
end
