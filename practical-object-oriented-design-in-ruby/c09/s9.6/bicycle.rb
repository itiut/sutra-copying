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
