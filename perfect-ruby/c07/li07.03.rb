class DelegateArray
  def initialize
    @array = []
  end

  def method_missing(name, *args)
    @array.__send__ name, *args
  end
end

delegate_array = DelegateArray.new
p delegate_array << 1
p delegate_array << 2
