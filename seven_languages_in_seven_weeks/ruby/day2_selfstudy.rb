# hash to array
ha = {'1' => 'one', '2' => 'two', '3' => 'three'}
ha.map {|key, val| val}

# array to hash
ar = ['one', 'two', 'three', 'four']
Hash[*ar.map {|e| [e, e]}.flatten]


# each and each_slice
ar = [(0..15).to_a, (0..3).to_a]
ar.each {|e| puts e.join(',')}


# grep
File.open('test.txt', 'r') do |f|
  f.readlines.each_with_index do |line, i|
    if /abc/ =~ line
      puts "#{i}\t#{line}"
    end
  end
end
