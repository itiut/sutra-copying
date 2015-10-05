require 'drb/drb'
require 'rinda/rinda'
require 'rinda/tuplespace'

class MultipleNotify
  def initialize(ts, event, patterns)
    @queue = Queue.new
    @entries = []
    patterns.each do |pattern|
      make_listener(ts, event, pattern)
    end
  end

  def pop
    @queue.pop
  end

  private

  def make_listener(ts, event, pattern)
    entry = ts.notify(event, pattern)
    @entries.push(entry)

    Thread.new do
      entry.each do |ev|
        @queue.push(ev)
      end
    end
  end
end
