require 'rails_helper'

RSpec.describe Administrator, type: :model do
  it_behaves_like 'email_holder'
  it_behaves_like 'password_holder'
end
