require 'nkf'

module EmailHelper
  extend ActiveSupport::Concern

  included do
    before_validation do
      self.email = normalize_as_email(email)
      self.email_for_index = email.downcase if email
    end

    validates :email, presence: true, email: { allow_blank: true }
    validates :email_for_index, uniqueness: { allow_blank: true }

    after_validation do
      if errors.include?(:email_for_index)
        errors.add(:email, :taken)
        errors.delete(:email_for_idnex)
      end
    end
  end

  private

  def normalize_as_email(text)
    NKF.nkf('-w -Z1', text).strip if text
  end
end
