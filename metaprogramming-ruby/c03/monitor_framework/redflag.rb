def event(name, &block)
  @events[name] = block
end

def setup(&block)
  @setups << block
end

# Dir.glob('*events.rb').each { |file| load file }

# @events.each do |name, alert|
#   @setups.each do |setup|
#     setup.call
#   end
#   puts "ALERT: #{name}" if alert.call
# end



Dir.glob('*events.rb').each do |file|
  @events = {}
  @setups = []
  load file
  @events.each do |name, event|
    env = Object.new
    @setups.each do |setup|
      env.instance_eval &setup
    end
    puts "ALERT: #{name}" if env.instance_eval &event
  end
end
