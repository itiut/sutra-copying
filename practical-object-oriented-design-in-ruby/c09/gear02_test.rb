require_relative 'gear02'
require_relative 'wheel01'
require_relative 'test_helper'
require 'minitest/autorun'

class DiameterDouble
  def diameter
    10
  end
end

class DiameterDoubleTest < Minitest::Test
  include DiameterizableInterfaceTest

  def setup
    @subject = DiameterDouble.new
  end
end


class GearTest < Minitest::Test
  def test_calculates_gear_inches
    gear = Gear.new(chainring: 52, cog: 11, wheel: Wheel.new(26, 1.5))

    assert_in_delta(137.1, gear.gear_inches, 0.01)
  end

  def test_calculates_gear_inches_with_double
    gear = Gear.new(chainring: 52, cog: 11, wheel: DiameterDouble.new)

    assert_in_delta(47.27, gear.gear_inches, 0.01)
  end
end
