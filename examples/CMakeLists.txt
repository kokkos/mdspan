
function(mdspan_add_example EXENAME)
  add_executable(${EXENAME} ${EXENAME}.cpp)
  target_link_libraries(${EXENAME} mdspan)
endfunction(mdspan_add_example)

add_subdirectory(dot_product)
add_subdirectory(subspan)
