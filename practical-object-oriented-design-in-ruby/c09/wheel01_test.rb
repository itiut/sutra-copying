require_relative 'wheel01'
require_relative 'test_helper'
require 'minitest/autorun'

class WheelTest < Minitest::Test
  include DiameterizableInterfaceTest

  def setup
    @subject = @wheel = Wheel.new(26, 1.5)
  end

  def test_calculates_diameter
    wheel = Wheel.new(26, 1.5)

    assert_in_delta(29, wheel.diameter, 0.01)
  end
end
