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
  def initialize(number_animals, number_plants, organism_factory)
    @animals = []
    number_animals.times do |i|
      @animals << organism_factory.new_animal("動物#{i}")
    end

    @plants = []
    number_plants.times do |i|
      @plants << organism_factory.new_plant("植物#{i}")
    end
  end

  def simulate_one_day
    @plants.each(&:grow)
    @animals.each(&:speak)
    @animals.each(&:eat)
    @animals.each(&:sleep)
  end
end

class PondOrganismFactory
  def new_animal(name)
    Frog.new(name)
  end

  def new_plant(name)
    Algae.new(name)
  end
end

class JungleOrganismFactory
  def new_animal(name)
    Tiger.new(name)
  end

  def new_plant(name)
    Tree.new(name)
  end
end

jungle = Habitat.new(1, 4, JungleOrganismFactory.new)
jungle.simulate_one_day

pond = Habitat.new(2, 4, PondOrganismFactory.new)
pond.simulate_one_day
