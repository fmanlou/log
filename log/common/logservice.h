#pragma once

#include <memory>

#include "log/common/ilogservice.h"

namespace logging {

class LogService : public ILogService {
 public:
  LogService(const std::string& name);

  LogLevel getLevel() const override;

  void setLevel(LogLevel level) override;

  void log(LogLevel level, std::string&& msg) override;

  void log(LogLevel level, std::string_view file, int line,
           std::string_view function, std::string&& msg) override;

  void flush() override;

 private:
  std::shared_ptr<ILogger> logger_;
};

class NullLogService : public ILogService {
 public:
  NullLogService(const std::string& name);

  LogLevel getLevel() const override;

  void setLevel(LogLevel level) override;

  void log(LogLevel level, std::string&& msg) override;

  void log(LogLevel level, std::string_view file, int line,
           std::string_view function, std::string&& msg) override;

  void flush() override;
};

}  // namespace logging
