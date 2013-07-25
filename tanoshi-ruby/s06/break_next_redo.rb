puts "break example:"
i = 0
["perl", "python", "ruby", "scheme"].each do |lang|
  i += 1
  if i == 3
    break
  end
  p [i, lang]
end

puts "next example:"
i = 0
["perl", "python", "ruby", "scheme"].each do |lang|
  i += 1
  if i == 3
    next
  end
  p [i, lang]
end

puts "redo example:"
i = 0
["perl", "python", "ruby", "scheme"].each do |lang|
  i += 1
  if i == 3
    redo
  end
  p [i, lang]
end
