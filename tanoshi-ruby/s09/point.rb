class Point
  attr_reader :x, :y

  def initialize(x=0, y=0)
    @x, @y = x, y
  end

  def inspect
    "(#{x}, #{y})"
  end

  def +(other)
    self.class.new(x + other.x, y + other.y)
  end

  def -(other)
    self.class.new(x - other.x, y - other.y)
  end

  def +@
    dup
  end

  def -@
    self.class.new(-x, -y)
  end

  def ~@
    self.class.new(-y, x)
  end

  def [](index)
    case index
    when 0
      x
    when 1
      y
    else
      raise ArgumentError, "out of range `#{index}'"
    end
  end

  def []=(index, val)
    case index
    when 0
      @x = val
    when 1
      @y = val
    else
      raise ArgumentError, "out of range `#{index}'"
    end
  end
end

p0 = Point.new(3, 6)
p1 = Point.new(1, 8)

p p0
p p1
p p0 + p1
p p0 - p1

p (+ p0)
p (- p0)
p (~ p0)

p p0[0]
p p0[1] = 2
p p0[1]
p p0[2]
