l = w = c = 0
File.open(ARGV[0]) do |file|
  file.each_line do |line|
    l += 1
    words = line.chomp.split(/\s+/).delete_if { |word| word.empty? }
    w += words.size
    c += line.size
  end
end
puts "line: #{l}"
puts "word: #{w}"
puts "char: #{c}"
