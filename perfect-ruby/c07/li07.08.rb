class LoggingInstanceVariable
  logging_instance_val_names = %w{first_val second_val third_val}

  logging_instance_val_names.each do |val_name|
    eval <<-EOF
      attr_reader :#{val_name}, :before_#{val_name}

      def #{val_name}=(val)
        @before_#{val_name} = @#{val_name}
        @#{val_name} = val
      end
    EOF
  end
end

obj = LoggingInstanceVariable.new

obj.first_val = 1
obj.first_val = 2

p obj.first_val
p obj.before_first_val

obj.third_val = :third_val
obj.third_val = 'third_val'

p obj.third_val
p obj.before_third_val
