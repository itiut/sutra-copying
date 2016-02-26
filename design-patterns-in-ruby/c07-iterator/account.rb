class Account
  attr_accessor :name, :balance

  def initialize(name, balance)
    @name = name
    @balance = balance
  end

  def <=>(other)
    balance <=> other.balance
  end
end

class Portfolio
  include Enumerable

  def initialize
    @accounts = []
  end

  def each(&block)
    @accounts.each(&block)
  end

  def add_account(account)
    @accounts << account
  end
end

portfolio = Portfolio.new
portfolio.add_account(Account.new('Bank 1', 300))
portfolio.add_account(Account.new('Bank 2', 2_400))
portfolio.add_account(Account.new('Bank 3', 900))

puts portfolio.any? { |account| account.balance > 2_000 }
puts portfolio.all? { |account| account.balance >= 10 }
