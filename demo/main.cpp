#include <memory>

#include "log/common/ilogservice.h"
#include "log/common/logservice.h"

int main() {
  std::shared_ptr<logging::ILogService> logService =
      std::make_shared<logging::LogService>("log_demo");
  logService->setLevel(logging::LogLevel::Info);
  logInfo("macro: {}", "ok");
  return 0;
}
