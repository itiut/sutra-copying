class Staff::Authenticator < Authenticator
  def authenticate(raw_password)
    ok, error_type = super(raw_password)
    return false, error_type unless ok
    return false, :suspended if @user.suspended?
    return false, :not_yet_active if Date.today < @user.start_date
    return false, :expired if @user.end_date && @user.end_date <= Date.today
    true
  end
end
