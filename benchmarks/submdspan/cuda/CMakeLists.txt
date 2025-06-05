
if(CMAKE_CUDA_COMPILER_ID STREQUAL "NVIDIA")
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --extended-lambda")
endif()

mdspan_add_cuda_benchmark(submdspan_cuda)
target_include_directories(submdspan_cuda PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/benchmarks/submdspan>
)
