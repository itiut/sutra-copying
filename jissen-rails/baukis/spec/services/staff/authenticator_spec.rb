require 'rails_helper'

RSpec.describe Staff::Authenticator do
  describe '#authenticate' do

    example '正しいパスワードなら[true, nil]を返す' do
      m = build(:staff_member)
      ok, error_type = described_class.new(m).authenticate('pw')
      expect(ok).to be_truthy
      expect(error_type).to be_nil
    end

    example '誤ったパスワードなら[false, :invalid_email_or_password]を返す' do
      m = build(:staff_member)
      ok, error_type = described_class.new(m).authenticate('xy')
      expect(ok).to be_falsey
      expect(error_type).to eq(:invalid_email_or_password)
    end

    example 'パスワード未設定なら[false, :invalid_email_or_password]を返す' do
      m = build(:staff_member, password: nil)
      ok, error_type = described_class.new(m).authenticate(nil)
      expect(ok).to be_falsey
      expect(error_type).to eq(:invalid_email_or_password)
    end

    example '停止フラグが立っていれば[false, :suspended]を返す' do
      m = build(:staff_member, suspended: true)
      ok, error_type = described_class.new(m).authenticate('pw')
      expect(ok).to be_falsey
      expect(error_type).to eq(:suspended)
    end

    example '開始前なら[false, :not_yet_active]を返す' do
      m = build(:staff_member, start_date: Date.tomorrow)
      ok, error_type = described_class.new(m).authenticate('pw')
      expect(ok).to be_falsey
      expect(error_type).to eq(:not_yet_active)
    end

    example '終了後なら[false, :expired]を返す' do
      m = build(:staff_member, end_date: Date.today)
      ok, error_type = described_class.new(m).authenticate('pw')
      expect(ok).to be_falsey
      expect(error_type).to eq(:expired)
    end
  end
end
