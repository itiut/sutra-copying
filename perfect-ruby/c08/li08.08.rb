lambda_obj = lambda { 1 }
p lambda_obj.class
p lambda_obj.call

inc = ->(x) { x + 1 }
p inc.(2)


def proc_return
  Proc.new { return 1; puts :unreachable}.call
  :unreachable
end

proc_return

# Proc.new { return 1; puts :unreachable }.call

p lambda { return 1; puts :unreachable }.call

def lambda_return
  ->() { return 1; puts :unreachable}.call
  :reachable
end

p lambda_return
