require 'monitor'

class Reminder
  include MonitorMixin

  def initialize
    super
    @item = {}
    @serial = 0
  end

  def [](key)
    @item[key]
  end

  def add(str)
    synchronize do
      @serial += 1
      @item[@serial] = str
      @serial
    end
  end

  def delete(key)
    synchronize do
      @item.delete(key)
    end
  end

  def to_a
    synchronize do
      @item.keys.sort.map do |k|
        [k, @item[k]]
      end
    end
  end
end
