require 'thread'

class SemQ
  def initialize(n)
    @queue = Queue.new
    n.times { up }
  end

  def synchronize
    succ = down
    yield
  ensure
    up if succ
  end

  private

  def up
    @queue.push(true)
  end

  def down
    @queue.pop
  end
end
