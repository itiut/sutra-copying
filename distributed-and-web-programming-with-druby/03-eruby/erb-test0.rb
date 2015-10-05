require 'drb/drb'
require 'erb'

erb_src = <<EOS
<ul>
<% there.to_a.each do |k, v| %>
  <li><%= k %>: <%= v %></li>
<% end %>
</ul>
EOS

DRb.start_service
there = DRbObject.new_with_uri('druby://localhost:12345')
ERB.new(erb_src).run
