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

class Algae
  def initialize(name)
    @name = name
  end

  def grow
    puts "藻 #{@name} は日光を浴びて育ちます。"
  end
end

class WaterLily
  def initialize(name)
    @name = name
  end

  def grow
    puts "スイレン #{@name} は浮きながら日光を浴びて育ちます。"
  end
end

class Pond
  def initialize(number_animals, number_plants)
    @animals = []
    number_animals.times do |i|
      @animals << new_organism(:animal, "動物#{i}")
    end

    @plants = []
    number_plants.times do |i|
      @plants << new_organism(:plant, "植物#{i}")
    end
  end

  def simulate_one_day
    @plants.each(&:grow)
    @animals.each(&:speak)
    @animals.each(&:eat)
    @animals.each(&:sleep)
  end
end

class DuckWaterLilyPond < Pond
  def new_organism(type, name)
    case type
    when :animal
      Duck.new(name)
    when :plant
      WaterLily.new(name)
    else
      fail "Unknown organism type: #{type}"
    end
  end
end

pond = DuckWaterLilyPond.new(3, 2)
pond.simulate_one_day
