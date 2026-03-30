cmake_minimum_required(VERSION 3.20)

project(log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOG_LIBRARY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/library")
if(IS_DIRECTORY "${LOG_LIBRARY_ROOT}")
  list(APPEND CMAKE_PREFIX_PATH "${LOG_LIBRARY_ROOT}/fmt"
       "${LOG_LIBRARY_ROOT}/spdlog")
endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(TARGET_NAME log)

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
