require_relative 'bicycle'
require_relative 'test_helper'
require 'minitest/autorun'

class StubbedBike < Bicycle
  def default_tire_size
    0
  end

  def local_spares
    { saddle: 'painful' }
  end
end

class StubbedBikeTest < Minitest::Test
  include BicycleSubclassTest

  def setup
    @subject = StubbedBike.new
  end
end

class BicycleTest < Minitest::Test
  include BicycleInterfaceTest

  def setup
    @bike = @subject = Bicycle.new(tire_size: 0)
    @stubbed_bike = StubbedBike.new
  end

  def test_forces_subclasses_to_implement_default_tire_size
    assert_raises(NotImplementedError) do
      @bike.default_tire_size
    end
  end

  def test_includes_local_spares_in_spares
    assert_equal(@stubbed_bike.spares, {
      tire_size: 0,
      chain: '10-speed',
      saddle: 'painful',
    })
  end
end
