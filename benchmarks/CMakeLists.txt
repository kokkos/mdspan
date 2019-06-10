
function(mdspan_add_benchmark EXENAME)
  add_executable(${EXENAME} ${EXENAME}.cpp)
  target_link_libraries(${EXENAME} mdspan benchmark::benchmark)
endfunction(mdspan_add_benchmark)

find_package(benchmark)

add_subdirectory(sum)
