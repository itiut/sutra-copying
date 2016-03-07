class Computer
  attr_accessor :display, :motherboard
  attr_reader :drives

  def initialize(display = :crt, motherboard = Motherboard.new, drives = [])
    @display = display
    @motherboard = motherboard
    @drives = drives
  end
end

class DesktopCompuer < Computer
end

class LaptopComputer < Computer
  def initialize(motherboard = Motherboard.new, drives = [])
    super(:lcd, motherboard, drives)
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

class LaptopDrive < Drive
end

class ComputerBuilder
  attr_reader :computer

  def turbo
    @computer.motherboard.cpu = TurboCPU.new
  end

  def memory_size=(size_in_mb)
    @computer.motherboard.memory_size = size_in_mb
  end
end

class DesktopBuilder < ComputerBuilder
  def initialize
    @computer = DesktopComputer.new
  end

  def display=(display)
    @computer.display = display
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
end

class LaptopBuilder < ComputerBuilder
  def initialize
    @computer = LaptopComputer.new
  end

  def display=(display)
    fail 'Laptop display must be lcd' unless display == :lcd
  end

  def add_cd(writer = false)
    @computer.dirves << LaptopDrive.new(:cd, 760, writer)
  end

  def add_dvd(writer = false)
    @computer.drives << LaptopDrive.new(:dvd, 4_700, writer)
  end

  def add_hard_disk(size_in_mb)
    @computer.drives << LaptopDrive.new(:hard_disk, size_in_mb, true)
  end
end
