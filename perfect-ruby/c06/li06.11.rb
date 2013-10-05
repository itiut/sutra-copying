module IncludedModule
  def included_module_method
    :included_module_method
  end
end

class Klass
  include IncludedModule

  define_method :included_module_method, IncludedModule.instance_method(:included_module_method)
end

object = Klass.new
p object.included_module_method
