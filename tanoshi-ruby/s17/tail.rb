def tail(n, filename)
  lines = File.readlines(filename)
  i_begin = (lines.size - n < 0) ? 0 : lines.size - n
  i_end = lines.size - 1
  (i_begin..i_end).each do |i|
    puts lines[i]
  end
end

tail(ARGV[1].to_i, ARGV[0])
