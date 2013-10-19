class Hello
  protected
  def protected_hello
    'protected_hello'
  end

  private
  def private_hello
    'private hello'
  end
end

hello = Hello.new

p hello.send :protected_hello
p hello.send :private_hello
