class Gear
  attr_reader :chainring, :cog, :wheel, :observer

  def initialize(**args)
    @chainring = args[:chainring]
    @cog = args[:cog]
    @wheel = args[:wheel]
    @observer = args[:observer]
  end

  def cog=(value)
    @cog = value
    changed
  end

  def chainring=(value)
    @chainring = value
    changed
  end

  def changed
    observer.changed(chainring, cog)
  end
end
