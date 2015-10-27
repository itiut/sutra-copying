class Staff::ChangePasswordForm
  include ActiveModel::Model

  attr_accessor :object, :current_password, :new_password, :new_password_confirmation

  validates :new_password, presence: true, confirmation: true

  validate do
    ok, _ = Staff::Authenticator.new(object).authenticate(current_password)
    errors.add(:current_password, :wrong) unless ok
  end

  def save
    if valid?
      object.password = new_password
      object.save!
    end
  end
end
