require 'rinda/ring'

class Hello
  def greeting
    'Hello, world.'
  end
end

hello = Hello.new
DRb.start_service(nil, hello)

provider = Rinda::RingProvider.new(:Hello, DRbObject.new(hello), 'Hello')
provider.provide

DRb.thread.join
