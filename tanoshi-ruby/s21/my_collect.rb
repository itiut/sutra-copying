def my_collect(obj, &block)
  result = []
  obj.each do |item|
    if block
      result << block.call(item)
    else
      result << item
    end
  end
  result
end

array = my_collect([1, 2, 3, 4, 5]) do |i|
  i * 2
end

p array
