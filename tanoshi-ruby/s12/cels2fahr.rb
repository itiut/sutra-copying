def cels2fahr(cels)
  cels * 9.0 / 5.0 + 32.0
end

p cels2fahr 30
p cels2fahr 20
p cels2fahr 10

puts "cels  fahr"
1.upto(100) do |i|
  printf(" %3d %5.1f\n", i, cels2fahr(i))
end
