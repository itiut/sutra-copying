a = (1..100).to_a
p a
p a[99]

a2 = a.collect{|elem| elem * 2}
p a2

# a.collect!{|elem| elem * 2}
# p a

a3 = a.select{|elem| elem % 3 == 0}
p a3

p a.reverse

p a.inject(:+)

result = []
10.times do |i|
  result << a[i * 10, 10]
end
p result

def sum_array(a1, a2)
  if a1.size > a2.size
    a1, a2 = a2, a1
  end
  result = []
  a1.zip(a2) do |e1, e2|
    result << e1 + e2
  end
  result
end

p sum_array([1,2,3], [4,6,8])
