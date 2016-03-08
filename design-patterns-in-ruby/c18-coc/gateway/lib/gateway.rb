class MessageGateway
  def initialize
    load_adapters
    load_authorizers
  end

  def process_message(message)
    adapter = adapter_for(message)
    adapter.send_message(message)
  end

  def adapter_for(message)
    protocol = message.to.scheme
    adapter_class = protocol.capitalize + 'Adapter'
    adapter_class = self.class.const_get(adapter_class)
    adapter_class.new
  end

  def load_adapters
    lib_dir = File.dirname(__FILE__)
    full_pattern = File.join(lib_dir, 'adapter', '*.rb')
    Dir.glob(full_pattern).each do |file|
      require file
    end
  end

  def load_authorizers
    lib_dir = File.dirname(__FILE__)
    full_pattern = File.join(lib_dir, 'auth', '*.rb')
    Dir.glob(full_pattern).each do |file|
      require file
    end
  end

  def camel_case(string)
    tokens = string.split('.')
    tokens.map!(&:capitalize)
    tokens.join('Dot')
  end

  def worm_case(string)
    tokens = string.split('.')
    tokens.map!(&:downcase)
    tokens.join('_dot_')
  end

  def authorizer_for(message)
    to_host = message.to.host || 'default'
    authorizer_class = camel_case(to_host) + 'Authorizer'
    authorizer_class = self.class.const_get(authorizer_class)
    authorizer_class.new
  end

  def authorized?(message)
    authorizer = authorizer_for(message)
    user_method = worm_case(message.from) + '_authorized?'
    return authorizer.send(user_method, message) if authorizer.respond_to?(user_method)
    authorizer.authorized?(message)
  end
end
