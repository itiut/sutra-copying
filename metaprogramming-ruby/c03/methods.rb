class MyClass
  def initialize(value)
    @x = value
  end

  def my_method
    @x
  end
end

obj = MyClass.new(1)
m = obj.method :my_method
p m.call

unbound = m.unbind
another_obj = MyClass.new(2)
m = unbound.bind(another_obj)
p m.call
