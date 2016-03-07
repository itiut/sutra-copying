class DataSource
  attr_reader :directory, :find_expression

  def initialize(directory, find_expression)
    @directory = directory
    @find_expression = find_expression
  end

  def backup(backup_directory)
    files = @find_expression.evaluate(@directory)
    files.each do |file|
      backup_file(file, backup_directory)
    end
  end

  def backup_file(path, backup_directory)
    copy_path = File.join(backup_directory, path)
    FileUtils.mkdir_p(File.dirname(copy_path))
    FileUtils.cp(path, copy_path)
  end
end
