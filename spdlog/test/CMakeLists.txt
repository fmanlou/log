include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

aux_source_directory(. TEST_SOURCES)

add_executable(platform_log_spdlog_test ${TEST_SOURCES})

target_link_libraries(platform_log_spdlog_test PRIVATE log GTest::gtest_main)

add_test(NAME platform_log_spdlog_test COMMAND platform_log_spdlog_test)
