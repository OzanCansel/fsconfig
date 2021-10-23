cmake_minimum_required( VERSION 3.10 )
project( fsconfig )

add_library( fsconfig INTERFACE )
add_library( fsconfig::fsconfig ALIAS fsconfig )

target_compile_features( fsconfig INTERFACE cxx_std_17 )
target_include_directories(
    fsconfig INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include( GNUInstallDirs )

install(
    TARGETS fsconfig
    EXPORT fsconfig-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/fsconfig
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

include( CMakePackageConfigHelpers )

install(
    EXPORT fsconfig-targets
    FILE fsconfig-targets.cmake
    NAMESPACE fsconfig::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsconfig
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/fsconfig-config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/fsconfig-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsconfig
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/fsconfig-config-version.cmake
    VERSION 3.1
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    ${CMAKE_BINARY_DIR}/cmake/fsconfig-config.cmake
    ${CMAKE_BINARY_DIR}/cmake/fsconfig-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsconfig
)

export( EXPORT fsconfig-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/fsconfig-targets.cmake
    NAMESPACE fsconfig::
)

enable_testing()
add_subdirectory( test )