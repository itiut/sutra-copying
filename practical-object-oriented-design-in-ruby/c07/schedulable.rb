require 'date'

class Schedule
  def scheduled?(schedulable, start_date, end_date)
    puts <<-EOS
This #{schedulable.class} is not scheduled
  between #{start_date} and #{end_date}
    EOS
  end
end

module Schedulable
  attr_reader :schedule

  def schedule
    @schedule ||= ::Schedule.new
  end

  def schedulable?(start_date, end_date)
    !scheduled?(start_date - lead_days, end_date)
  end

  def scheduled?(start_date, end_date)
    schedule.scheduled?(self, start_date, end_date)
  end

  def lead_days
    0
  end
end

class Bicycle
  include Schedulable

  def lead_days
    1
  end
end

class Vehicle
  include Schedulable

  def lead_days
    3
  end
end

class Mechanic
  include Schedulable

  def lead_days
    4
  end
end

Bicycle.new.schedulable?(Date.parse('2015/09/04'), Date.parse('2015/09/10'))
Vehicle.new.schedulable?(Date.parse('2015/09/01'), Date.parse('2015/09/10'))
Mechanic.new.schedulable?(Date.parse('2015/03/04'), Date.parse('2015/09/10'))
