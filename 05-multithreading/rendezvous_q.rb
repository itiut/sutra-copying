require 'thread'

class Rendezvous
  def initialize
    super
    @send_queue = SizedQueue.new(1)
    @recv_queue = SizedQueue.new(1)
  end

  def send(obj)
    @send_queue.push(obj)
    @recv_queue.pop
  end

  def recv
    @send_queue.pop
  ensure
    @recv_queue.push(nil)
  end
end
