class OverrideMethodMissing
  def method_missing(name, *args)
    return 'target_method is called' if name == :target_method
    super
  end
end

p OverrideMethodMissing.new.target_method
p OverrideMethodMissing.new.no_method
