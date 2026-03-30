include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  TARGETS ${TARGET_NAME}
  EXPORT logTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/common/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/common"
        FILES_MATCHING
        PATTERN "*.h")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/spdlog"
        FILES_MATCHING
        PATTERN "*.h")

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
