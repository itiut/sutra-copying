add = Proc.new { |x, y| x + y }
inc = add.curry.(1)

p inc.(2)

append_prefix_atmark = add.curry.('@')
p append_prefix_atmark.('takkanm')
