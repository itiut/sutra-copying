add = Proc.new { |x, y| x + y }
inc = Proc.new { |y| add.(1, y) }

p inc.(1)
