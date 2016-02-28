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

class Frog
  def initialize(name)
    @name = name
  end

  def eat
    puts "カエル #{@name} は食事中です。"
  end

  def speak
    puts "カエル #{@name} はゲロゲロッと泣いています。"
  end

  def sleep
    puts "カエル #{@name} は眠りません。一晩中ゲロゲロ泣いています。"
  end
end

class Pond
  def initialize(number_animals)
    @animals = []
    number_animals.times do |i|
      @animals << new_animal("動物#{i}")
    end
  end

  def simulate_one_day
    @animals.each(&:speak)
    @animals.each(&:eat)
    @animals.each(&:sleep)
  end
end

class DuckPond < Pond
  def new_animal(name)
    Duck.new(name)
  end
end

class FrogPond < Pond
  def new_animal(name)
    Frog.new(name)
  end
end

pond = FrogPond.new(3)
pond.simulate_one_day
