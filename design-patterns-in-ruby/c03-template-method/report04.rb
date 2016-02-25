class Report
  def initialize
    @title = '月次報告'
    @text = %w(順調 最高の調子)
  end

  def output_report
    output_start
    output_head
    output_body_start
    output_body
    output_body_end
    output_end
  end

  def output_body
    @text.each do |line|
      output_line(line)
    end
  end

  def output_start
  end

  def output_head
    ouptut_line(@title)
  end

  def output_body_start
  end

  def output_line(_line)
    fail 'Called abstract method: output_line'
  end

  def output_body_end
  end

  def output_end
  end
end

class HTMLReport < Report
  def output_start
    puts '<html>'
  end

  def output_head
    puts '<head>'
    puts "  <title>#{@title}</title>"
    puts '</head>'
  end

  def output_body_start
    puts '<body>'
  end

  def output_line(line)
    puts "  <p>#{line}</p>"
  end

  def output_body_end
    puts '</body>'
  end

  def output_end
    puts '</html>'
  end
end

class PlainReport < Report
  def output_head
    puts "*** #{@title} ***"
  end

  def output_line(line)
    puts line
  end
end

puts '# html'
HTMLReport.new.output_report

puts "\n# plain"
PlainReport.new.output_report
