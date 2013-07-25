def fetch_and_downcase(array, index)
  if str = array[index]
    str.downcase
  end
end

array = ["Boo", "Foo", "Woo"]
p fetch_and_downcase(array, 1)

hash = {0 => "Boo", 1 => "Foo", 2 => "Woo"}
p fetch_and_downcase(hash, 1)
