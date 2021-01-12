
function(mdspan_add_example EXENAME)
  add_executable(${EXENAME} ${EXENAME}.cpp)
  target_link_libraries(${EXENAME} mdspan)
endfunction()

add_subdirectory(dot_product)
add_subdirectory(subspan)
add_subdirectory(tiled_layout)
