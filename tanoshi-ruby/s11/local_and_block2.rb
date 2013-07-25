x = y = z = 0
array = [1, 2, 3]

array.each do |x; y|
  y = x
  z = x
  p [x, y, z]
end

puts
p [x, y, z]
