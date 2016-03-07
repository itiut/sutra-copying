require 'find'

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

class Bigger < Expression
  def initialize(size)
    @size = size
  end

  def evaluate(dir)
    super(dir).select { |p| File.size(p) > @size }
  end
end

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

class Or < Expression
  def initialize(expression1, expression2)
    @expression1 = expression1
    @expression2 = expression2
  end

  def evaluate(dir)
    @expression1.evaluate(dir) | @expression2.evaluate(dir)
  end
end

class And < Expression
  def initialize(expression1, expression2)
    @expression1 = expression1
    @expression2 = expression2
  end

  def evaluate(dir)
    @expression1.evaluate(dir) & @expression2.evaluate(dir)
  end
end

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
