require 'drb/drb'

class FactServer
  def initialize(ts)
    @ts = ts
  end

  def main_loop
    loop do
      _, m, n = @ts.take(['fact', Integer, Integer])
      value = (m..n).reduce(1, :*)
      @ts.write(['fact-answer', m, n, value])
    end
  end
end

ts_uri = ARGV.shift || 'druby://localhost:12345'
DRb.start_service
ts = DRbObject.new_with_uri(ts_uri)
FactServer.new(ts).main_loop
