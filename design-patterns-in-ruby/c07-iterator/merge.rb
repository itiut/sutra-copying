class ArrayIterator
  def initialize(array)
    @array = array
    @index = 0
  end

  def has_next?
    @index < @array.length
  end

  def item
    @array[@index]
  end

  def next_item
    value = @array[@index]
    @index += 1
    value
  end
end

def merge(array1, array2)
  merged = []

  iter1 = ArrayIterator.new(array1)
  iter2 = ArrayIterator.new(array2)

  while iter1.has_next? && iter2.has_next?
    if iter1.item < iter2.item
      merged << iter1.next_item
    else
      merged << iter2.next_item
    end
  end

  merged << iter1.next_item while iter1.has_next?
  merged << iter2.next_item while iter2.has_next?

  merged
end

array1 = (10...100).to_a.sample(10).sort
array2 = (10...100).to_a.sample(10).sort

print 'array1:'
array1.each { |e| print ' ', e }
puts

print 'array2:'
array2.each { |e| print ' ', e }
puts

merged = merge(array1, array2)
print 'merged:'
merged.each { |e| print ' ', e }
puts
