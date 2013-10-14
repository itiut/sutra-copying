# Proc.new { break; puts :unreachable }.call

def proc_break
  Proc.new { break 1; puts :unreachable }.call
end

# proc_break

p ->() { break 1; puts :unreachable }.call

def lambda_break
  ->() { break 1; puts :unreachable }.call
  :reachable
end

p lambda_break


def wrap_method(proc_or_lambda)
  x = proc_or_lambda.call(1)
  x.to_s
end

p wrap_method proc { |x| next x; x.succ }
p wrap_method ->(x) { next x; x.succ }
