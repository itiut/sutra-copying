class StaffMember < ActiveRecord::Base
  include EmailHelper
  include PasswordHelper
end
