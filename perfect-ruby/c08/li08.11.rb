args_proc = Proc.new { |x, y| [x, y] }
p args_proc[1, 2, 3]
p args_proc[1]
p args_proc[[1, 2]]
