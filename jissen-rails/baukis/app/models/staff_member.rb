class StaffMember < ActiveRecord::Base
  include EmailHolder
  include PasswordHolder
  include PersonalNameHolder

  has_many :events, class_name: 'StaffEvent', dependent: :destroy

  validates :start_date, date: {
              after_or_equal_to: Date.new(2000, 1, 1),
              before: -> (_) { 1.year.from_now.to_date },
              allow_blank: false
            }
  validates :end_date, date: {
              after: :start_date,
              before: -> (_) { 1.year.from_now.to_date},
              allow_blank: true
            }

  def active?
    !suspended? &&
      start_date <= Date.today &&
      (end_date.nil? || end_date > Date.today)
  end
end
