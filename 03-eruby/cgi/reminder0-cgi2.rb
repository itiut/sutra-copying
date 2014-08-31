#!/usr/bin/env ruby
# list 3.7
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
<table class="table table-striped table-hover table-bordered">
  <thead>
    <tr>
      <th>Key</th>
      <th>Item</th>
    </tr>
  </thead>
  <tbody>
<% @reminder.to_a.each do |k, v| %>
    <tr>
      <td><%= k %></td>
      <td><%=h v %></td>
    </tr>
<% end %>
  </tbody>
</table>
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
        + cgi.link(rel: 'stylesheet', href: 'https://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css') \
        + cgi.title { 'Reminder' }
      end \
      + cgi.body do
        cgi.div(class: 'container') do
          cgi.h1 { 'Reminder' } \
          + writer.to_html
        end
      end
    end
  end
end

main
