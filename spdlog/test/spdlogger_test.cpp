#include "src/platform/log/spdlog/spdlogger.h"

#include <gtest/gtest.h>

TEST(Spdlogger, ShortFileName) {
  ASSERT_EQ(shortFileName("/path/to/file.cpp"), "file.cpp");
  ASSERT_EQ(shortFileName("C:\\path\\to\\file.cpp"), "file.cpp");
  ASSERT_EQ(shortFileName("file.cpp"), "file.cpp");
}

TEST(Spdlogger, LogLevelConversion) {
  ASSERT_EQ(levelToSpdlog(LogLevel::Trace), spdlog::level::trace);
  ASSERT_EQ(levelToSpdlog(LogLevel::Debug), spdlog::level::debug);
  ASSERT_EQ(levelToSpdlog(LogLevel::Info), spdlog::level::info);
  ASSERT_EQ(levelToSpdlog(LogLevel::Warning), spdlog::level::warn);
  ASSERT_EQ(levelToSpdlog(LogLevel::Error), spdlog::level::err);
  ASSERT_EQ(levelToSpdlog(LogLevel::Off), spdlog::level::off);

  ASSERT_EQ(spdlogToLevel(spdlog::level::trace), LogLevel::Trace);
  ASSERT_EQ(spdlogToLevel(spdlog::level::debug), LogLevel::Debug);
  ASSERT_EQ(spdlogToLevel(spdlog::level::info), LogLevel::Info);
  ASSERT_EQ(spdlogToLevel(spdlog::level::warn), LogLevel::Warning);
  ASSERT_EQ(spdlogToLevel(spdlog::level::err), LogLevel::Error);
  ASSERT_EQ(spdlogToLevel(spdlog::level::off), LogLevel::Off);
}

TEST(Spdlogger, LogMessage) {
  auto spdlLogger = std::make_shared<Spdlogger>("TestLogger");
  spdlLogger.reset();
  ASSERT_EQ(spdlog::get("TestLogger"), nullptr);
}

TEST(Spdlogger, Dispose) {
  auto spdlLogger = std::make_shared<Spdlogger>("DisposeLogger");
  spdlLogger->dispose();
  ASSERT_EQ(spdlog::get("DisposeLogger"), nullptr);
}
