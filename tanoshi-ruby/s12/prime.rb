def prime?(num)
  if num < 2
    return false
  end
  (2..Math.sqrt(num)).each do |i|
    if num % i == 0
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
