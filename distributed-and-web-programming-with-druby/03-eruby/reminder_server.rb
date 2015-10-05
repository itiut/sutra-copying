require 'drb/drb'
require_relative '../02-hello-druby/reminder0'

uri = ARGV.shift
uri ||= 'druby://localhost:12345'
DRb.start_service(uri, Reminder.new)

puts DRb.uri
sleep
