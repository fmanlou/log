cmake_minimum_required(VERSION 3.20)

project(log VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LOG_BUILD_TESTS "Build log unit tests" ON)

if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/library")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/library/fmt"
       "${CMAKE_CURRENT_SOURCE_DIR}/library/spdlog")
endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/log/common" SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/log/spdlog" SRCS)

add_library(log ${SRCS})

target_include_directories(
  log
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(log PUBLIC fmt::fmt spdlog::spdlog)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/install.cmake")

if(LOG_BUILD_TESTS)
  enable_testing()
  add_subdirectory(log/spdlog/test)
endif()
