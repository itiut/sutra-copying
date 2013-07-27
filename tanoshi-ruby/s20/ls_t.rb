require 'find'

def ls_t(dirname)
  Find.find(dirname).sort_by { |path| File.ctime(path) }.each do |path|
    print File.ctime(path), " ", path, "\n"
  end
end

ls_t(ARGV[0])
