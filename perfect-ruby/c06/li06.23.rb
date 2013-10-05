module RefineModule
  refine String do
    def hello
      puts "#{self} hello"
    end
  end
end

using RefineModule

'Bob'.hello
