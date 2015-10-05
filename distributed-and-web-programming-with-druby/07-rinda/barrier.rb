class Barrier
  def initialize(ts, n, name = nil)
    @ts = ts
    @name = name || self
    @ts.write([key, n])
  end

  def sync
    _, value = @ts.take([key, nil])
    @ts.write([key, value - 1])
    @ts.read([key, 0])
  end

  private

  def key
    @name
  end
end
