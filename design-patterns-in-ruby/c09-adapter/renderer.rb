class Renderer
  def render(text_object)
    text = text_object.text
    size = text_object.size_inches
    color = text_object.color

    # render string...
  end
end

class TextObject
  attr_accessor :text, :size_inches, :color

  def initialize(text, size_inches, color)
    @text = text
    @size_inches = size_inches
    @color = color
  end
end

class BritishTextObject
  attr_accessor :string, :size_mm, :colour

  def initialize(string, size_mm, colour)
    @string = string
    @size_mm = size_mm
    @colour = colour
  end
end

class BritishTextObjectAdapter < TextObject
  def initialize(bto)
    @bto = bto
  end

  def text
    @bto.string
  end

  def size_inches
    @bto.size_mm / 25.4
  end

  def color
    @bto.colour
  end
end

bto = BritishTextObject.new('hello', 50.8, :blue)

bto_adapter = BritishTextObjectAdapter.new(bto)
puts bto_adapter.text
puts bto_adapter.size_inches
puts bto_adapter.color
puts

class << bto
  def text
    string
  end

  def size_inches
    size_mm / 25.4
  end

  def color
    colour
  end
end

puts bto.text
puts bto.size_inches
puts bto.color
