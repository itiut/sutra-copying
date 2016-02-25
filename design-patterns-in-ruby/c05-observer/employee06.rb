require 'observer'

class Employee
  include Observable

  attr_accessor :name, :title, :salary

  def initialize(name, title, salary)
    super()
    @name = name
    @title = title
    @salary = salary
  end

  def change
    yield(self)
    changed
    notify_observers(self)
  end
end

fred = Employee.new('Fred Flintstone', 'Crane Operator', 30_000)

class Payroll
  def update(changed_employee)
    puts "#{changed_employee.name}のために小切手を切ります!"
    puts "彼の給与はいま#{changed_employee.salary}です!"
  end
end

payroll = Payroll.new
fred.add_observer(payroll)
fred.change do |e|
  e.salary = 35_000
end

puts

class TaxMan
  def update(changed_employee)
    puts "#{changed_employee.name}に新しい税金の請求書を送ります!"
  end
end

tax_man = TaxMan.new
fred.add_observer(tax_man)
fred.change do |e|
  e.salary = 90_000
end

puts

class BulletinBoard
  def update(changed_employee)
    puts "#{changed_employee.name} (#{changed_employee.title}): #{changed_employee.salary}"
  end
end

board = BulletinBoard.new
fred.add_observer(board)
fred.change do |e|
  e.salary = 1_000_000
  e.title = 'Vice President of Sales'
end
