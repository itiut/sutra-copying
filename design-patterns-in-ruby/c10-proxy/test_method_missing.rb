class TestMethodMissing
  def hello
    puts 'Hello from a real method'
  end

  def method_missing(name, *args)
    puts "Warning, warning, unknown method caled: #{name}"
    puts "Arguments: #{args.join(' ')}"
  end
end

tmm = TestMethodMissing.new
tmm.hello

tmm.goodbye('cruel', 'world')

tmm.send(:hello)
tmm.send(:goodbye, 'cruel', 'world')
