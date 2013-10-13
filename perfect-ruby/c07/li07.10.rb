class EvalTarget
  def initialize
    @instance_val = 'instance_valiable'
  end

  def instance_binding
    local_val = 'local valiable'
    binding
  end

  private
  def private_method
    'private method'
  end
end

e1 = EvalTarget.new
binding_obj= e1.instance_binding

p eval '@instance_val', binding_obj
p eval 'local_val', binding_obj
p eval 'private_method', binding_obj

p binding_obj.eval '@instance_val'
p binding_obj.eval 'local_val'
p binding_obj.eval 'private_method'
