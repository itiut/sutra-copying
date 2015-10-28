class Customer < ActiveRecord::Base
  include EmailHolder
  include PasswordHolder
  include PersonalNameHolder

  has_one :home_address, dependent: :destroy, autosave: true
  has_one :work_address, dependent: :destroy, autosave: true

  validates :gender, inclusion: { in: %w(male female), allow_blank: true }
  validates :birthday, date: {
              after_or_equal_to: Date.new(1900, 1, 1),
              before_or_equal_to: -> (_) { Date.today },
              allow_blank: true
            }
end
