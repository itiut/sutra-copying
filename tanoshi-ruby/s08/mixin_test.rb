module M1
  def meth
    "meth"
  end
end

module M2

end

class C
  include M1
  include M2

  def meth
    "C#meth"
  end
end

c = C.new
p c.meth

p C.include?(M1)

p C.ancestors
p C.superclass
