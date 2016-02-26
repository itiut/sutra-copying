class Task
  attr_reader :name, :required_time
  attr_accessor :parent

  def initialize(name, required_time = 0.0)
    @name = name
    @required_time = required_time
    @parent = nil
  end

  def basic_task_size
    1.0
  end
end

class CompositeTask < Task
  def initialize(name)
    super(name)
    @sub_tasks = []
  end

  def add_sub_task(task)
    @sub_tasks << task
    task.parent = self
  end

  def remove_sub_task(task)
    @sub_tasks.delete(task)
    task.parent = nil
  end

  def required_time
    @sub_tasks.map(&:required_time).reduce(&:+)
  end

  def basic_task_size
    @sub_tasks.map(&:basic_task_size).reduce(&:+)
  end
end

class AddDryIngredientsTask < Task
  def initialize
    super('Add dry ingredients', 1.0)
  end
end

class AddLiquidsTask < Task
  def initialize
    super('Add liquids', 0.5)
  end
end

class MixTask < Task
  def initialize
    super('Mix that batter up!', 3.0)
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

class FillPanTask < Task
  def initialize
    super('Fill pan', 1.5)
  end
end

class BakeTask < Task
  def initialize
    super('Bake', 4.0)
  end
end

class FrostTask < Task
  def initialize
    super('Frost', 8.0)
  end
end

class MakeCakeTask < CompositeTask
  def initialize
    super('Make cake')
    add_sub_task(MakeBatterTask.new)
    add_sub_task(FillPanTask.new)
    add_sub_task(BakeTask.new)
    add_sub_task(FrostTask.new)
  end
end

class BoxTask < Task
  def initialize
    super('Box', 0.75)
  end
end

class LabelTask < Task
  def initialize
    super('Label', 1.0)
  end
end

class PackageCakeTask < CompositeTask
  def initialize
    super('Package cake')
    add_sub_task(BoxTask.new)
    add_sub_task(LabelTask.new)
  end
end

class ManufactureCakeTask < CompositeTask
  def initialize
    super('Manufacture cake')
    add_sub_task(MakeCakeTask.new)
    add_sub_task(PackageCakeTask.new)
  end
end

task = ManufactureCakeTask.new
puts "#{task.name}:"
puts "  - required_time: #{task.required_time}"
puts "  - basic_task_size: #{task.basic_task_size}"
