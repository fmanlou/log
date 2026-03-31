cmake_minimum_required(VERSION 3.20)

project(log_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(log 1.0 CONFIG REQUIRED)

add_executable(log_demo main.cpp)
target_link_libraries(log_demo PRIVATE log::log)

enable_testing()
add_test(NAME log_demo_sm COMMAND log_demo)
