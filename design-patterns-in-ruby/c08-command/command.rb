require 'fileutils'

class Command
  attr_accessor :description

  def initialize(description)
    @description = description
  end

  def execute
  end

  def unexecute
  end
end

class CreateFile < Command
  def initialize(path, contents)
    super("Create file: #{path}")
    @path = path
    @contents = contents
  end

  def execute
    File.open(@path, 'w') do |f|
      f.write(@contents)
    end
  end

  def unexecute
    File.delete(@path)
  end
end

class DeleteFile < Command
  def initialize(path)
    super("Delete file: #{path}")
    @path = path
  end

  def execute
    @contents = File.read(@path) if File.exist?(@path)
    File.delete(@path)
  end

  def unexecute
    return unless @contents
    File.open(@path, 'w') do |f|
      f.write(@contents)
    end
  end
end

class CopyFile < Command
  def initialize(source, target)
    super("Copy file: #{source} to #{target}")
    @source = source
    @target = target
  end

  def execute
    @contents = File.read(@source) if File.exist?(@source)
    FileUtils.copy(@source, @target)
  end

  def unexecute
    File.delete(@target)
    return unless @contents
    File.open(@source, 'w') do |f|
      f.write(@contents)
    end
  end
end

class CompositeCommand < Command
  def initialize
    @commands = []
  end

  def add_command(cmd)
    @commands << cmd
  end

  def execute
    @commands.each(&:execute)
  end

  def unexecute
    @commands.reverse_each(&:unexecute)
  end

  def description
    @commands.map(&:description).join("\n")
  end
end

cmds = CompositeCommand.new
cmds.add_command(CreateFile.new('file1.txt', "hello world\n"))
cmds.add_command(CopyFile.new('file1.txt', 'file2.txt'))
cmds.add_command(DeleteFile.new('file1.txt'))

cmds.execute
puts cmds.description

cmds.unexecute
