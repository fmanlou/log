#include "src/platform/log/common/ilogservice.h"

ILogService::ILogService(const std::string& name) : ILogger(name) {}

void ILogServiceInjectMinix::inject(
    const std::shared_ptr<ILogService>& service) {
  if (logService) return;

  logService = service;
}

std::shared_ptr<ILogService> logService;
