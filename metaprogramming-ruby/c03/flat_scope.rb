my_var = 'Success'

MyClass = Class.new do
  puts "#{my_var}はクラス定義の中!"

  define_method :my_method do
    puts "#{my_var}はメソッド定義の中!"
  end
end

obj = MyClass.new
obj.my_method
