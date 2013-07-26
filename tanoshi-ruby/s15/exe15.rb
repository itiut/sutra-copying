wday = {
  sunday: "日曜日", monday: "月曜日", tuesday: "火曜日", wednesday: "水曜日",
  thursday: "木曜日", friday: "金曜日", saturday: "土曜日"
}

p wday[:sunday]
p wday[:monday]
p wday[:saturday]

p wday.size

wday.each do |key, value|
  puts "「#{key}」は#{value}のことです。"
end

def str2hash(str)
  array = str.split
  hash = {}
  1.step(array.size - 1, 2) do |i|
    hash[array[i - 1]] = array[i]
  end
  hash
end

p str2hash("blue 青 white 白\nred 赤")
