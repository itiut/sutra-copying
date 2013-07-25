ltotal = 0
wtotal = 0
ctotal = 0

ARGV.each do |filename|
  begin
    file = File.open(filename)
    l = 0
    w = 0
    c = 0
    file.each_line do |line|
      l += 1
      c += line.size
      line.sub!(/^\s+/, "")
      array = line.split(/\s+/)
      w += array.size
    end
    file.close

    printf("%8d %8d %8d %s\n", l, w, c, filename)
    ltotal += l
    wtotal += w
    ctotal += c
  rescue => e
    puts e.message
  end
end

printf("%8d %8d %8d %s\n", ltotal, wtotal, ctotal, "total")
