
function(mdspan_add_benchmark EXENAME)
  add_executable(${EXENAME} ${EXENAME}.cpp)
  target_link_libraries(${EXENAME} mdspan benchmark::benchmark)
  target_include_directories(${EXENAME} PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/benchmarks>
  )
endfunction(mdspan_add_benchmark)

find_package(benchmark REQUIRED)

add_subdirectory(sum)
add_subdirectory(copy)
