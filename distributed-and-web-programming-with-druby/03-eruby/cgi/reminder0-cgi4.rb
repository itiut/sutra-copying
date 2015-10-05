#!/usr/bin/env ruby
# list 3.9
require 'cgi'
require 'drb/drb'
require 'erb'
require 'nkf'

class ReminderCGI
  include ERB::Util

  ERB_SRC = <<-EOS
<table class="table table-striped table-hover table-bordered">
  <thead>
    <tr>
      <th>Key</th>
      <th>Item</th>
      <th>Delete!</th>
    </tr>
  </thead>
  <tbody>
<% @reminder.to_a.each do |k, v| %>
    <tr>
      <td><%= k %></td>
      <td><%=h v %></td>
      <td>[<%= a_delete(cgi, k) %>X</a>]</td>
    </tr>
<% end %>
  </tbody>
</table>

<h2>New Item</h2>
<form action="<%= script_name(cgi) %>" method="post">
  <input type="hidden" name="cmd" value="add">
  <input type="text" name="item" value="">
  <input type="submit" name="add" value="add">
</form>
  EOS

  def initialize(reminder)
    @reminder = reminder
    @erb = ERB.new(ERB_SRC)
  end

  def to_html(cgi)
    @erb.result(binding)
  end

  def do_request(cgi)
    cmd, _ = cgi['cmd']
    case cmd
    when 'add'
      do_add(cgi)
    when 'delete'
      do_delete(cgi)
    end
  end

  private

  def script_name(cgi)
    cgi.script_name
  end

  def kconv(str)
    NKF.nkf('-wdXm0', str.to_s)
  end

  def make_param(hash)
    hash.map { |k, v|
      u(k) + '=' + u(v)
    }.join('&')
  end

  def anchor(cgi, hash)
    %Q(<a href="#{script_name(cgi)}?#{make_param(hash)}">)
  end
  alias_method :a, :anchor

  def a_delete(cgi, key)
    anchor(cgi, cmd: 'delete', key: key)
  end

  def do_add(cgi)
    item, _ = cgi['item']
    return if item.nil? || item.empty?
    @reminder.add(kconv(item))
  end

  def do_delete(cgi)
    key, _ = cgi['key']
    return if key.nil? || key.empty?
    @reminder.delete(key.to_i)
  end
end

def main
  DRb.start_service
  there = DRbObject.new_with_uri('druby://localhost:12345')
  reminder = ReminderCGI.new(there)

  cgi = CGI.new('html5')
  reminder.do_request(cgi)

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
          + reminder.to_html(cgi)
        end
      end
    end
  end
end

main
