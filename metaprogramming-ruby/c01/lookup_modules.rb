module M
  def my_method
    'M#my_method()'
  end
end

module M2
  def my_method2
    'M2#my_method2()'
  end
end

class C
  include M
  include M2
end

class D < C
end

d = D.new
p d.my_method()
p D.ancestors
