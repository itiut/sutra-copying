class BaseClass
  def hello
    :hello
  end
end

base_object = BaseClass.new
p base_object.hello


class InheritClass < BaseClass
end

inherit_object = InheritClass.new
p inherit_object.hello


def base_object.hello
  :singleton_method_hello
end

p base_object.hello


module HelloModule
  def hello_from_module
    :hello_from_module
  end
end

class InheritClass
  include HelloModule
end

p inherit_object.hello_from_module


module ByeModule
  def hello_from_module
    :hello_from_bye_module
  end
end

class MixinClass < BaseClass
  include HelloModule
  include ByeModule
  include HelloModule
end

p MixinClass.new.hello_from_module
