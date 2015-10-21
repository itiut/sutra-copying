module EmailHelper
  extend ActiveSupport::Concern

  included do
    before_validation :set_email_for_index
  end

  def set_email_for_index
    self.email_for_index = email.downcase if email
  end
end
