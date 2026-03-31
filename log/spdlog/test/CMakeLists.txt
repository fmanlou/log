if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/library/googletest")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/library/googletest")
endif()

find_package(GTest CONFIG REQUIRED)

aux_source_directory(. TEST_SOURCES)

add_executable(platform_log_spdlog_test ${TEST_SOURCES})

target_link_libraries(platform_log_spdlog_test PRIVATE log GTest::gtest_main)

add_test(NAME platform_log_spdlog_test COMMAND platform_log_spdlog_test)
