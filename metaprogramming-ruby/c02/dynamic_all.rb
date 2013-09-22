class MyClass
  def my_method(my_arg)
    my_arg * 2
  end

  private
  def my_private_method(arg)
    arg * 3
  end
end

obj = MyClass.new
p obj.my_method(3)
p obj.send(:my_method, 3)

p obj.send(:my_private_method, 3)
