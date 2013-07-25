file = File.open(ARGV[0])
begin
  file.each_line do |line|
    puts line
  end
ensure
  file.close
end
