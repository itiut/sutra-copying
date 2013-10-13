class EvalTarget
end

e1 = EvalTarget.new
e2 = EvalTarget.new

EvalTarget.class_eval do
  def class_method
    :class_method
  end
end

p e1.class_method
p e2.class_method

e1.instance_eval do
  def unique_method
    :unique_method
  end
end

p e1.unique_method
p e2.unique_method
