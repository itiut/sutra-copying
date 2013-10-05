module BeforeHelloFilter
  def hello
    'Hi! ' + super
  end
end

class Hello
  prepend BeforeHelloFilter

  def hello
    'hello'
  end
end

p Hello.new.hello
