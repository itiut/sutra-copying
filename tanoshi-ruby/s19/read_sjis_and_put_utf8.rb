File.open("sjis.txt", "w:sjis") do |file|
  file.puts "あいうえお"
end

File.open("sjis.txt", "r:sjis") do |file|
  print file.gets.encode("utf-8")
end
