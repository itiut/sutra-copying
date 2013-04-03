# definition of function
def tell_the_truth
  true
end


# array
animals = ['lions', 'tigers', 'bears']
puts animals
animals[0]
animals[2]
animals[10]
animals[-1]
animals[-2]
animals[0..1]

(0..1).class

[].class
[].methods.include?(:[])

a[0] = 0

a = []
a[0] = 'zero'
a[1] = 1
a[2] = ['two', 'things']
a

a = [[1, 2, 3], [10, 20, 30], [40, 50, 60]]
a[0][0]
a[1][2]

a = [1]
a.push(1)

a = [1]
a.push(2)
a.pop
a.pop

# hash
numbers = {1 => 'one', 2 => 'two'}
numbers[1]
numbers[2]

stuff = {:array => [1, 2, 3], :string => 'Hi, mom!'}
stuff[:array]
stuff[:string]

'string'.object_id
:string.object_id

def tell_the_truth(options = {})
  if options[:profession] == :lawyer
    'it could be believed that this is almost certainly not false.'
  else
    true
  end
end

tell_the_truth
tell_the_truth :profession => :lawyer


# code block and yield
3.times {puts 'hiya there, kiddo'}

animals = ['lions and ', 'tigers and', 'bears', 'oh my']
animals.each {|a| puts a}

class Fixnum
  def my_times
    i = self
    while i > 0
      i -= 1
      yield
    end
  end
end

3.my_times {puts 'mangy moose'}

def call_block(&block)
  block.call
end

def pass_block(&block)
  call_block(&block)
end

pass_block {puts 'Hello, block'}


# definition of class
4.class
4.class.superclass
4.class.superclass.superclass
4.class.superclass.superclass.superclass
4.class.superclass.superclass.superclass.superclass
4.class.superclass.superclass.superclass.superclass.superclass

4.class.class
4.class.class.superclass
4.class.class.superclass.superclass
4.class.class.superclass.superclass.superclass

class Tree
  attr_accessor :children, :node_name

  def initialize(name, children=[])
    @children = children
    @node_name = name
  end

  def visit_all(&block)
    visit &block
    children.each {|c| c.visit_all &block}
  end

  def visit(&block)
    block.call self
  end
end

ruby_tree = Tree.new('Ruby',
                     [Tree.new('Reia'),
                      Tree.new('MacRuby')])
puts 'Visiting a node'
ruby_tree.visit {|node| puts node.node_name}
puts

puts 'Visiting entire tree'
ruby_tree.visit_all {|node| puts node.node_name}
puts


# mixin
module ToFile
  def filename
    "object_#{self.object_id}.txt"
  end

  def to_f
    File.open(filename, 'w') {|f| f.write(to_s)}
  end
end

class Person
  include ToFile
  attr_accessor :name

  def initialize(name)
    @name = name
  end

  def to_s
    name
  end
end

Person.new('matz').to_f


# moudle, enumerable, set
'begin' <=> 'end'
'same' <=> 'same'

a = [5, 3, 4, 1]
a.sort
a.any? {|i| i > 6}
a.any? {|i| i > 4}
a.all? {|i| i > 4}
a.all? {|i| i > 0}
a.collect {|i| i * 2}
a.select {|i| i % 2 == 0}
a.select {|i| i % 2 == 1}
a.max
a.min
a.member?(2)

a.inject(0) {|sum, i| sum + i}
a.inject {|sum, i| sum + i}
a.inject {|product, i| product * i}


a.inject(0) do |sum, i|
  puts "sum: #{sum}\t i: #{i}\t sum + i: #{sum + i}"
  sum + i
end
