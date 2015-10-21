require 'rails_helper'

module Staff
  RSpec.describe Authenticator do
    describe '#authenticate' do

      example '正しいパスワードならtrueを返す' do
        m = build(:staff_member)
        expect(described_class.new(m).authenticate('pw')).to be_truthy
      end

      example '誤ったパスワードならfalseを返す' do
        m = build(:staff_member)
        expect(described_class.new(m).authenticate('xy')).to be_falsey
      end

      example 'パスワード未設定ならfalseを返す' do
        m = build(:staff_member, password: nil)
        expect(described_class.new(m).authenticate(nil)).to be_falsey
      end

      example '停止フラグが立っていればfalseを返す' do
        m = build(:staff_member, suspended: true)
        expect(described_class.new(m).authenticate('pw')).to be_falsey
      end

      example '開始前ならfalseを返す' do
        m = build(:staff_member, start_date: Date.tomorrow)
        expect(described_class.new(m).authenticate('pw')).to be_falsey
      end

      example '終了後ならfalseを返す' do
        m = build(:staff_member, end_date: Date.today)
        expect(described_class.new(m).authenticate('pw')).to be_falsey
      end
    end
  end
end
