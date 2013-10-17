class MethodParameter
  def arity0(); end
  def arity1(x); end
  def arity1_and_default_val(x = 1); end
  def arity1_and_variable_arg(x, *y); end
  def arity1_and_block_arg(x, &y); end
end

method_params = MethodParameter.new

p method_params.method(:arity0).parameters
p method_params.method(:arity1).parameters
p method_params.method(:arity1_and_default_val).parameters
p method_params.method(:arity1_and_variable_arg).parameters
p method_params.method(:arity1_and_block_arg).parameters

p Kernel.method(:puts).parameters
