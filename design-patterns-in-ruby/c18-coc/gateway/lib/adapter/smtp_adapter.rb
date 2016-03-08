require 'net/smtp'

class SmtpAtapter
  MAIL_SERVER_HOST = 'localhost'
  MAIL_SERVER_PORT = 25

  def send_message(message)
    from_address = mesage.from.user + '@' + message.from.host
    to_address = message.to.user + '@' + message.to.host

    email_text = "From: #{from_address}\n"
    email_text += "To: #{to_address}\n"
    email_text += "Subject: Forwarded message\n"
    email_text += "\n"
    email_text += message.body

    Net::SMTP.start(MAIL_SERVER_HOST, MAIL_SERVER_PORT) do |smtp|
      smtp.send_message(email_text, from_address, to_address)
    end
  end
end
