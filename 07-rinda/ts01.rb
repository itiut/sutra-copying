require 'rinda/tuplespace'

$ts = Rinda::TupleSpace.new
DRb.start_service('druby://localhost:12345', $ts)
puts DRb.uri
DRb.thread.join
