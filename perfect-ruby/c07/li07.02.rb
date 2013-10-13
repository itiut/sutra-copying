class Numeric
  def steps
    return [] if self <= 0

    0.upto(self).to_a
  end
end

p 10.steps
p 1.steps
p 0.steps
p -1.steps
