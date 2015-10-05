class TSStruct
  def initialize(ts, name, struct = nil)
    @ts = ts
    @name = name || self
    return unless struct
    struct.each_pair do |key, value|
      @ts.write([@name, key, value])
    end
  end

  attr_reader :name

  def [](key)
    tuple = @ts.read([name, key, nil])
    tuple[2]
  end

  def []=(key, value)
    replace(key) { |_| value }
  end

  def replace(key)
    tuple = @ts.take([name, key, nil])
    tuple[2] = yield(tuple[2])
  ensure
    @ts.write(tuple) if tuple
  end
end
