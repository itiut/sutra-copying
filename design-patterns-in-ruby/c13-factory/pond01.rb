class Duck
  def initialize(name)
    @name = name
  end

  def eat
    puts "アヒル #{@name} は食事中です。"
  end

  def speak
    puts "アヒル #{@name} がガーガー泣いています。"
  end

  def sleep
    puts "アヒル #{@name} は静かに眠っています。"
  end
end

class Pond
  def initialize(number_ducks)
    @ducks = []
    number_ducks.times do |i|
      @ducks << Duck.new("アヒル#{i}")
    end
  end

  def simulate_one_day
    @ducks.each(&:speak)
    @ducks.each(&:eat)
    @ducks.each(&:sleep)
  end
end

pond = Pond.new(3)
pond.simulate_one_day
