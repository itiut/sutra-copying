class Computer
  attr_accessor :display, :motherboard
  attr_reader :drives

  def initialize(display = :crt, motherboard = Motherboard.new, drives = [])
    @display = display
    @motherboard = motherboard
    @drives = drives
  end
end

class CPU
end

class BasicCPU < CPU
end

class TurboCPU < CPU
end

class Motherboard
  attr_accessor :cpu, :memory_size

  def initialize(cpu = BasicCPU.new, memory_size = 1_000)
    @cpu = cpu
    @memory_size = memory_size
  end
end

class Drive
  attr_reader :type, :size, :writable

  def initialize(type, size, writable)
    @type = type
    @size = size
    @writable = writable
  end
end

motherboard = Motherboard.new(TurboCPU.new, 4_000)

drives = []
drives << Drive.new(:hard_drive, 200_000, true)
drives << Drive.new(:cd, 760, true)
drives << Drive.new(:dvd, 4_700, false)

computer = Computer.new(:lcd, motherboard, drives)

class ComputerBuilder
  def initialize
    @computer = Computer.new
  end

  def turbo
    @computer.motherboard.cpu = TurboCPU.new
  end

  def display=(display)
    @computer.display = display
  end

  def memory_size=(size_in_mb)
    @computer.motherboard.memory_size = size_in_mb
  end

  def add_cd(writer = false)
    @computer.dirves << Drive.new(:cd, 760, writer)
  end

  def add_dvd(writer = false)
    @computer.drives << Drive.new(:dvd, 4_700, writer)
  end

  def add_hard_disk(size_in_mb)
    @computer.drives << Drive.new(:hard_disk, size_in_mb, true)
  end

  def computer
    fail 'Not enough memory' if @computer.motherboard.memory_size < 250
    fail 'Too many drives' if @computer.drives.size >= 4
    fail 'No hard disk' unless @computer.drives.any? { |drive| drive.type == :hard_disk }
    @computer
  end

  def reset
    @computer = Computer.new
  end

  def method_missing(meth, *args)
    words = meth.to_s.split('_')
    return super(meth, *args) unless words.shift == 'add'
    words.each do |word|
      case word
      when 'and'
        next
      when 'cd'
        add_cd
      when 'dvd'
        add_dvd
      when 'harddisk'
        add_hard_disk(100_000)
      when 'turbo'
        turbo
      end
    end
  end
end

builder = ComputerBuilder.new
builder.turbo
builder.add_cd(true)
builder.add_dvd
builder.add_hard_disk(100_000)

computer = builder.conputer
