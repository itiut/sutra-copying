staff_members = StaffMember.all
256.times do |i|
  m = staff_members.sample
  e = m.events.build
  e.type = if m.active?
             if i.even?
               'logged_in'
             else
               'logged_out'
             end
           else
             'rejected'
           end
  e.occurred_at = (256 - i).hours.ago
  e.save!
end
