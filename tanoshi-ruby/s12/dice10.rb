def dice10
  sum = 0
  10.times do
    sum += 1 + Random.rand(6)
  end
  sum
end

10.times{p dice10}
