#!/usr/bin/env ruby
# list 3.8
require 'cgi'
require 'drb/drb'
require 'erb'
require 'nkf'

class ReminderWriter
  include ERB::Util

  ERB_SRC = <<-EOS
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

<h2>New Item</h2>
<form action="<%=script_name(cgi)%>" method="post">
  <input name="item" value="" type="text">
  <input name="add" value="add" type="submit">
</form>
  EOS

  def initialize(reminder)
    @reminder = reminder
    @erb = ERB.new(ERB_SRC)
  end

  def to_html(cgi)
    @erb.result(binding)
  end

  def script_name(cgi)
    cgi.script_name
  end
end

def kconv(str)
  NKF.nkf('-wdXm0', str.to_s)
end

def do_request(cgi, reminder)
  item, _ = cgi['item']
  return if item.nil? || item.empty?
  reminder.add(kconv(item))
end

def main
  DRb.start_service
  there = DRbObject.new_with_uri('druby://localhost:12345')
  writer = ReminderWriter.new(there)

  cgi = CGI.new('html5')
  do_request(cgi, there)

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
          + writer.to_html(cgi)
        end
      end
    end
  end
end

main
