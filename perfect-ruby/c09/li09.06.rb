class MethodInfo
  def sample_method
  end
end

obj = MethodInfo.new
sample_method = obj.method(:sample_method)

p sample_method.owner
p sample_method.name
p sample_method.receiver
p sample_method.receiver == obj
