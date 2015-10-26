require 'rails_helper'

RSpec.shared_examples 'name_helper' do
  describe 'before_validation' do
    example 'family_name_kanaに含まれるひらがなをカタカナに変換' do
      member = create(described_class.name.underscore.to_sym, family_name_kana: 'てすと')
      expect(member.family_name_kana).to eq('テスト')
    end

    example 'family_nake_kanaに含まれる半角カナを全角カナに変更' do
      member = create(described_class.name.underscore.to_sym, family_name_kana: 'ﾃｽﾄ')
      expect(member.family_name_kana).to eq('テスト')
    end

    example 'given_name_kanaに含まれるひらがなをカタカナに変換' do
      member = create(described_class.name.underscore.to_sym, given_name_kana: 'てすと')
      expect(member.given_name_kana).to eq('テスト')
    end

    example 'given_nake_kanaに含まれる半角カナを全角カナに変更' do
      member = create(described_class.name.underscore.to_sym, given_name_kana: 'ﾃｽﾄ')
      expect(member.given_name_kana).to eq('テスト')
    end
  end

  describe 'validation' do
    describe '.family_name, .given_name' do
      example '漢字、ひらがな、カタカナ、アルファベットだけを含むfamily_nameは有効' do
        member = build(described_class.name.underscore.to_sym, family_name: '漢ひカaA')
        expect(member).to be_valid
      end

      example '漢字、ひらがな、カタカナ、アルファベットだけを含むgiven_nameは有効' do
        member = build(described_class.name.underscore.to_sym, given_name: '漢ひカaA')
        expect(member).to be_valid
      end

      example '数値を含むfamily_nameは無効' do
        member = build(described_class.name.underscore.to_sym, family_name: '0')
        expect(member).not_to be_valid
      end

      example '数値を含むgiven_nameは無効' do
        member = build(described_class.name.underscore.to_sym, given_name: '0')
        expect(member).not_to be_valid
      end

      example '記号を含むfamily_nameは無効' do
        member = build(described_class.name.underscore.to_sym, family_name: '()')
        expect(member).not_to be_valid
      end

      example '記号を含むgiven_nameは無効' do
        member = build(described_class.name.underscore.to_sym, given_name: '()')
        expect(member).not_to be_valid
      end
    end

    describe '.family_name_kana, .given_name_kana' do
      example '漢字を含むfamily_name_kanaは無効' do
        member = build(described_class.name.underscore.to_sym, family_name_kana: '試験')
        expect(member).not_to be_valid
      end

      example '長音符を含むfamily_name_kanaは有効' do
        member = build(described_class.name.underscore.to_sym, family_name_kana: 'エリー')
        expect(member).to be_valid
      end

      example '漢字を含むgiven_name_kanaは無効' do
        member = build(described_class.name.underscore.to_sym, given_name_kana: '試験')
        expect(member).not_to be_valid
      end

      example '長音符を含むgiven_name_kanaは有効' do
        member = build(described_class.name.underscore.to_sym, given_name_kana: 'エリー')
        expect(member).to be_valid
      end
    end
  end
end
