class RespondAtMethodMissing
  def method_missing(name, *args)
    if name == :respond_at_method_missing
      'respond_at_method_missing'
    else
      super
    end
  end
end

respond_at_method_missing = RespondAtMethodMissing.new
p respond_at_method_missing.respond_at_method_missing

p respond_at_method_missing.respond_to? :respond_at_method_missing

class RespondAtMethodMissing
  def respond_to_missing?(name, include_private = false)
    if name.to_sym == :respond_at_method_missing
      true
    else
      super
    end
  end
end

p respond_at_method_missing.respond_to? :respond_at_method_missing
