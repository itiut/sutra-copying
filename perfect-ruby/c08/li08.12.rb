args_lambda = ->(x, y) { [x, y] }
# p args_lambda[1, 2, 3]
# p args_lambda[1]
# p args_lambda[[1, 2]]

p proc {}.lambda?
p ->() {}.lambda?

1.method(:+).to_proc.lambda?
