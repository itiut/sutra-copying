text = [
        "From: Bob",
        "To: Alice",
        "Subject: Hello",
        ""
       ]

text.each do |line|
  case line
  when /^From:/i
    puts "Find sender information."
  when /^To:/i
    puts "Find reciever information."
  when /^Subject:/i
    puts "Find subject information."
  when /^$/
    puts "Finish analyzing header."
    exit
  else
    # do nothing
  end
end
