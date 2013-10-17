p Array.instance_method(:shift)
p [].method(:shift).unbind

p unbound_push_operator = Array.instance_method(:<<)
p unbound_push_operator.arity
p unbound_push_operator.owner
p unbound_push_operator.name

unbind_shift = [].method(:shift).unbind
p unbind_shift.bind([1, 2, 3])
p unbind_shift.bind([1, 2, 3]).call
