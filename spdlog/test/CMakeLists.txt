find_package(GTest REQUIRED)

aux_source_directory(. TEST_SOURCES)

add_executable(platform_log_spdlog_test ${TEST_SOURCES})

target_link_libraries(platform_log_spdlog_test PRIVATE platform GTest::GTest
                                                       GTest::gtest_main)
