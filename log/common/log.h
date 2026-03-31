#pragma once

#include <fmt/format.h>

#include <cstdarg>
#include <string>
#include <utility>

enum class LogLevel { Off, Trace, Debug, Info, Warning, Error };

class ILogger {
 public:
  ILogger(const std::string& name);

  virtual ~ILogger() = default;

  virtual LogLevel getLevel() const = 0;

  virtual void setLevel(LogLevel level) = 0;

  template <typename... Args>
  void trace(std::string_view fmt, Args&&... args) {
    log(LogLevel::Trace, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(std::string_view fmt, Args&&... args) {
    log(LogLevel::Debug, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void info(std::string_view fmt, Args&&... args) {
    log(LogLevel::Info, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warn(std::string_view fmt, Args&&... args) {
    log(LogLevel::Warning, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(std::string_view fmt, Args&&... args) {
    log(LogLevel::Error, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void log(LogLevel level, std::string_view fmt, Args&&... args) {
    if (level < getLevel()) return;

    log(level, fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...));
  }

  template <typename... Args>
  void trace2(std::string_view file, int line, std::string_view func,
              std::string_view fmt, Args&&... args) {
    log2(LogLevel::Trace, file, line, func, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug2(std::string_view file, int line, std::string_view func,
              std::string_view fmt, Args&&... args) {
    log2(LogLevel::Debug, file, line, func, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void info2(std::string_view file, int line, std::string_view func,
             std::string_view fmt, Args&&... args) {
    log2(LogLevel::Info, file, line, func, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warn2(std::string_view file, int line, std::string_view func,
             std::string_view fmt, Args&&... args) {
    log2(LogLevel::Warning, file, line, func, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error2(std::string_view file, int line, std::string_view func,
              std::string_view fmt, Args&&... args) {
    log2(LogLevel::Error, file, line, func, fmt, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void log2(LogLevel level, std::string_view file, int line,
            std::string_view func, std::string_view fmt, Args&&... args) {
    if (level < getLevel()) return;

    log(level, file, line, func,
        fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...));
  }

  virtual void log(LogLevel level, std::string&& msg) = 0;

  virtual void log(LogLevel level, std::string_view file, int line,
                   std::string_view func, std::string&& msg) = 0;

  virtual void flush() = 0;
};
