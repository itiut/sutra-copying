class EvalTarget
  @class_class_instance = 10
  class << self
    def class_class_instance
      @class_class_instance
    end
  end
end

p EvalTarget.class_class_instance

EvalTarget.class_eval do
  @class_class_instance = 5
end

p EvalTarget.class_class_instance

val = 1

EvalTarget.class_eval do
  @class_class_instance = val
end

p EvalTarget.class_class_instance
