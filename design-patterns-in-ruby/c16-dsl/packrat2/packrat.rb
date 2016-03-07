require 'pp'
require 'singleton'
require_relative '../finder'
require_relative 'backup'

class PackRat
  include Singleton

  def initialize
    @backups = []
  end

  def register_backup(backup)
    @backups << backup
  end

  def run
    @backups.map do |backup|
      Thread.new { backup.run }
    end.each(&:join)
  end
end

eval(File.read('backup.pr'))
# PackRat.instance.run

pp PackRat.instance.instance_variable_get(:@backups)
