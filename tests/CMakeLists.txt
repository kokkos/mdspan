
macro(mdspan_add_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} mdspan GTest::GTest GTest::Main)
endmacro()

find_package(GTest REQUIRED)

mdspan_add_test(test_contiguous_layouts)
mdspan_add_test(test_layout_ctors)
mdspan_add_test(test_layout_stride)

