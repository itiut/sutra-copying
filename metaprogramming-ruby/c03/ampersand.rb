def math(a, b)
  yield(a, b)
end

def teach_math(a, b, &operation)
  puts "さあ、計算を始めよう："
  puts math(a, b, &operation)
end

teach_math(2, 3) { |x, y| x * y }


def my_method(&the_proc)
  the_proc
end

p = my_method { |name| "Hello, #{name}!"}
puts p.class
puts p.call('Bill')
