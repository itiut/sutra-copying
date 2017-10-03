require_relative 'mechanic'
require_relative 'test_helper'
require 'minitest/autorun'

class MechanicTest < Minitest::Test
  include PreparerInterfaceTest

  def setup
    @mechanic = @subject = Mechanic.new
  end
end
