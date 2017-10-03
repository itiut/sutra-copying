require_relative 'trip_coordinator'
require_relative 'test_helper'
require 'minitest/autorun'

class TripCoordinatorTest < Minitest::Test
  include PreparerInterfaceTest

  def setup
    @trip_coordinator = @subject = TripCoordinator.new
  end
end
