class Staff::SessionsController < Staff::Base
  skip_before_action :authorize

  def new
    if current_staff_member
      redirect_to staff_root_url
    else
      @form = Staff::LoginForm.new
      render action: 'new'
    end
  end

  def create
    @form = Staff::LoginForm.new(params[:staff_login_form])
    if @form.email.present?
      staff_member = StaffMember.find_by(email_for_index: @form.email.downcase)
    end
    ok, error_type = Staff::Authenticator.new(staff_member).authenticate(@form.password)
    if ok
      session[:staff_member_id] = staff_member.id
      session[:last_access_time] = Time.current
      staff_member.events.create!(type: 'logged_in')
      flash.notice = 'ログインしました。'
      redirect_to staff_root_url
    else
      staff_member.events.create!(type: 'rejected') if error_type == :suspended
      flash.now.alert = authentication_message_for(error_type)
      render action: 'new'
    end
  end

  def destroy
    if current_staff_member
      current_staff_member.events.create!(type: 'logged_out')
    end
    session.delete(:staff_member_id)
    flash.notice = 'ログアウトしました。'
    redirect_to staff_root_url
  end

  private

  def authentication_message_for(error_type)
    messages = {
      invalid_email_or_password: 'メールアドレスまたはパスワードが正しくありません。',
      suspended:                 'アカウントが停止されています。',
      not_yet_active:            'アカウントの有効期限前です。',
      expired:                   'アカウントの有効期限が切れています。'
    }
    messages[error_type] || '申し訳ございません。エラーが発生しました。'
  end
end
