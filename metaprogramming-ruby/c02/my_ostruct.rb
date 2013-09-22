class MyOpenStruct
  def initialize
    @attributes = {}
  end

  def method_missing(method, *args)
    attribute = method.to_s
    if attribute =~ /=$/
      @attributes[attribute.chop] = args[0]
    else
      @attributes[attribute]
    end
  end
end

icecream = MyOpenStruct.new
icecream.flavor = 'vanila'
p icecream.flavor
