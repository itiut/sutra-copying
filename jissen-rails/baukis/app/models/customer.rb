class Customer < ActiveRecord::Base
  include EmailHelper
  include PasswordHelper

  has_one :home_address, dependent: :destroy
  has_one :work_address, dependent: :destroy
end
