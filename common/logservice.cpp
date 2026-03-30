#include "src/platform/log/common/logservice.h"

#include "src/platform/log/spdlog/spdlogger.h"

LogService::LogService(const std::string& name) : ILogService(name) {
  logger_ = std::make_shared<Spdlogger>(name);
}

void LogService::dispose() {
  if (logger_) {
    logger_->dispose();
    logger_.reset();
  }
}

LogLevel LogService::getLevel() const {
  if (!logger_) return LogLevel::Off;

  return logger_->getLevel();
}

void LogService::setLevel(LogLevel level) {
  if (logger_) {
    logger_->setLevel(level);
  }
}

void LogService::log(LogLevel level, std::string&& msg) {
  if (logger_) {
    logger_->log(level, std::move(msg));
  }
}

void LogService::log(LogLevel level, std::string_view file, int line,
                     std::string_view func, std::string&& msg) {
  if (logger_) {
    logger_->log(level, file, line, func, std::move(msg));
  }
}

void LogService::flush() {
  if (logger_) {
    logger_->flush();
  }
}

NullLogService::NullLogService(const std::string& name) : ILogService(name) {}

LogLevel NullLogService::getLevel() const { return LogLevel::Off; }

void NullLogService::setLevel(LogLevel level) {}

void NullLogService::log(LogLevel level, std::string&& msg) {}

void NullLogService::log(LogLevel level, std::string_view file, int line,
                         std::string_view func, std::string&& msg) {}

void NullLogService::flush() {}
