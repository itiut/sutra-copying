class Arity
  def arity_variable_length(*x); end
  def arity_variable_length_with_default_arg(x, *y); end
  def arity_default_val_1(x = 1); end
  def arity_default_val_2(x, y = 1); end
end

arity_obj = Arity.new
p arity_obj.method(:arity_variable_length).arity
p arity_obj.method(:arity_variable_length_with_default_arg).arity
p arity_obj.method(:arity_default_val_1).arity
p arity_obj.method(:arity_default_val_2).arity
