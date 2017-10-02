class Bicycle
  attr_reader :size, :chain, :tire_size

  def initialize(**args)
    @size = args.delete(:size)
    @chain = args.delete(:chain) || default_chain
    @tire_size = args.delete(:tire_size) || default_tire_size
    post_initialize(args)
  end

  def spares
    { tire_size: tire_size, chain: chain }.merge(local_spares)
  end

  def default_tire_size
    raise NotImplementedError
  end

  def post_initialize(args)
    nil
  end

  def local_spares
    {}
  end

  def default_chain
    '10-speed'
  end
end

class RoadBike < Bicycle
  attr_reader :tape_color

  def post_initialize(tape_color:)
    @tape_color = tape_color
  end

  def local_spares
    { tape_color: tape_color }
  end

  def default_tire_size
    '23'
  end
end

class MountainBike < Bicycle
  attr_reader :front_shock, :rear_shock

  def post_initialize(front_shock:, rear_shock:)
    @front_shock = front_shock
    @rear_shock = rear_shock
  end

  def local_spares
    { rear_shock: rear_shock }
  end

  def default_tire_size
    '21'
  end
end

class RecumbentBike < Bicycle
  attr_reader :flag

  def post_initialize(flag:)
    @flag = flag
  end

  def local_spares
    { flag: flag }
  end

  def default_chain
    '9-speed'
  end

  def default_tire_size
    '28'
  end
end

def print_bike(bike)
  puts bike.class
  print "  .tire_size\t= ", bike.tire_size, "\n"
  print "  .chain\t= ", bike.chain, "\n"
  print "  .spares\t= ", bike.spares, "\n"
end

print_bike(RoadBike.new(size: 'M', tape_color: 'red'))
print_bike(MountainBike.new(size: 'S', front_shock: 'Manitou', rear_shock: 'Fox'))
print_bike(RecumbentBike.new(flag: 'tall and orange'))
