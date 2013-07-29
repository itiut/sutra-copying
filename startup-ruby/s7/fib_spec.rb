require './fib'

describe Fib do
  describe "#at" do
    before do
      @fib = Fib.new
    end

    it "最初の数値は0" do
      @fib.at(1).should == 0
    end

    it "7番目の数値は8" do
      @fib.at(7).should == 8
    end

    it "0を指定するとRuntimeError" do
      lambda{ @fib.at(0) }.should raise_error(RuntimeError)
    end

    after do
    end
  end
end
