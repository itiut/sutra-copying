class Klass
  @class_instance_val = :class_instance_val
  @@class_val = :class_val

  def instance_method
    p @class_instance_val
    p @@class_val
  end
end

klass = Klass.new
klass.instance_method
