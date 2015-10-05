class Stream
  def initialize(ts, name)
    @ts = ts
    @name = name
    @ts.write([name, 'tail', 0])
  end

  attr_reader :name

  def write(value)
    _, _, tail = @ts.take([name, 'tail', nil])
    tail += 1
    @ts.write([name, 'tail', tail])
    @ts.write([name, tail, value])
  end
end

class RDStream
  def initialize(ts, name)
    @ts = ts
    @name = name
    @head = 0
  end

  def read
    _, _, value = @ts.read([@name, @head, nil])
    @head += 1
    value
  end
end

class INStream
  def initialize(ts, name)
    @ts = ts
    @name = name
    @ts.write([@name, 'tail', 0])
    @ts.write([@name, 'head', 0])
  end

  def write(value)
    _, _, tail = @ts.take([@name, 'tail', nil])
    tail += 1
    @ts.write([@name, 'tail', tail])
    @ts.write([@name, tail, value])
  end

  def take
    _, _, head = @ts.take([@name, 'head', nil])
    _, _, value = @ts.take([@name, head, nil])
    @ts.write([@name, 'head', head + 1])
    value
  end
end
