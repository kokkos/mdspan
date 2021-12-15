
namespace {
bool dispatch_host = true;
#ifdef _MDSPAN_HAS_CUDA

template<class LAMBDA>
__global__ void dispatch_kernel(const LAMBDA f) {
  f();
}

template<class LAMBDA>
void dispatch(LAMBDA&& f) {
  if(dispatch_host) {
    (LAMBDA&&)f();
  } else {
    dispatch_kernel<<<1,1>>>((LAMBDA&&)f);
    cudaDeviceSynchronize();
  }
}

template<class T>
T* allocate_array(size_t size) {
  T* ptr = nullptr;
  if(dispatch_host == true)
    ptr = new T[size];
  else
    cudaMallocManaged(&ptr, sizeof(T)*size);
  return ptr;
}

template<class T>
void free_array(T* ptr) {
  if(dispatch_host == true)
    delete [] ptr;
  else
    cudaFree(ptr);
}

#define __MDSPAN_TESTS_DISPATCH_DEFINED
#endif

#ifndef __MDSPAN_TESTS_DISPATCH_DEFINED
template<class LAMBDA>
void dispatch(LAMBDA&& f) {
  (LAMBDA&&)f();
}
template<class T>
T* allocate_array(size_t size) {
  T* ptr = nullptr;
  ptr = new T[size];
  return ptr;
}

template<class T>
void free_array(T* ptr) {
  delete [] ptr;
}
#endif
} // namespace
