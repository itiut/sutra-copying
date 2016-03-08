class Object
  def self.readable_attribute(name)
    code = %(
      def #{name}
        @#{name}
      end
    )
    class_eval(code)
  end
end

class BankAccount
  readable_attribute :balance

  def initialize(balance)
    @balance = balance
  end
end

p BankAccount.new(1_000).balance
