#pragma once

class IDisposable {
 public:
  virtual ~IDisposable() = default;

  virtual void dispose() {}
};
