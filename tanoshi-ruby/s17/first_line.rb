filename = ARGV[0]
File.open(filename, "r+") do |file|
  if file.gets
    file.truncate(file.pos)
  end
end
