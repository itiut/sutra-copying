require 'find'
require 'pp'

class Expression
  def evaluate(dir)
    Find.find(dir).select { |p| File.file?(p) }
  end

  def |(other)
    Or.new(self, other)
  end

  def &(other)
    And.new(self, other)
  end
end

class All < Expression
end

class FileName < Expression
  def initialize(pattern)
    @pattern = pattern
  end

  def evaluate(dir)
    super(dir).select { |p| File.fnmatch(@pattern, File.basename(p)) }
  end
end

expr_all = All.new
files = expr_all.evaluate('test_dir')
p files

expr_mp3 = FileName.new('*.mp3')
mp3s = expr_mp3.evaluate('test_dir')
p mp3s

class Bigger < Expression
  def initialize(size)
    @size = size
  end

  def evaluate(dir)
    super(dir).select { |p| File.size(p) > @size }
  end
end

expr_bigger = Bigger.new(0)
p expr_bigger.evaluate('test_dir')

class Writable < Expression
  def evaluate(dir)
    super(dir).select { |p| File.writable?(p) }
  end
end

class Not < Expression
  def initialize(expression)
    @expression = expression
  end

  def evaluate(dir)
    super(dir) - @expression.evaluate(dir)
  end
end

expr_not_writable = Not.new(Writable.new)
p expr_not_writable.evaluate('test_dir')

expr_empty = Not.new(Bigger.new(0))
p expr_empty.evaluate('test_dir')

expr_not_mp3 = Not.new(FileName.new('*.mp3'))
p expr_not_mp3.evaluate('test_dir')

class Or < Expression
  def initialize(expression1, expression2)
    @expression1 = expression1
    @expression2 = expression2
  end

  def evaluate(dir)
    @expression1.evaluate(dir) | @expression2.evaluate(dir)
  end
end

expr_big_oir_mp3 = Or.new(Bigger.new(0), FileName.new('*mp3'))
p expr_big_oir_mp3.evaluate('test_dir')

class And < Expression
  def initialize(expression1, expression2)
    @expression1 = expression1
    @expression2 = expression2
  end

  def evaluate(dir)
    @expression1.evaluate(dir) & @expression2.evaluate(dir)
  end
end

complex_expression = And.new(
  And.new(Bigger.new(1024), FileName.new('*.mp3')),
  Not.new(Writable.new)
)
pp complex_expression

class Parser
  def initialize(text)
    @tokens = text.scan(/\(|\)|[\w\.\*]+/)
  end

  def next_token
    @tokens.shift
  end

  def expression
    token = next_token
    case token
    when nil
      nil
    when '('
      result = expression
      fail 'Expected )' unless next_token == ')'
      result
    when 'all'
      All.new
    when 'writable'
      Writable.new
    when 'bigger'
      Bigger.new(next_token.to_i)
    when 'filename'
      FileName.new(next_token)
    when 'not'
      Not.new(expression)
    when 'and'
      And.new(expression, expression)
    when 'or'
      Or.new(expression, expression)
    else
      fail "Unexpected token: #{token}"
    end
  end
end

parser = Parser.new('and (and (bigger 1024) (filename *.mp3)) writable')
ast = parser.expression
pp ast

pp (Bigger.new(2000) & Not.new(Writable.new)) | FileName.new('*.mp3')

def all
  All.new
end

def bigger(size)
  Bigger.new(size)
end

def file_name(pattern)
  FileName.new(pattern)
end

def except(expression)
  Not.new(expression)
end

def writable
  Writable.new
end

pp (bigger(2000) & except(writable)) | file_name('*.mp3')
