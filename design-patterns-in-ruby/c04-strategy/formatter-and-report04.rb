HTML_FORMATTER = lambda do |context|
  puts '<html>'
  puts '<head>'
  puts "  <title>#{context.title}</title>"
  puts '</head>'
  puts '<body>'
  context.text.each do |line|
    puts "  <p>#{line}</p>"
  end
  puts '</body>'
  puts '</html>'
end

class Report
  attr_reader :title, :text
  attr_accessor :formatter

  def initialize(&formatter)
    @title = '月次報告'
    @text = %w(順調 最高の調子)
    @formatter = formatter
  end

  def output_report
    @formatter.call(self)
  end
end

puts '# html'
report = Report.new(&HTML_FORMATTER)
report.output_report

puts "\n# plain"
report = Report.new do |context|
  puts "*** #{context.title} ***"
  context.text.each do |line|
    puts line
  end
end
report.output_report
