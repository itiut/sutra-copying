require 'drb/drb'

class DumbIdConv < DRb::DRbIdConv
  def initialize
    @table = {}
  end

  attr_reader :table

  def to_id(obj)
    ref = super(obj)
    @table[ref] = obj
    ref
  end
end
