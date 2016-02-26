class Task
  attr_reader :name

  def initialize(name)
    @name = name
  end

  def required_time
    0.0
  end
end

class CompositeTask < Task
  def initialize(name)
    super(name)
    @sub_tasks = []
  end

  def add_sub_task(task)
    @sub_tasks << task
  end

  def remove_sub_task(task)
    @sub_tasks.delete(task)
  end

  def <<(task)
    @sub_tasks << task
  end

  def [](index)
    @sub_tasks[index]
  end

  def []=(index, new_task)
    @sub_tasks[index] = new_task
  end

  def required_time
    @sub_tasks.map(&:required_time).reduce(&:+)
  end
end

class AddDryIngredientsTask < Task
  def initialize
    super('Add dry ingredients')
  end

  def required_time
    1.0
  end
end

class AddLiquidsTask < Task
  def initialize
    super('Add liquids')
  end

  def required_time
    0.5
  end
end

class MixTask < Task
  def initialize
    super('Mix that batter up!')
  end

  def required_time
    3.0
  end
end

class MakeBatterTask < CompositeTask
  def initialize
    super('Make batter')
    self << AddDryIngredientsTask.new
    self << AddLiquidsTask.new
    self << MixTask.new
  end
end

task = MakeBatterTask.new
puts "#{task.name}: #{task.required_time}"
3.times do |i|
  puts "  - #{task[i].name}: #{task[i].required_time}"
end
