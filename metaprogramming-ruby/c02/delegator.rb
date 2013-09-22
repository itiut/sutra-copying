require 'delegate'

class Assistant
  def initialize(name)
    @name = name
  end

  def read_email
    "(#{@name}) ほとんどスパムです。"
  end

  def check_schedule
    "(#{@name}) 今日は打ち合わせがあります。"
  end
end

class Manager < DelegateClass(Assistant)
  def initialize(assistant)
    super(assistant)
  end

  def attend_meeting
    "電話は取り次がないでください。"
  end
end

frank = Assistant.new('Frank')
anne = Manager.new(frank)
p anne.attend_meeting
p anne.read_email
p anne.check_schedule
