rand_num = rand(100)

puts 'hit a random number(0 to 100):'

while true
  input_num = gets.chomp.to_i
  if input_num < rand_num
    puts 'wrong. more bigger.'
  elsif input_num > rand_num
    puts 'wrong. more smaller.'
  else
    puts 'correct'
    break
  end
end
