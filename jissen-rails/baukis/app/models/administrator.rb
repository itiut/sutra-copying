class Administrator < ActiveRecord::Base
  include EmailHelper
  include PasswordHelper

  def active?
    !suspended?
  end
end
