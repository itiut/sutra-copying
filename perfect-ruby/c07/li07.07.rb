class LoggingInstanceVariable
  attr_reader :first_val, :before_first_val

  def first_val=(val)
    @before_first_val = @first_val
    @first_val = val
  end
end

obj = LoggingInstanceVariable.new

obj.first_val = 1
p obj.first_val
p obj.before_first_val

obj.first_val = 2
p obj.first_val
p obj.before_first_val
