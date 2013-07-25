def call_each(array, &block)
  array.each(&block)
end

call_each [1, 2, 3] do |item|
  p item
end
