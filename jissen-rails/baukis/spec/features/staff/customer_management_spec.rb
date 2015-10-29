require 'rails_helper'

feature '職員による顧客管理' do
  include FeaturesSpecHelper
  let(:staff_member) { create(:staff_member) }
  let!(:customer) { create(:customer) }

  before do
    switch_namespace(:staff)
    login_as_staff_member(staff_member)
  end

  scenario '職員が顧客（基本情報のみ）を登録する' do
    click_link '顧客管理'
    first('div.links').click_link '新規登録'

    fill_in 'メールアドレス', with: 'test@example.com'
    fill_in 'パスワード', with: 'pw'
    fill_in 'form_customer_family_name', with: '試験'
    fill_in 'form_customer_given_name', with: '花子'
    fill_in 'form_customer_family_name_kana', with: 'シケン'
    fill_in 'form_customer_given_name_kana', with: 'ハナコ'
    fill_in '生年月日', with: '1970-01-01'
    choose '女性'
    click_button '登録'

    new_customer = Customer.order(:id).last
    expect(new_customer.email).to eq('test@example.com')
    expect(new_customer.birthday).to eq(Date.new(1970, 1, 1))
    expect(new_customer.gender).to eq('female')
    expect(new_customer.home_address).to be_nil
    expect(new_customer.work_address).to be_nil
  end

  scenario '職員が顧客、自宅住所、勤務先を登録する' do
    click_link '顧客管理'
    first('div.links').click_link '新規登録'

    fill_in 'メールアドレス', with: 'test@example.com'
    fill_in 'パスワード', with: 'pw'
    fill_in 'form_customer_family_name', with: '試験'
    fill_in 'form_customer_given_name', with: '花子'
    fill_in 'form_customer_family_name_kana', with: 'シケン'
    fill_in 'form_customer_given_name_kana', with: 'ハナコ'
    fill_in '生年月日', with: '1970-01-01'
    choose '女性'
    check '自宅住所を入力する'
    within('fieldset#home-address-fields') do
      fill_in '郵便番号', with: '1000001'
      select '東京都', from: '都道府県'
      fill_in '市区町村', with: '千代田区'
      fill_in '町域、番地など', with: '千代田1-1'
      fill_in '建物名、部屋番号など', with: ''
    end
    check '勤務先を入力する'
    within('fieldset#work-address-fields') do
      fill_in '会社名', with: 'テスト社'
      fill_in '部署名', with: ''
      fill_in '郵便番号', with: ''
      select '', from: '都道府県'
      fill_in '市区町村', with: ''
      fill_in '町域、番地など', with: ''
      fill_in '建物名、部屋番号など', with: ''
    end
    click_button '登録'

    new_customer = Customer.order(:id).last
    expect(new_customer.email).to eq('test@example.com')
    expect(new_customer.birthday).to eq(Date.new(1970, 1, 1))
    expect(new_customer.gender).to eq('female')
    expect(new_customer.home_address.postal_code).to eq('1000001')
    expect(new_customer.work_address.company_name).to eq('テスト社')
  end

  scenario '職員が顧客、自宅住所、勤務先を更新する' do
    click_link '顧客管理'
    first('table.listing').click_link '編集'

    fill_in 'メールアドレス', with: 'test@example.com'
    within('fieldset#home-address-fields') do
      fill_in '郵便番号', with: '9999999'
    end
    within('fieldset#work-address-fields') do
      fill_in '会社名', with: 'テスト社'
    end
    click_button '更新'

    customer.reload
    expect(customer.email).to eq('test@example.com')
    expect(customer.home_address.postal_code).to eq('9999999')
    expect(customer.work_address.company_name).to eq('テスト社')
  end

  scenario '職員が顧客の自宅住所と勤務先を削除する' do
    click_link '顧客管理'
    first('table.listing').click_link '編集'

    uncheck '自宅住所を入力する'
    uncheck '勤務先を入力する'
    click_button '更新'

    customer.reload
    expect(customer.home_address).to be_nil
    expect(customer.work_address).to be_nil
  end

  scenario '職員が勤務先データのない既存顧客に会社名の情報を追加する' do
    customer.work_address.mark_for_destruction
    customer.save!
    click_link '顧客管理'
    first('table.listing').click_link '編集'

    check '勤務先を入力する'
    within('fieldset#work-address-fields') do
      fill_in '会社名', with: 'テスト社'
    end
    click_button '更新'

    customer.reload
    expect(customer.work_address).not_to be_nil
    expect(customer.work_address.company_name).to eq('テスト社')
  end

  scenario '職員が生年月日と自宅の郵便番号に無効な値を入力する' do
    click_link '顧客管理'
    first('table.listing').click_link '編集'

    fill_in '生年月日', with: '2100-01-01'
    within('fieldset#home-address-fields') do
      fill_in '郵便番号', with: 'XYZ'
    end
    click_button '更新'

    expect(page).to have_css('header span.alert')
    expect(page).to have_css('div.field_with_errors input#form_customer_birthday')
    expect(page).to have_css('div.field_with_errors input#form_home_address_postal_code')
  end
end
