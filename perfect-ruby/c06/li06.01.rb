klass_object = nil

ThirdClass = Class.new do |klass|
  klass_object = klass
  p klass == self

  def hello
    :hello
  end
end

p klass_object == ThirdClass

third_class_instance = ThirdClass.new
p third_class_instance.hello
