class RussolsenDotComAuthorizer
  def russ_dot_olsen_authorized?(_message)
    true
  end

  def authorized?(message)
    message.body.size < 2048
  end
end
