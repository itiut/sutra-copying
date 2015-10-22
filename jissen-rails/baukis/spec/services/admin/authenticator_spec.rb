require 'rails_helper'

RSpec.describe Admin::Authenticator do
  describe '#authenticate' do

    example '正しいパスワードなら[true, nil]を返す' do
      admin= build(:administrator)
      ok, error_type = described_class.new(admin).authenticate('pw')
      expect(ok).to be_truthy
      expect(error_type).to be_nil
    end

    example '誤ったパスワードなら[false, :invalid_email_or_password]を返す' do
      admin= build(:administrator)
      ok, error_type = described_class.new(admin).authenticate('xy')
      expect(ok).to be_falsey
      expect(error_type).to eq(:invalid_email_or_password)
    end

    example 'パスワード未設定なら[false, :invalid_email_or_password]を返す' do
      admin= build(:administrator, password: nil)
      ok, error_type = described_class.new(admin).authenticate(nil)
      expect(ok).to be_falsey
      expect(error_type).to eq(:invalid_email_or_password)
    end
  end
end
