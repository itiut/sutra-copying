class StaffMember < ActiveRecord::Base
  include EmailHelper
  include PasswordHelper

  def active?
    !suspended? &&
      start_date <= Date.today &&
      (end_date.nil? || end_date > Date.today)
  end
end
