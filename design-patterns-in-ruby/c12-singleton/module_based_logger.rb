module ModuleBasedLogger
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

ModuleBasedLogger.level = ModuleBasedLogger::ERROR

ModuleBasedLogger.info('コンピュータがチェスゲームに勝ちました。')
ModuleBasedLogger.warning('ユニットAE-35の故障が予測されました。')
ModuleBasedLogger.error('HAL-9000 機能停止、緊急動作を実行します！')
