
cmake_minimum_required(VERSION 3.12)
project(MDSpan
  VERSION 0.0.1
  LANGUAGES CXX
)

################################################################################

set(CMAKE_CXX_STANDARD 20)

################################################################################

#option(MDSPAN_ENABLE_TESTING "Enable tests." Off)
option(MDSPAN_ENABLE_EXAMPLES "Build examples." Off)

################################################################################

add_library(mdspan INTERFACE)
add_library(std::mdspan ALIAS mdspan)

target_include_directories(mdspan INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

#target_compile_features(mdspan INTERFACE cxx_std_20)
#target_compile_options(mdspan INTERFACE -fconcepts)

################################################################################

install(TARGETS mdspan EXPORT mdspanTargets
  INCLUDES DESTINATION include
)

install(EXPORT mdspanTargets
    FILE mdspanTargets.cmake
    NAMESPACE std::
    DESTINATION cmake
)

export(TARGETS mdspan
    NAMESPACE std::
    FILE mdspanTargets.cmake
)

install(DIRECTORY include/experimental DESTINATION include)

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/MDSpanConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/MDSpanConfig.cmake
  INSTALL_DESTINATION cmake
)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/MDSpanConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MDSpanConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/MDSpanConfigVersion.cmake
    DESTINATION cmake
)

################################################################################

#if(MDSPAN_ENABLE_TESTING)
  #add_subdirectory(tests)
#endif()
#
if(MDSPAN_ENABLE_EXAMPLES)
 add_subdirectory(examples)
endif()
