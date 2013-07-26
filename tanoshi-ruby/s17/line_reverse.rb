filename = ARGV[0]
lines = File.readlines(filename)
File.open(filename, "w") do |file|
  file.write(lines.reverse.join)
end
