require 'rinda/rinda'

class FactServer
  def initialize(ts)
    @ts = ts
  end

  def main_loop
    loop do
      tuple = @ts.take('request' => 'fact', 'range' => Range)
      value = tuple['range'].reduce(1, :*)
      @ts.write('answer' => 'fact', 'range' => tuple['range'], 'fact' => value)
    end
  end
end

ts_uri = ARGV.shift || 'druby://localhost:12345'
DRb.start_service
ts = DRbObject.new_with_uri(ts_uri)
FactServer.new(Rinda::TupleSpaceProxy.new(ts)).main_loop
