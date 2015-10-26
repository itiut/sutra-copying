require 'rails_helper'

RSpec.shared_examples 'email_helper' do
  describe 'before_validation' do
    describe '.email' do
      example 'email前後のスペースを除去' do
        member = create(described_class.name.underscore.to_sym, email: '  test@example.com ')
        expect(member.email).to eq('test@example.com')
      end

      example 'email前後の全角スペースを除去' do
        member = create(described_class.name.underscore.to_sym, email: "\u{3000}test@example.com\u{3000}\u{3000}")
        expect(member.email).to eq('test@example.com')
      end

      example 'emailに含まれる全角英数記号を半角に変更' do
        member = create(described_class.name.underscore.to_sym, email: 'ｔｅｓｔ＠ｅｘａｍｐｌｅ．ｃｏｍ')
        expect(member.email).to eq('test@example.com')
      end
    end

    describe '.email_for_index' do
      example 'emailを小文字にした文字列がセットされる' do
        member = create(described_class.name.underscore.to_sym, email: 'MEMBER@example.com')
        expect(member.email_for_index).to eq('member@example.com')
      end
    end
  end

  describe 'validation' do
    example '@を2個含むemailは無効' do
      member = build(described_class.name.underscore.to_sym, email: 'test@@example.com')
      expect(member).not_to be_valid
    end

    example '重複するemailは無効' do
      member1 = create(described_class.name.underscore.to_sym)
      member2 = build(described_class.name.underscore.to_sym, email: member1.email)
      expect(member2).not_to be_valid
    end
  end
end
