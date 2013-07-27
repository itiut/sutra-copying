def counter
  c = 0
  Proc.new do
    c += 1
  end
end

c1 = counter
p c1.call
p c1.call
p c1.call

c2 = counter
p c2.call
p c2.call

p c1.call
