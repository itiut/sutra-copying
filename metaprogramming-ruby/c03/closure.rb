def my_method
  x = 'Google'
  yield('cruel')
end

x = 'Hello'
p my_method { |y| "#{x}, #{y} world" }
