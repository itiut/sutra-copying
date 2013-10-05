module PrependModule
  def prepended_method
    :prepended_method
  end
end

class PrependedClass
  prepend PrependModule
end

prepended_obj = PrependedClass.new
p prepended_obj.prepended_method
