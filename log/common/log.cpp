#include "log/common/log.h"

namespace logging {

std::string shortFileName(std::string_view file) {
  auto pos = file.find_last_of("/\\");
  if (pos != std::string_view::npos) {
    return std::string(file.substr(pos + 1));
  }
  return std::string(file);
}

ILogger::ILogger(const std::string& name) {}

void ILogger::log(LogLevel level, std::string_view file, int line,
                  std::string_view func, std::string&& msg) {
  auto formattedMsg = fmt::format("[{}:{}] {}", shortFileName(file), line, msg);
  log(level, std::move(formattedMsg));
}

}  // namespace logging
