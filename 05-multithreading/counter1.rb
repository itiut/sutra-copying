class Counter
  def initialize
    @mutex = Mutex.new
    @value = 0
  end

  attr_reader :value

  def up
    @mutex.synchronize do
      @value += 1
    end
  end
end

def test
  c = Counter.new

  t1 = Thread.new { 100_000.times { c.up } }
  t2 = Thread.new { 100_000.times { c.up } }

  t1.join
  t2.join

  c.value
end

p test
