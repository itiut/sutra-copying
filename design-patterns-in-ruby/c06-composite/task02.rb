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
    add_sub_task(AddDryIngredientsTask.new)
    add_sub_task(AddLiquidsTask.new)
    add_sub_task(MixTask.new)
  end
end

task = MakeBatterTask.new
puts task.required_time
