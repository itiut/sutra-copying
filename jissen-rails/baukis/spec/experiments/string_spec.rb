require 'spec_helper'

describe String do
  let(:s) { 'ABC' }

  describe '#<<' do
    example '文字の追加' do
      s << 'D'
      expect(s.size).to eq 4
    end

    example 'nilの追加', :exception do
      expect { s << nil }.to raise_error TypeError
    end
  end
end
