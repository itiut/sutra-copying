sum_proc = Proc.new { |a, b| a + b }
p sum_proc === [1, 2]


def what_class(obj)
  case obj
  when proc { |x| x.kind_of? String }
    String
  when proc { |x| x.kind_of? Numeric }
    Numeric
  else
    Class
  end
end

p what_class 'string'
p what_class 1
p what_class []
