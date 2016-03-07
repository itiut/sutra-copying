require 'pp'
require_relative '../finder'
require_relative '../data_source'
require_relative 'backup'

def backup(dir, find_expression = All.new)
  puts "Backup called, source dir=#{dir} find expr=#{find_expression}"
  Backup.instance.data_sources << DataSource.new(dir, find_expression)
end

def to(backup_directory)
  puts "To called, backup dir=#{backup_directory}"
  Backup.instance.backup_directory = backup_directory
end

def interval(minutes)
  puts "Interval called, interval=#{minutes} minutes"
  Backup.instance.interval = minutes
end

eval(File.read('backup.pr'))
# Backup.instance.run

pp Backup.instance
