Administrator.find_or_create_by!(email_for_index: 'hanako@example.com') do |m|
  m.email = 'hanako@example.com'
  m.password = 'foobar'
end
