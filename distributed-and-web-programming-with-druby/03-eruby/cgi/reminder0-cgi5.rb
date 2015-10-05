#!/usr/bin/env ruby
# list 3.11
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

  ERROR_MESSAGE = %q(<p>It seems that the reminder server is downed.</p>)

  def initialize(reminder)
    @reminder = reminder
    @erb = ERB.new(ERB_SRC)
  end

  def to_html(cgi)
    @erb.result(binding)
  rescue DRb::DRbConnError
    ERROR_MESSAGE
  end

  def do_request(cgi)
    cmd, _ = cgi['cmd']
    case cmd
    when 'add'
      do_add(cgi)
    when 'delete'
      do_delete(cgi)
    end
    nil
  rescue DRb::DRbConnError
    ERROR_MESSAGE
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

class UnknownErrorPage
  include ERB::Util

  ERB_SRC = <<-EOS
<p><%=h @error %> - <%=h @error.class %></p>
<ul>
<% @info.each do |line| %>
  <li><%=h line %></li>
<% end %>
</ul>
  EOS

  def initialize(error = $!, info = $@)
    @erb = ERB.new(ERB_SRC)
    @error = error
    @info = info
  end

  def to_html
    @erb.result(binding)
  end
end

def main
  DRb.start_service
  there = DRbObject.new_with_uri('druby://localhost:12345')
  reminder = ReminderCGI.new(there)

  cgi = CGI.new('html5')
  begin
    content = reminder.do_request(cgi)
    content ||= reminder.to_html(cgi)
  rescue
    content = UnknownErrorPage.new($!, $@).to_html
  end

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
          + content
        end
      end
    end
  end
end

main
