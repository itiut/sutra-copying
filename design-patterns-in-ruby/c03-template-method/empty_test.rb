require 'test/unit'

def empty?(s)
  s.length == 0
end

class EmptyTest < Test::Unit::TestCase
  def setup
    @empty_string = ''
    @one_char_string = 'X'
    @long_string = 'The rain in Spain'
    @empty_array = []
    @one_element_array = [1]
    @long_array = (1..6).to_a
  end

  def test_empty_on_strings
    assert empty?(@empty_string)
    assert !empty?(@one_char_string)
    assert !empty?(@long_string)
  end

  def test_empty_on_arrays
    assert empty?(@empty_array)
    assert !empty?(@one_element_array)
    assert !empty?(@long_array)
  end
end
