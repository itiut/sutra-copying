class HaveMethod
  def has_method
    'has_method'
  end
end

class NotHaveMethod
end

have_method = HaveMethod.new
not_have_method = NotHaveMethod.new

p have_method.respond_to? :has_method
p not_have_method.respond_to? :has_method
