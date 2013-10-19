class Hello
  def hi
    'hi'
  end

  def hello(name)
    "hello #{name}"
  end
end

hello = Hello.new
p hello.send :hi
p hello.send :hello, 'Bob'
