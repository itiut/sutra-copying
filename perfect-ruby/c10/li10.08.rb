class MailSender
  attr_reader :from

  def initialize(from)
    @from = from
  end

  def send(to)
    "send mail: #{to}"
  end
end

mail_sender = MailSender.new('Bob')

p mail_sender.send 'john@example.com'
p mail_sender.__send__ :from
