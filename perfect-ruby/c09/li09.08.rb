class SuperKlass
  def super_method
    self.class
  end
end

class Klass < SuperKlass
end

class NotInheritKlass
  def super_method
    self.class
  end
end

super_klass = SuperKlass.new
klass = Klass.new
not_inherit_klass = NotInheritKlass.new

unbind_super_method = SuperKlass.instance_method(:super_method)

p unbind_super_method.bind(super_klass).call

p unbind_super_method.bind(klass).call

p unbind_super_method.bind(not_inherit_klass).call
