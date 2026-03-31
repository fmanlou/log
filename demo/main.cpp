#include <memory>

#include "log/common/ilogservice.h"
#include "log/common/logservice.h"

int main() {
  getLogService() = std::make_shared<LogService>("log_demo");
  getLogService()->setLevel(LogLevel::Info);
  logInfo("macro: {}", "ok");
  getLogService()->info("direct: {}", "ok");
  getLogService()->flush();
  getLogService().reset();
  return 0;
}
