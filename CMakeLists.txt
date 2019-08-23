
cmake_minimum_required(VERSION 3.12)
project(MDSpan
  VERSION 0.0.1
  LANGUAGES CXX
)

################################################################################

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################################################################

option(MDSPAN_ENABLE_TESTS "Enable tests." Off)
option(MDSPAN_ENABLE_EXAMPLES "Build examples." Off)
option(MDSPAN_ENABLE_BENCHMARKS "Enable benchmarks." Off)
option(MDSPAN_ENABLE_COMP_BENCH "Enable compilation benchmarks." Off)
option(MDSPAN_ENABLE_CUDA "Enable Cuda tests/benchmarks/examples if tests/benchmarks/examples are enabled." Off)
option(MDSPAN_ENABLE_OPENMP "Enable OpenMP benchmarks if benchmarks are enabled." On)

# Option to override which C++ standard to use
set(MDSPAN_CXX_STANDARD DETECT CACHE STRING "Override the default CXX_STANDARD to compile with.")
set_property(CACHE MDSPAN_CXX_STANDARD PROPERTY STRINGS DETECT 11 14 17 20)

option(MDSPAN_ENABLE_CONCEPTS "Try to enable concepts support by giving extra flags." On)

################################################################################

# Decide on the standard to use
if(MDSPAN_CXX_STANDARD STREQUAL "17")
  if("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "Using C++17 standard")
    set(CMAKE_CXX_STANDARD 17)
  else()
    message(FATAL_ERROR "Requested MDSPAN_CXX_STANDARD \"17\" not supported by provided C++ compiler")
  endif()
elseif(MDSPAN_CXX_STANDARD STREQUAL "14")
  if("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "Using C++14 standard")
    set(CMAKE_CXX_STANDARD 14)
  else()
    message(FATAL_ERROR "Requested MDSPAN_CXX_STANDARD \"14\" not supported by provided C++ compiler")
  endif()
elseif(MDSPAN_CXX_STANDARD STREQUAL "11")
  message(STATUS "Using C++11 standard")
  set(CMAKE_CXX_STANDARD 11)
elseif(MDSPAN_CXX_STANDARD STREQUAL "20")
  if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(STATUS "Using C++20 standard")
    set(CMAKE_CXX_STANDARD 20)
  else()
    message(FATAL_ERROR "Requested MDSPAN_CXX_STANDARD \"20\" not supported by provided C++ compiler")
  endif()
else()
  if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD 20)
    message(STATUS "Detected support for C++20 standard")
  elseif("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD 17)
    message(STATUS "Detected support for C++17 standard")
  elseif("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD 14)
    message(STATUS "Detected support for C++14 standard")
  elseif("cxx_std_11" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD 11)
    message(STATUS "Newest supported C++ standard detected is C++11.")
  else()
    message(FATAL_ERROR "Cannot detect CXX_STANDARD of C++11 or newer.")
  endif()
endif()

################################################################################

if(MDSPAN_ENABLE_CONCEPTS)
  if(CMAKE_CXX_STANDARD STREQUAL "20")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-fconcepts" COMPILER_SUPPORTS_FCONCEPTS)
    if(COMPILER_SUPPORTS_FCONCEPTS)
      message(STATUS "Using \"-fconcepts\" to enable concepts support")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
    else()
      CHECK_CXX_COMPILER_FLAG("-fconcepts-ts" COMPILER_SUPPORTS_FCONCEPTS_TS)
      if(COMPILER_SUPPORTS_FCONCEPTS)
        message(STATUS "Using \"-fconcepts-ts\" to enable concepts support")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts-ts")
      endif()
    endif()
    # Otherwise, it's possible that the compiler supports concepts without flags,
    # but if it doesn't, they just won't be used, which is fine
  endif()
endif()

################################################################################

if(MDSPAN_ENABLE_CUDA)
  include(CheckLanguage)
  check_language(CUDA)
  if(CMAKE_CUDA_COMPILER)
    message(STATUS "Using ${CMAKE_CXX_STANDARD} as CMAKE_CUDA_STANDARD")
    set(CMAKE_CUDA_STANDARD ${CMAKE_CXX_STANDARD})
    set(CMAKE_CUDA_STANDARD_REQUIRED ON)
    enable_language(CUDA)
  else()
    message(FATAL_ERROR "Requested CUDA support, but no CMAKE_CUDA_COMPILER available")
  endif()
endif()

################################################################################

add_library(mdspan INTERFACE)
add_library(std::mdspan ALIAS mdspan)

target_include_directories(mdspan INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

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

if(MDSPAN_ENABLE_TESTS)
  add_subdirectory(tests)
  add_subdirectory(compilation_tests)
endif()

if(MDSPAN_ENABLE_EXAMPLES)
 add_subdirectory(examples)
endif()

if(MDSPAN_ENABLE_BENCHMARKS)
 add_subdirectory(benchmarks)
endif()

if(MDSPAN_ENABLE_COMP_BENCH)
  add_subdirectory(comp_bench)
endif()
