require './fib'

describe Fib do
  describe "#at" do
    let(:fib) { Fib.new }

    context "with 1" do
      it { fib.at(1).should == 0 }
    end

    context "with 7" do
      it { fib.at(7).should == 8 }
    end

    context "with 0" do
      it { expect { fib.at(0) }.to raise_error(RuntimeError) }
    end
  end
end
