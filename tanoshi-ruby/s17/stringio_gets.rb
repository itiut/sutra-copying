require "stringio"

io = StringIO.new("A\nB\nB\n")
while str = io.gets
  p str
end
