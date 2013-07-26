address = "sample@google.com"
/^([^@]+)@(.+)$/ =~ address
p $1
p $2

str = "正規表現は難しい! なんて難しいんだ!"
s = str.gsub(/難しい(んだ)?/) do |_|
  if $1
    "簡単なんだ"
  else
    "簡単だ"
  end
end
p s

def word_capitalize(str)
  str.split("-").map { |elem| elem.capitalize }.join("-")
end

p word_capitalize("in-reply-to")
p word_capitalize("X-MMAILER")
