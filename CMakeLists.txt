cmake_minimum_required(VERSION 3.20)

project(log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

unset(TARGET_NAME)
unset(SRCS)

set(TARGET_NAME log)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog)

aux_source_directory(. SRCS)
aux_source_directory(common SRCS)
aux_source_directory(spdlog SRCS)

add_library(${TARGET_NAME} ${SRCS})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} PUBLIC fmt::fmt spdlog::spdlog)

option(LOG_BUILD_TESTS "Build log unit tests" ON)
if(LOG_BUILD_TESTS)
  enable_testing()
  add_subdirectory(spdlog/test)
endif()
