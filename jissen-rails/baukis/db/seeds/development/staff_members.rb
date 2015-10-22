StaffMember.create!(
  email: 'taro@example.com',
  family_name: '山田',
  given_name: '太郎',
  family_name_kana: 'ヤマダ',
  given_name_kana: 'タロウ',
  password: 'password',
  start_date: Date.today
)

family_names = %w(
  佐藤:サトウ:sato
  鈴木:スズキ:suzuki
  高橋:タカハシ:takahashi
  田中:タナカ:tanaka
)

given_names = %w(
  二郎:ジロウ:jiro
  三郎:サブロウ:saburo
  松子:マツコ:matsuko
  竹子:タケコ:takeko
  梅子:ウメコ:umeko
)

20.times do |i|
  fn = family_names[i % 4].split(':')
  gn = given_names[i % 5].split(':')

  StaffMember.create!(
    email: "#{fn[2]}.#{gn[2]}@example.com",
    family_name: fn[0],
    given_name: gn[0],
    family_name_kana: fn[1],
    given_name_kana: gn[1],
    password: 'password',
    start_date: (100 - i).days.ago.to_date,
    end_date: i == 0 ? Date.today : nil,
    suspended: i == 1
  )
end
