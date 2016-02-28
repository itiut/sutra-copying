class ClassBasedLogger
  ERROR = 1
  WARNING = 2
  INFO = 3
  @@log = File.open('log.txt', 'w')
  @@level = WARNING

  class << self
    def error(msg)
      @@log.puts(msg)
      @@log.flush
    end

    def warning(msg)
      @@log.puts(msg) if @@level >= WARNING
      @@log.flush
    end

    def info(msg)
      @@log.puts(msg) if @@level >= INFO
      @@log.flush
    end

    def level=(new_level)
      @@level = new_level
    end

    def level
      @@level
    end
  end
end

ClassBasedLogger.level = ClassBasedLogger::INFO

ClassBasedLogger.info('コンピュータがチェスゲームに勝ちました。')
ClassBasedLogger.warning('ユニットAE-35の故障が予測されました。')
ClassBasedLogger.error('HAL-9000 機能停止、緊急動作を実行します！')
