module NameHelper
  extend ActiveSupport::Concern

  def full_name
    family_name + given_name
  end
end
