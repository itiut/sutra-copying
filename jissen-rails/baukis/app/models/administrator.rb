class Administrator < ActiveRecord::Base
  include EmailHelper
  include PasswordHelper
end
