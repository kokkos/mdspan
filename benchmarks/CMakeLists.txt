
function(mdspan_add_benchmark EXENAME)
  add_executable(${EXENAME} ${EXENAME}.cpp)
  target_link_libraries(${EXENAME} mdspan benchmark::benchmark)
  target_include_directories(${EXENAME} PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/benchmarks>
  )
endfunction(mdspan_add_benchmark)

find_package(benchmark REQUIRED)

function(mdspan_add_cuda_benchmark EXENAME)
  add_executable(${EXENAME} ${EXENAME}.cu)
  target_link_libraries(${EXENAME} PUBLIC mdspan)
  target_include_directories(${EXENAME} PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/benchmarks>
  )
  # This is gross, but it's the best I can do in this version of CMake
  get_target_property(_benchmark_include benchmark::benchmark INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(_benchmark_libs_old benchmark::benchmark INTERFACE_LINK_LIBRARIES)
  get_target_property(_benchmark_libs_imported benchmark::benchmark IMPORTED_LOCATION_RELEASE)
  string(REPLACE "-pthread" "" _benchmark_libs "${_benchmark_libs_old}")
  target_include_directories(${EXENAME} PUBLIC "${_benchmark_include}")
  target_link_libraries(${EXENAME} PUBLIC "${_benchmark_libs};${_benchmark_libs_imported}")
  if(_benchmark_libs_old MATCHES "-pthread")
    target_compile_options(${EXENAME} PUBLIC "-Xcompiler=-pthread")
  endif()
endfunction(mdspan_add_cuda_benchmark)


add_subdirectory(sum)
add_subdirectory(copy)
