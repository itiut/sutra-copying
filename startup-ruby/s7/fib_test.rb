require 'test/unit'
require './fib'

class FibTest < Test::Unit::TestCase
  def setup
    @fib = Fib.new
  end

  def test_at1
    r = @fib.at 1
    assert_equal(0, r)
  end

  def test_at7
    r = @fib.at 7
    assert_equal(8, r)
  end

  def test_at0
    assert_raise RuntimeError do
      @fib.at 0
    end
  end

  def teardown

  end
end
