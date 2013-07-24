class String
  def count_word
    self.split(/\s+/).size
  end
end

str = "Just Another Ruby Newbie"
p str.count_word
