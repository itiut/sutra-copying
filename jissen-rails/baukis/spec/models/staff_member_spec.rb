require 'rails_helper'

RSpec.describe StaffMember, type: :model do
  include_examples 'email_helper'
  include_examples 'password_helper'
end