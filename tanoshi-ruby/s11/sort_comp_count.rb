array = %w(
Ruby is a open source programming language with a focus on simplicity and productivity. It has an elegant syntax that is natural to read and easy to write
)

call_num = 0
sorted = array.sort do |a, b|
  call_num += 1
  a.size <=> b.size
end

# sorted = array.sort_by do |item|
#   call_num += 1
#   item.size
# end

puts "ソートの結果 #{sorted}"
puts "配列の要素数 #{sorted.size}"
puts "ブロックの呼び出し回数 #{call_num}"
