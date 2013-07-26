str = %q(Ruby is an object oriented programming language)
str_array = str.split
p str_array

p str_array.sort

p str_array.sort_by { |s| s.downcase }

p str_array.map { |s| s.capitalize }.join(" ")

hash = {}
hash.default = 0
str.each_char do |c|
  hash[c] += 1
end

hash.each do |key, val|
  print "'", key, "': ", "*" * val, "\n"
end

def kan2num(kan)
  k2n = {
    "一" => 1, "二" => 2, "三" => 3, "四" => 4, "五" => 5,
    "六" => 6, "七" => 7, "八" => 8, "九" => 9, "" => 1
  }
  lank = {
    "千" => 1000, "百" => 100, "十" => 10
  }

  result = 0
  prev = -1
  kan.each_char do |c|
    if k2n.key?(c)
      prev = k2n[c]
    else
      if prev < 0
        result += lank[c]
      else
        result += prev * lank[c]
      end
      prev = -1
    end
  end
  if prev > 0
    result += prev
  end
  result
end


p kan2num("七千百二十三")
p kan2num("千百十一")
p kan2num("百一")
