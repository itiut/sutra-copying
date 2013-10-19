class HasPrivateMethod
  private
  def private_method
    'private_method'
  end
end

has_private_method = HasPrivateMethod.new

p has_private_method.respond_to? :private_method
p has_private_method.respond_to? :private_method, true
