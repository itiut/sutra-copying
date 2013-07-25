file = File.open(ARGV[0])
file.each_line do |line|
  puts line
end
file.close
