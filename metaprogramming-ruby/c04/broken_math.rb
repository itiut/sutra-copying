class Fixnum
  alias :old_plus :+

  def +(arg)
    self.old_plus(arg).old_plus(1)
  end
end

require 'test/unit'

class BrokenMathTest < Test::Unit::TestCase
  def test_math_is_broken
    assert_equal 1, 1
    assert_equal 3, 1 + 1
    assert_equal 1, -1 + 1
    assert_equal 111, 100 + 10
  end
end
