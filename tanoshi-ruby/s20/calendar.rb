require 'date'

def print_calendar
  today = Date.today
  first_day = Date.new(today.year, today.month, 1)
  last_day = (first_day >> 1) - 1

  print today.strftime("       %b %Y\n")
  print                " Su Mo Tu We Th Fr Sa\n"
  print "   " * first_day.wday
  (1..last_day.day).each do |i|
    printf("%3d", i)
    print "\n" if (first_day.wday + i) % 7 == 0
  end
  print "\n"
end

print_calendar
