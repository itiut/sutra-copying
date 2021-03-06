class Employee
  attr_reader :name, :title, :salary

  def initialize(name, title, salary, payroll)
    @name = name
    @title = title
    @salary = salary
    @payroll = payroll
  end

  def salary=(new_salary)
    @salary = new_salary
    @payroll.update(self)
  end
end

class Payroll
  def update(changed_employee)
    puts "#{changed_employee.name}のために小切手を切ります!"
    puts "彼の給与はいま#{changed_employee.salary}です!"
  end
end

payroll = Payroll.new
fred = Employee.new('Fred Flintstone', 'Crane Operator', 30_000, payroll)
fred.salary = 35_000
