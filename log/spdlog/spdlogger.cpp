#include "log/spdlog/spdlogger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

spdlog::level::level_enum levelToSpdlog(LogLevel level) {
  switch (level) {
    case LogLevel::Trace:
      return spdlog::level::trace;
    case LogLevel::Debug:
      return spdlog::level::debug;
    case LogLevel::Info:
      return spdlog::level::info;
    case LogLevel::Warning:
      return spdlog::level::warn;
    case LogLevel::Error:
      return spdlog::level::err;
    case LogLevel::Off:
      return spdlog::level::off;
    default:
      return spdlog::level::info;
  }
}

LogLevel spdlogToLevel(spdlog::level::level_enum level) {
  switch (level) {
    case spdlog::level::trace:
      return LogLevel::Trace;
    case spdlog::level::debug:
      return LogLevel::Debug;
    case spdlog::level::info:
      return LogLevel::Info;
    case spdlog::level::warn:
      return LogLevel::Warning;
    case spdlog::level::err:
      return LogLevel::Error;
    case spdlog::level::off:
      return LogLevel::Off;
    default:
      return LogLevel::Info;
  }
}

std::string shortFileName(std::string_view file) {
  auto pos = file.find_last_of("/\\");
  if (pos != std::string_view::npos) {
    return std::string(file.substr(pos + 1));
  }
  return std::string(file);
}

Spdlogger::Spdlogger(const std::string& name) : ILogger(name) {
  logger_ = spdlog::stdout_color_mt(name);

  logger_->set_level(level_);
  logger_->set_pattern(
      "[%Y-%m-%d %H:%M:%S.%e] [%n %P] [thread %t] [%^%l%$] %v");
}

Spdlogger::~Spdlogger() {
  if (logger_) {
    logger_->flush();
    spdlog::drop(logger_->name());
  }
}

LogLevel Spdlogger::getLevel() const { return spdlogToLevel(level_); }

void Spdlogger::setLevel(LogLevel level) {
  level_ = levelToSpdlog(level);
  logger_->set_level(level_);
}

void Spdlogger::log(LogLevel level, std::string&& msg) {
  logger_->log(levelToSpdlog(level), msg);
}

void Spdlogger::log(LogLevel level, std::string_view file, int line,
                    std::string_view func, std::string&& msg) {
  auto formattedMsg = format(file, line, func, std::move(msg));
  log(level, std::move(formattedMsg));
}

void Spdlogger::flush() { logger_->flush(); }

std::string Spdlogger::format(std::string_view file, int line,
                              std::string_view func, std::string&& msg) const {
  return fmt::format("[{}:{}] {}", shortFileName(file), line, msg);
}