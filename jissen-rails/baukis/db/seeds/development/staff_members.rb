StaffMember.find_or_create_by!(email_for_index: 'taro@example.com') do |m|
  m.email = 'taro@example.com'
  m.family_name = '山田'
  m.given_name = '太郎'
  m.family_name_kana = 'ヤマダ'
  m.given_name_kana = 'タロウ'
  m.password = 'password'
  m.start_date = Date.today
end
