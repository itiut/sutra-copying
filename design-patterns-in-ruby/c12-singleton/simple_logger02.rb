class SimpleLogger
  attr_accessor :level

  ERROR = 1
  WARNING = 2
  INFO = 3

  def initialize
    @log = File.open('log.txt', 'w')
    @level = WARNING
  end

  def error(msg)
    @log.puts(msg)
    @log.flush
  end

  def warning(msg)
    @log.puts(msg) if @level >= WARNING
    @log.flush
  end

  def info(msg)
    @log.puts(msg) if @level >= INFO
    @log.flush
  end

  @@instance = self.new

  def self.instance
    @@instance
  end

  private_class_method :new
end

SimpleLogger.instance.info('コンピュータがチェスゲームに勝ちました。')
SimpleLogger.instance.warning('ユニットAE-35の故障が予測されました。')
SimpleLogger.instance.error('HAL-9000 機能停止、緊急動作を実行します！')

SimpleLogger.new # => NoMethodError
