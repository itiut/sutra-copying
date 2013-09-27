def explore_array(method, *args)
  ['a', 'b', 'c'].send(method, *args)
end

loop do
  p explore_array(gets.chomp)
end
