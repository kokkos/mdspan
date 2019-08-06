
macro(add_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} mdspan GTest::GTest GTest::Main)
endmacro()

find_package(GTest REQUIRED)

add_test(test_contiguous_layouts)
add_test(test_layout_ctors)
add_test(test_layout_stride)

