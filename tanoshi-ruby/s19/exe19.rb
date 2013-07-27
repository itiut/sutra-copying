def to_utf8(str_euc, str_sjis)
  str_euc.encode("utf-8") + str_sjis.encode("utf-8")
end

str = to_utf8("あいうえお".encode("euc-jp"), "かきくけこ".encode("sjis"))
p str
p str.encoding
