def prime?(num)
  if num < 2
    return false
  end
  num_i = num.to_i
  2.upto(num_i - 1) do |i|
    if num_i % i == 0
      return false
    end
  end
  true
end

(1..100).each do |i|
  if prime?(i)
    puts i
  end
  # puts "#{i}, #{prime?(i)}"
end
