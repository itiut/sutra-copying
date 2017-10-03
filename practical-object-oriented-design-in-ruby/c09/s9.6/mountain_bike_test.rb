require_relative 'mountain_bike'
require_relative 'test_helper'
require 'minitest/autorun'

class MountainBikeTest < Minitest::Test
  include BicycleInterfaceTest
  include BicycleSubclassTest

  def setup
    @bike = @subject = MountainBike.new
  end
end
