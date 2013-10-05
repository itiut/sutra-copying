module SuperCallModule
  def super_call_method
    super
  end
end

class OverrideClass
  prepend SuperCallModule

  def super_call_method
    :overrode
  end
end

p OverrideClass.new.super_call_method
