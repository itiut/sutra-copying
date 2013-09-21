def replace(array, from, to)
  array.each_with_index do |elem, i|
    array[i] = to if elem == from
  end
end

require 'test/unit'

class ReplaceTest < Test::Unit::TestCase
  def test_replace
    book_topics = ['html', 'java', 'css']
    replace(book_topics, 'java', 'ruby')
    expected = ['html', 'ruby', 'css']
    assert_equal expected, book_topics
  end
end


class Array
  def substitute(from, to)
    each_with_index do |elem, i|
      self[i] = to if elem == from
    end
  end
end

class ArrayExtensionsTest < Test::Unit::TestCase
  def test_substitute
    book_topics = ['html', 'java', 'css']
    book_topics.substitute('java', 'ruby')
    expected = ['html', 'ruby', 'css']
    assert_equal expected, book_topics
  end
end
