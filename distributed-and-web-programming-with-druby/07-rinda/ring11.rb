require 'rinda/ring'
require_relative 'div_cal'
require_relative 'ring_notify'

point = ARGV.shift || '/dcal'

DRb.start_service
bartender = Tofu::Bartender.new(DivCal::DivCallSession)

notifier = RingNotify.new(Rinda::RingFinger.primary, :Tofulet)
notifier.each do |_, _, tofulet, _|
  begin
    tofulet.mount(point, bartender)
  rescue
  end
end
