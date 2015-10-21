require 'rails_helper'

RSpec.shared_examples 'email_helper' do
  describe '#set_email_for_index' do
    example 'バリデーション前にset_email_for_indexが実行される' do
      member = described_class.new(email: 'member@example.com')
      member.valid?
      expect(member.email_for_index).to eq(member.email)
    end

    example 'email_for_passwordにemailを小文字にした文字列がセットされる' do
      member = described_class.new(email: 'MEMBER@example.com')
      member.set_email_for_index
      expect(member.email_for_index).to eq('member@example.com')
    end
  end
end
