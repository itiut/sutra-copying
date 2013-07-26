array1 = [1, 2, 3, 4, 5]
array2 = [10, 20, 30, 40, 50]
array3 = [100, 200, 300, 400, 500]

result = []
array1.zip(array2, array3) do |a, b, c|
  result << a + b + c
end
p result
