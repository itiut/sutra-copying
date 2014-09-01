require 'thread'
require 'rinda/ring'

class RingNotify
  def initialize(ts, kind, desc = nil)
    @queue = Queue.new
    pattern = [:name, kind, DRbObject, desc]
    open_stream(ts, pattern)
  end

  def pop
    @queue.pop
  end

  def each
    while tuple = @queue.pop
      yield(tuple)
    end
  end

  private

  def open_stream(ts, pattern)
    @notifier = ts.notify('write', pattern)
    ts.read_all(pattern).each do |tuple|
      @queue.push(tuple)
    end
    @writer = writer_thread
  end

  def writer_thread
    Thread.new do
      begin
        @notifier.each do |_, tuple|
          @queue.push(tuple)
        end
      rescue
        @queue.push(nil)
      end
    end
  end
end
