require 'singleton'

class DatabaseConnectionManager
  include Singleton

  def connection
    # return database connection...
  end
end

class PreferenceManager
  def initialize
    @reader = PrefReader.new
    @writer = PrefWriter.new
    @preferences = { display_splash: false, background_color: false }
  end

  def save
    @writer.write(DatabaseConnectionManager.instance, @preferences)
  end

  def read
    @preferences = @reader.read(DatabaseConnectionManager.instance)
  end
end

class PrefWriter
  def write(connection_manager, preferences)
    connection = connection_manager.connection
    # write preferences...
  end
end

class PrefReader
  def read(connection_manager)
    connection = connection_manager.connection
    # read and return preferences
  end
end
