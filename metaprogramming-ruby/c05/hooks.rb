class String
  def self.inherited(subclass)
    puts "#{self} は #{subclass} に継承された"
  end
end

class MyString < String
end

module M
  def self.included(othermod)
    puts "M は #{othermod} にミックスインされた"
  end

  def self.method_added(method)
    puts "新しいメソッド: M##{method}"
  end

  def my_method
  end
end

class C
  def self.include(*modules)
    puts "Called: C.include(#{modules})"
    super
  end

  include M
end
