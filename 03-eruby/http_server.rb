require 'webrick'

module WEBrick::HTTPServlet
  FileHandler.add_handler('rb', CGIHandler)
end

server = WEBrick::HTTPServer.new(Port: 8080, CGIInterpreter: WEBrick::HTTPServlet::CGIHandler::Ruby)
server.mount('/', WEBrick::HTTPServlet::FileHandler, __dir__ + '/cgi', FancyIndexing: true)

%w(INT TERM).each do |signal|
  trap(signal) { server.stop }
end

server.start
