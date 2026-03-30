unset(TARGET_NAME)
unset(SRCS)

set(TARGET_NAME log)

aux_source_directory(. SRCS)

aux_source_directory(common SRCS)

aux_source_directory(spdlog SRCS)

add_library(${TARGET_NAME} ${SRCS})

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

target_link_libraries(${TARGET_NAME} PUBLIC fmt::fmt spdlog::spdlog Qt::Core
                                            Qt::Quick)

add_subdirectory(spdlog/test)
