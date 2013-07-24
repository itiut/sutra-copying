class HelloCount
  @@count = 0

  def self.count
    @@count
  end

  def initialize(myname="Ruby")
    @name = myname
  end

  def hello
    @@count += 1
    puts "Hello, world. I am #{@name}"
  end
end

bob = HelloCount.new("Bob")
alice = HelloCount.new("Alice")
ruby = HelloCount.new

p HelloCount::count
bob.hello
alice.hello
ruby.hello
p HelloCount::count
