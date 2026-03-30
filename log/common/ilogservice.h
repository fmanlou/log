#pragma once

#include <memory>

#include "log/common/log.h"

class ILogService : public ILogger {
 public:
  ILogService(const std::string& name);

  virtual ~ILogService() = default;
};

extern std::shared_ptr<ILogService> logService;

#define logTrace(...) \
  if (logService) logService->trace2(__FILE__, __LINE__, __func__, __VA_ARGS__)

#define logDebug(...) \
  if (logService) logService->debug2(__FILE__, __LINE__, __func__, __VA_ARGS__)

#define logInfo(...) \
  if (logService) logService->info2(__FILE__, __LINE__, __func__, __VA_ARGS__)

#define logWarning(...) \
  if (logService) logService->warn2(__FILE__, __LINE__, __func__, __VA_ARGS__)

#define logError(...) \
  if (logService) logService->error2(__FILE__, __LINE__, __func__, __VA_ARGS__)
