class Authenticator
  def initialize(user)
    @user = user
  end

  def authenticate(raw_password)
    if @user.nil? ||
       @user.hashed_password.blank? ||
       BCrypt::Password.new(@user.hashed_password) != raw_password
      return false, :invalid_email_or_password
    end
    true
  end
end
