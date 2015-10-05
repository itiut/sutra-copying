#!/usr/bin/env ruby
# list 3.2
require 'cgi'
require 'drb/drb'
require 'erb'

cgi = CGI.new('html5')

cgi.out(charset: 'utf-8') do
  cgi.html(lang: 'ja') do
    cgi.head do
      cgi.meta(charset: 'utf-8') +
      cgi.title do
        'Hello, CGI.'
      end
    end +
    cgi.body do
      '<p>こんにちは、世界。</p>'
    end
  end
end
