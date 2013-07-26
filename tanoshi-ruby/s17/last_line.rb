filename = ARGV[0]
last_line = File.readlines(filename)[-1]
File.open(filename, "w") do |file|
  file.puts(last_line)
end
