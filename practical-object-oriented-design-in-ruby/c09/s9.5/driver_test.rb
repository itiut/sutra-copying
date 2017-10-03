require_relative 'driver'
require_relative 'test_helper'
require 'minitest/autorun'

class DriverTest < Minitest::Test
  include PreparerInterfaceTest

  def setup
    @driver = @subject = Driver.new
  end
end
