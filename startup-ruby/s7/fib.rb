class Fib
  def at(n)
    raise "invalid index" unless n > 0
    if n == 1
      0
    elsif n == 2
      1
    else
      at(n-1) + at(n-2)
    end
  end
end
