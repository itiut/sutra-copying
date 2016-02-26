s = 'Petter Piper picked a peck of pickled peppers'
s.scan(/[Pp]\w*/) do |word|
  puts "The word is #{word}"
end
puts

h = { name: 'russ', eyes: 'blue', sex: 'male' }
h.each_key do |key|
  puts key
end
puts

h.each_value do |value|
  puts value
end
puts

h.each do |key, value|
  puts "#{key}: #{value}"
end
puts

require 'pathname'
pn = Pathname.new('/usr/lib/ruby/2.0.0')
pn.each_filename do |file|
  puts "File: #{file}"
end
puts

pn.each_entry do |entry|
  puts "Entry: #{entry}"
end
puts

ObjectSpace.each_object(Numeric) do |n|
  puts "The number is #{n}"
end
puts

def subclasses_of(superclass)
  ObjectSpace.each_object(Class).select do |k|
    k.ancestors.include?(superclass) && k != superclass && !k.to_s.include?('::')
  end.uniq.map(&:to_s)
end
p subclasses_of(Numeric)
