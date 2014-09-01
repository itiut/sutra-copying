require 'webrick'
require 'tofu/tofulet'
require 'rinda/ring'

class TofuletFront
  include DRbUndumped

  def initialize(webrick)
    @webrick = webrick
  end

  def mount_tofulet(point, bartender)
    @webrick.unmount(point)
    @webrick.mount(point, WEBrick::Tofulet, bartender)
  end

  alias_method :mount, :mount_tofulet
end

def main
  DRb.start_service

  logger = WEBrick::Log::New($stderr, WEBrick::Log::DEBUG)

  s = WEBrick::HTTPServer.new(
    Port: 2000,
    AddressFamily: Socket::AF_INET,
    BindAddress: ENV['HOSTNAME'],
    Logger: logger
  )

  front = TofuletFront.new(s)
  provider = Rinda::RingProvider.new(:Tofulet, front, 'tofu-runner')
  provider.provide

  trap('INT') { s.shutdown }
  s.start
end

main
