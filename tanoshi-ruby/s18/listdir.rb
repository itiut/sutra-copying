require 'find'

IGNORES = [/^\.$/, /^\.git$/, /^CVS$/, /^RCS$/]

def listdir(top)
  Find.find(top) do |path|
    if FileTest.directory?(path)
      _, base = File.split(path)
      IGNORES.each do |re|
        if re =~ base
          Find.prune
        end
      end
      puts path
    end
  end
end

listdir(ARGV[0])
