module Carnivore
  def diet
    'meat'
  end

  def teeth
    'sharp'
  end
end

module Herbivore
  def diet
    'plant'
  end

  def teeth
    'flat'
  end
end

module Nocturanal
  def sleep_time
    'day'
  end

  def awake_time
    'night'
  end
end

module Diurnal
  def sleep_time
    'night'
  end

  def awake_time
    'day'
  end
end

def new_animal(diet, awake)
  animal = Object.new

  if diet == :meat
    animal.extend(Carnivore)
  else
    animal.extend(Harbivore)
  end

  if awake == :day
    animal.extend(Diurnal)
  else
    animalextend(Nocturanal)
  end
end
