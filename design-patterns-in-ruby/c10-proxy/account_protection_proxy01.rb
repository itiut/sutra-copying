require 'etc'

class BankAccount
  attr_reader :balance

  def initialize(starting_balance = 0)
    @balance = starting_balance
  end

  def deposit(amount)
    @balance += amount
  end

  def withdraw(amount)
    @balance -= amount
  end
end

class AccountProtectionProxy
  def initialize(real_account, owner_name)
    @subject = real_account
    @owner_name = owner_name
  end

  def deposit(amount)
    check_access
    @subject.deposit(amount)
  end

  def withdraw(amount)
    check_access
    @subject.withdraw(amount)
  end

  def balance
    check_access
    @subject.balance
  end

  def check_access
    fail "Illegal access: #{Etc.getlogin} cannot access account." if Etc.getlogin != @owner_name
  end
end

account = BankAccount.new(100)
proxy = AccountProtectionProxy.new(account, 'nobody')
proxy.withdraw(10) # => RuntimeError
