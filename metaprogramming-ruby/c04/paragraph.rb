class Paragraph
  def initialize(text)
    @text = text
  end

  def title?
    @text.upcase == @text
  end

  def reverse
    @text.reverse
  end

  def upcase
    @text.upcase
  end
end

paragraph = 'any string can be a paragraph'

def paragraph.title?
  self.upcase == self
end

p paragraph.title?
