
macro(add_compilation_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} mdspan)
endmacro()

add_compilation_test(ctest_constructor_sfinae)
add_compilation_test(ctest_extents_ctors)
add_compilation_test(ctest_standard_layout)
add_compilation_test(ctest_no_unique_address)

