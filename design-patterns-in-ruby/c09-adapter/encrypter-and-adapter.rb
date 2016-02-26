class Encrypter
  def initialize(key)
    @key = key
  end

  def encrypt(reader, writer)
    key_index = 0
    until reader.eof?
      clear_char = reader.getc
      encrypted_char = clear_char.ord ^ @key[key_index].ord
      writer.putc(encrypted_char)
      key_index = (key_index + 1) % @key.length
    end
  end
end

class StringIOAdapter
  def initialize(string)
    @string = string
    @position = 0
  end

  def getc
    fail EOFError if @position >= @string.length
    ch = @string[@position]
    @position += 1
    ch
  end

  def eof?
    @position >= @string.length
  end
end

encrypter = Encrypter.new('XYZZY')
reader = StringIOAdapter.new("We attach at dawn\n")
writer = File.open('out.txt', 'w')
encrypter.encrypt(reader, writer)
writer.close

reader = File.open('out.txt')
encrypter.encrypt(reader, $stdout)
