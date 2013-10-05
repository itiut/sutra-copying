module IncludeModule
  def embedded_method
    :from_include_module
  end
end

module PrependModule
  def embedded_method
    :from_prepend_module
  end
end

class EmbeddedClass
  prepend PrependModule
  include IncludeModule

  def embedded_method
    :prepended_class
  end
end

embedded_obj = EmbeddedClass.new
p embedded_obj.embedded_method
