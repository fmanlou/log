#include "log/common/ilogservice.h"

ILogService::ILogService(const std::string& name) : ILogger(name) {}

std::shared_ptr<ILogService> logService;
