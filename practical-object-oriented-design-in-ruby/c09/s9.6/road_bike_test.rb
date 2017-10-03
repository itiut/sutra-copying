require_relative 'road_bike'
require_relative 'test_helper'
require 'minitest/autorun'

class RoadBikeTest < Minitest::Test
  include BicycleInterfaceTest
  include BicycleSubclassTest

  def setup
    @bike = @subject = RoadBike.new(tape_color: 'red')
  end

  def test_puts_tape_color_in_local_spares
    assert_equal('red', @bike.local_spares[:tape_color])
  end
end
