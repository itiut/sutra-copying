double = Proc.new { |x| x * 2 }
p double.(3)

array = [1, 2, 3, 4, 5]
array_shift = array.method(:shift)

p array_shift.call


class Dog
  def bark
    puts 'wan!!'
  end
end

dog = Dog.new
bark_wan = dog.method(:bark)

class Dog
  def bark
    puts 'bowwow!!'
  end
end

dog.bark

bark_wan.call

def dog.bark
  puts 'kyankyan!!'
end

dog.bark

bark_wan.call
