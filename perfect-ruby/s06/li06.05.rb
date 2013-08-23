class Klass
  @class_instance_val = :class_instance_val
  @@class_val = :class_val
end

class InheritKlass < Klass
  p @class_instance_val
  p @@class_val
end
