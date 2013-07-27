def traverse(path)
  if File.directory?(path)
    Dir.open(path) do |dir|
      dir.each do |name|
        next if name == "."
        next if name == ".."
        traverse(path + "/" + name)
      end
    end
  else
    process_file(path)
  end
end

def process_file(path)
  puts File.basename(path)
end

def print_libraries
  $:.each do |path|
    traverse(path)
  end
end

print_libraries
