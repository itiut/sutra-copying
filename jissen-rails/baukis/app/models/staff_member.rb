class StaffMember < ActiveRecord::Base
  include NameHelper
  include EmailHelper
  include PasswordHelper

  has_many :events, class_name: 'StaffEvent', dependent: :destroy

  def active?
    !suspended? &&
      start_date <= Date.today &&
      (end_date.nil? || end_date > Date.today)
  end
end
