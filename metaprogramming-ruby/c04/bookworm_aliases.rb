class Amazon
  alias :old_reviews_of :reviews_of

  def reviews_of(book)
    start = Time.now
    result = old_reviews_of book
    time_token = Time.now - start
    puts "reviews_of() took more than #{time_token} seconds" if time_token > 2
    result
  rescue
    puts "reviews_of() failed"
    []
  end
end
