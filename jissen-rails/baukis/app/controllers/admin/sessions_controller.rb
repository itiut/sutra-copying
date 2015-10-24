class Admin::SessionsController < Admin::Base
  skip_before_action :authorize

  def new
    if current_administrator
      redirect_to admin_root_url
    else
      @form = Admin::LoginForm.new
      render action: 'new'
    end
  end

  def create
    @form = Admin::LoginForm.new(params[:admin_login_form])
    if @form.email.present?
      administrator = Administrator.find_by(email_for_index: @form.email.downcase)
    end
    ok, error_type = Admin::Authenticator.new(administrator).authenticate(@form.password)
    if ok
      session[:administrator_id] = administrator.id
      session[:last_access_time] = Time.current
      flash.notice = 'ログインしました。'
      redirect_to admin_root_url
    else
      flash.now.alert = authentication_message_for(error_type)
      render action: 'new'
    end
  end

  def destroy
    session.delete(:administrator_id)
    flash.notice = 'ログアウトしました。'
    redirect_to admin_root_url
  end

  private

  def authentication_message_for(error_type)
    messages = {
      invalid_email_or_password: 'メールアドレスまたはパスワードが正しくありません。'
    }
    messages[error_type] || '申し訳ございません。エラーが発生しました。'
  end
end
