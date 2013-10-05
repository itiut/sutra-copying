module FirstPrependModule
  def prepended_method
    :first_prepend_module
  end
end

module SecondPrependModule
  def prepended_method
    :second_prepend_module
  end
end

class PrependedClass
  prepend FirstPrependModule
  prepend SecondPrependModule
end

p PrependedClass.new.prepended_method
