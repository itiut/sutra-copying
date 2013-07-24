class HelloWorld
  attr_accessor :name
  Version = "1.0"

  def initialize(myname="Ruby")
    @name = myname
  end

  def hello
    puts "Hello, world. I am #{@name}."
  end

  def greet
    puts "Hi, I am #{self.name}"
  end

  # def name
  #   @name
  # end

  # def name=(value)
  #   @name = value
  # end

  class << self
    def hello(name)
      puts "#{name} said hello."
    end
  end
end

bob = HelloWorld.new("Bob")
alice = HelloWorld.new("Alice")
ruby = HelloWorld.new

bob.hello
alice.hello
ruby.hello

p bob.name
bob.name = "Robert"
p bob.name

bob.greet

HelloWorld::hello("John")

p HelloWorld::Version
