require 'drb/drb'

def fact_client(ts, a, b)
  ts.write(['fact', a, b])
  tuple = ts.take(['fact-answer', a, b, nil])
  tuple[3]
end

ts_uri = ARGV.shift || 'druby://localhost:12345'
DRb.start_service
ts = DRbObject.new_with_uri(ts_uri)
p fact_client(ts, 1, 5)
