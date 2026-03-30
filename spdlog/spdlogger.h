#pragma once

#include <spdlog/spdlog.h>

#include "src/platform/log/common/log.h"

spdlog::level::level_enum levelToSpdlog(LogLevel level);

LogLevel spdlogToLevel(spdlog::level::level_enum level);

std::string shortFileName(std::string_view file);

class Spdlogger : public ILogger {
 public:
  Spdlogger(const std::string& name);

  ~Spdlogger() override;

  void dispose() override;

  LogLevel getLevel() const override;

  void setLevel(LogLevel level) override;

  void log(LogLevel level, std::string&& msg) override;

  void log(LogLevel level, std::string_view file, int line,
           std::string_view func, std::string&& msg) override;

  void flush() override;

 private:
  std::string format(std::string_view file, int line, std::string_view func,
                     std::string&& msg) const;

 private:
  spdlog::level::level_enum level_{spdlog::level::info};
  std::shared_ptr<spdlog::logger> logger_;
};