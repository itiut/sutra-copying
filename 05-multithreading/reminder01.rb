class Reminder
  def initialize
    @mutex = Mutex.new
    @item = {}
    @serial = 0
  end

  def [](key)
    @item[key]
  end

  def serial
    @mutex.synchronize do
      @serial += 1
      return @serial
    end
  end

  def add(str)
    key = serial
    @item[key] = str
    key
  end

  def delete(key)
    @mutex.synchronize do
      @item.delete(key)
    end
  end

  def to_a
    @mutex.synchronize do
      @item.keys.sort.map do |k|
        [k, @item[k]]
      end
    end
  end
end
