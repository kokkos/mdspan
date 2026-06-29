mdspan_add_example(aligned_accessor)

if(MDSPAN_ENABLE_OPENMP)
  if(OpenMP_CXX_FOUND)
    target_link_libraries(aligned_accessor OpenMP::OpenMP_CXX)
    target_compile_definitions(aligned_accessor MDSPAN_ENABLE_OPENMP)
    message(STATUS "Building aligned accessor example with OpenMP")
  endif()
endif()
