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

class Tree
  def initialize(name)
    @name = name
  end

  def grow
    puts "樹木 #{@name} が高く育っています。"
  end
end

class Tiger
  def initialize(name)
    @name = name
  end

  def eat
    puts "トラ #{@name} は食べたいものを何でも食べます。"
  end

  def speak
    puts "トラ #{@name} はガオーとほえています。"
  end

  def sleep
    puts "トラ #{@name} は眠くなったら眠ります。"
  end
end

class Habitat
  def initialize(number_animals, animal_class, number_plants, plant_class)
    @animal_class = animal_class
    @plant_class = plant_class

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

  def new_organism(type, name)
    case type
    when :animal
      @animal_class.new(name)
    when :plant
      @plant_class.new(name)
    else
      fail "Unknown organism type: #{type}"
    end
  end
end

jungle = Habitat.new(1, Tiger, 4, Tree)
jungle.simulate_one_day

pond = Habitat.new(2, Duck, 4, WaterLily)
pond.simulate_one_day
