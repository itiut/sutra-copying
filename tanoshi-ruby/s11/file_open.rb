File.open(ARGV[0]) do |file|
  file.each_line do |line|
    puts line
  end
end
