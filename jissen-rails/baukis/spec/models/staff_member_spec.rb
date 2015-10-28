require 'rails_helper'

RSpec.describe StaffMember, type: :model do
  it_behaves_like 'email_holder'
  it_behaves_like 'password_holder'
  it_behaves_like 'personal_name_holder'

  describe 'validation' do
    describe '.start_date' do
      example 'nilなら無効' do
        member = build(:staff_member, start_date: nil)
        expect(member).not_to be_valid
      end

      example '1999-12-31以前なら無効' do
        member = build(:staff_member, start_date: Date.new(1999, 12, 31))
        expect(member).not_to be_valid
      end

      example '2001-01-01以降なら有効' do
        member = build(:staff_member, start_date: Date.new(2001, 1, 1))
        expect(member).to be_valid
      end

      example '1年後より前なら有効' do
        member = build(:staff_member, start_date: (1.year.from_now - 1.day).to_date)
        expect(member).to be_valid
      end

      example '1年後以降なら無効' do
        member = build(:staff_member, start_date: 1.year.from_now.to_date)
        expect(member).not_to be_valid
      end
    end

    describe '.end_date' do
      example 'start_date以前なら無効' do
        member = build(:staff_member, end_date: attributes_for(:staff_member)[:start_date])
        expect(member).not_to be_valid
      end

      example 'start_dateより後なら有効' do
        member = build(:staff_member, end_date: attributes_for(:staff_member)[:start_date] + 1.day)
        expect(member).to be_valid
      end

      example '1年後より前なら有効' do
        member = build(:staff_member, end_date: (1.year.from_now - 1.day).to_date)
        expect(member).to be_valid
      end

      example '1年後以降なら無効' do
        member = build(:staff_member, end_date: 1.year.from_now.to_date)
        expect(member).not_to be_valid
      end
    end
  end
end
