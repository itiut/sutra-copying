require 'rails_helper'

RSpec.describe Customer, type: :model do
  it_behaves_like 'email_holder'
  it_behaves_like 'password_holder'
  it_behaves_like 'personal_name_holder'

  describe 'validation' do
    describe '.gender' do
      example 'maleかfemaleなら有効' do
        customer = build(:customer, gender: 'male')
        expect(customer).to be_valid

        customer = build(:customer, gender: 'female')
        expect(customer).to be_valid
      end

      example 'maleかfemale以外なら無効' do
        customer = build(:customer, gender: 'unknown')
        expect(customer).not_to be_valid
      end
    end

    describe '.birthday' do
      example '1900年1月1日より前の日付なら無効' do
        customer = build(:customer, birthday: Date.new(1899, 12, 31))
        expect(customer).not_to be_valid
      end

      example '1900年1月1日以降の日付なら有効' do
        customer = build(:customer, birthday: Date.new(1900, 1, 1))
        expect(customer).to be_valid
      end

      example '今日以前の日付なら有効' do
        customer = build(:customer, birthday: Date.today)
        expect(customer).to be_valid
      end

      example '明日以降の日付なら無効' do
        customer = build(:customer, birthday: Date.today.tomorrow)
        expect(customer).not_to be_valid
      end
    end
  end
end
