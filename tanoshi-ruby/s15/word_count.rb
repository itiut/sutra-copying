count = Hash.new(0)

File.open(ARGV[0]) do |f|
  f.each_line do |line|
    words = line.split
    words.each do |word|
      count[word] += 1
    end
  end
end

count.sort_by { |a| a[1] }.each do |key, value|
  print "#{key}: #{value}\n"
end
