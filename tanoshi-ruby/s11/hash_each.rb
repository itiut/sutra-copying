sum = 0
outcome = {"参加費" => 1000, "ストラップ代" => 1000, "懇親会費" => 4000}
outcome.each do |pair|
  sum += pair[1]
end
puts "合計: #{sum}"
