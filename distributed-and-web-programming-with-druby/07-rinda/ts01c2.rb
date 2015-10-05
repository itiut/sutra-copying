require 'drb/drb'

def fact_client(ts, a, b, n = 1000)
  req = []
  a.step(b, n) do |head|
    tail = [b, head + n - 1].min
    req.push([head, tail])
    ts.write(['fact', head, tail])
  end

  req.reduce(1) do |value, range|
    tuple = ts.take(['fact-answer', range[0], range[1], nil])
    value * tuple[3]
  end
end

ts_uri = ARGV.shift || 'druby://localhost:12345'
DRb.start_service
ts = DRbObject.new_with_uri(ts_uri)
fact_client(ts, 1, 20000)
