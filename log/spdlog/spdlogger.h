#pragma once

#include <spdlog/spdlog.h>

#include "log/common/log.h"

namespace logging {

spdlog::level::level_enum levelToSpdlog(LogLevel level);

LogLevel spdlogToLevel(spdlog::level::level_enum level);

class Spdlogger : public ILogger {
 public:
  Spdlogger(const std::string& name);

  ~Spdlogger() override;

  LogLevel getLevel() const override;

  void setLevel(LogLevel level) override;

  void log(LogLevel level, std::string&& msg) override;

  void flush() override;

 private:
  spdlog::level::level_enum level_{spdlog::level::info};
  std::shared_ptr<spdlog::logger> logger_;
};

}  // namespace logging
