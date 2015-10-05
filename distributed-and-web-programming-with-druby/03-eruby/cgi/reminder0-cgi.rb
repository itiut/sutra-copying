#!/usr/bin/env ruby
# list 3.6
require 'cgi'
require 'drb/drb'
require 'erb'

class ReminderWriter
  include ERB::Util

  def initialize(reminder)
    @reminder = reminder
    @erb = ERB.new(erb_src)
  end

  def erb_src
    <<-EOS
<ul>
<% @reminder.to_a.each do |k, v| %>
  <li><%= k %>: <%=h v %></li>
<% end %>
</ul>
    EOS
  end

  def to_html
    @erb.result(binding)
  end
end

def main
  DRb.start_service
  there = DRbObject.new_with_uri('druby://localhost:12345')
  writer = ReminderWriter.new(there)

  cgi = CGI.new('html5')

  cgi.out(charset: 'utf-8') do
    cgi.html(lang: 'ja') do
      cgi.head do
        cgi.meta(charset: 'utf-8') \
        + cgi.title { 'Reminder' }
      end \
      + cgi.body do
        writer.to_html
      end
    end
  end
end

main
