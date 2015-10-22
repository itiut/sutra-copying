class Staff::Authenticator
  def initialize(staff_member)
    @staff_member = staff_member
  end

  def authenticate(raw_password)
    if @staff_member.nil? ||
       @staff_member.hashed_password.blank? ||
       BCrypt::Password.new(@staff_member.hashed_password) != raw_password
      return false, :invalid_email_or_password
    end

    return false, :suspended if @staff_member.suspended?
    return false, :not_yet_active if Date.today < @staff_member.start_date
    return false, :expired if @staff_member.end_date && @staff_member.end_date <= Date.today
    true
  end
end
