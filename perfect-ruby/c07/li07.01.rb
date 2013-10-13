class QuotableString < String
  def quote
    "'#{self}'"
  end
end

quotable_string = QuotableString.new('quotable_string')
p quotable_string.quote
