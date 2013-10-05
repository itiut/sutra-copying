class Klass
  define_method :instance_method, -> { :instance_method }
end

object = Klass.new
p object.instance_method
