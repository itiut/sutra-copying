def prefix(array, obj)
  result = []
  array.each do |item|
    result << item
    if item == obj
      return result
    end
  end
  return result
end

p prefix([1,2,3,4,5], 3)
