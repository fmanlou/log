#include "log/common/ilogservice.h"

namespace logging {

ILogService::ILogService(const std::string& name) : ILogger(name) {}

}  // namespace logging
