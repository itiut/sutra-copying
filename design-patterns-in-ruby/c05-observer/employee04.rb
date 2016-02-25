require 'observer'

class Employee
  include Observable

  attr_reader :name, :title, :salary

  def initialize(name, title, salary)
    super()
    @name = name
    @title = title
    @salary = salary
  end

  def salary=(new_salary)
    @salary = new_salary
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
fred.salary = 35_000

puts

class TaxMan
  def update(changed_employee)
    puts "#{changed_employee.name}に新しい税金の請求書を送ります!"
  end
end

tax_man = TaxMan.new
fred.add_observer(tax_man)
fred.salary = 90_000
