class ParentClass
  def super_public_method; end

  private
  def super_private_method; end

  protected
  def super_protected_method; end
end

class ChildClass < ParentClass
  def public_method; end

  private
  def private_method; end

  protected
  def protected_method; end
end

child = ChildClass.new

def child.singleton_method; end

p child.methods
p child.public_methods
p child.private_methods
p child.protected_methods
p child.singleton_methods
