def du(path)
  size = 0
  Dir.open(path) do |dir|
    dir.each do |name|
      next if name == "."
      next if name == ".."
      next if name == ".git"
      if File.directory?(path + "/" + name)
        du(path + "/" + name)
      else
        size += File.size(path + "/" + name)
      end
    end
  end
  printf("%10d %s\n", size, path)
end

du(ARGV[0])
