class VirtualProxy
  def initialize(&creation_block)
    @creation_block = creation_block
  end

  def method_missing(name, *args, &block)
    subject.send(name, *args, &block)
  end

  def subject
    @subject ||= @creation_block.call
  end
end

array = VirtualProxy.new { Array.new }
array << 'hello'
array << 'out'
array << 'there'
p array
array.each { |e| puts e }
