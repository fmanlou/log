include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(NOT DEFINED LOG_INSTALL_PREFIX)
  set(LOG_INSTALL_PREFIX "${CMAKE_INSTALL_INCLUDEDIR}/log")
endif()

install(
  TARGETS log
  EXPORT logTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/log/common/"
        DESTINATION "${LOG_INSTALL_PREFIX}/common"
        FILES_MATCHING
        PATTERN "*.h")

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/log/spdlog/spdlogger.h"
        DESTINATION "${LOG_INSTALL_PREFIX}/spdlog")

install(
  EXPORT logTargets
  FILE logTargets.cmake
  NAMESPACE log::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/log")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/logConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/logConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/log")

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/logConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/logConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/logConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/log")
