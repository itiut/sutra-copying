class HaveInstanceVal
  def initialize
    @foo = 1
    @bar = 2
  end
end

have_instance_val = HaveInstanceVal.new
p have_instance_val.instance_variables

p have_instance_val.instance_variables.any? { |instance_val_name|
  instance_val_name =~ /fo/
}

p have_instance_val.instance_variables.select { |instance_val_name|
  instance_val_name =~ /f/
}

p have_instance_val.instance_variable_defined? :@foo
p have_instance_val.instance_variable_defined? :@buzz

p have_instance_val.instance_variable_get :@foo
p have_instance_val.instance_variable_get :@buzz

have_instance_val.instance_variable_set :@foo, 10
p have_instance_val.instance_variable_get :@foo

have_instance_val.instance_variable_set :@buzz, 3
p have_instance_val.instance_variable_get :@buzz
