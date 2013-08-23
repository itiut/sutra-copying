class Klass
  @class_instance_val = :class_instance_val

  def self.class_instance_val
    @class_instance_val
  end
end

p Klass.class_instance_val
