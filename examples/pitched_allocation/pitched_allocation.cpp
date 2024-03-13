#include <experimental/mdspan>

#if defined(__cpp_lib_bit_cast)
#  include <bit>
#endif
#include <cassert>
#include <cstring>
#include <cstdint>
#include <memory>
#include <type_traits>

// This example shows how to deal with "pitched" allocations.
// These are multidimensional array allocations
// that may have extra padding bytes at the end of each "row"
// (the contiguous mode of the array).
// As a result, each element's size might not evenly divide
// the number of bytes per "row" of the contiguous dimension.
// However, each element in the row is stored in aligned fashion,
// so that we can use reinterpret_cast instead of memcpy
// to access the elements.
//
// The commented-out example below uses cudaMallocPitch
// to allocate a 4 x 5 two-dimensional array of T,
// where sizeof(T) is 12.  Each row (the contiguous dimension) has
// 64 bytes.  The last 4 bytes of each row are padding that do not
// participate in an element.
//


// void* ptr = nullptr;
// size_t pitch = 0;
//
// constexpr size_t num_cols = 5;
// constexpr size_t num_rows = 4;
//
// cudaMallocPitch(&ptr, &pitch, sizeof(T) * num_cols, num_rows);
// extents<int, num_rows, num_cols> exts{};
// layout_stride::mapping mapping{exts, std::array{pitch, sizeof(T)}};
// mdspan m{reinterpret_cast<char*>(ptr), mapping, aligned_byte_accessor<T>{}};

namespace stdex = std::experimental;

// This is the element type.  "tbs" stands for Twelve-Byte Struct.
// In this example, the struct includes a mixture of float and int,
// just to make aliasing more interesting.
struct tbs {
  float f0 = 0.0f;
  std::int32_t i = 0;
  float f1 = 0.0f;
};

// Use of the proxy reference types is only required
// if access to each element is not aligned.
// That should not be the case here.

class const_tbs_proxy;
class nonconst_tbs_proxy;

template<class T, class Enable = void>
class const_proxy {
private:
  const char* p_ = nullptr;

  friend class const_tbs_proxy;
  constexpr const_proxy(const char* p) noexcept
    : p_(p)
  {}

public:
  // Not constexpr because of reinterpret_cast or memcpy
  operator T () const noexcept {
    // We can't do the commented-out reinterpret_cast
    // in Standard C++, because p_ might not have correct
    // alignment to point to a T.
    //
    //return *reinterpret_cast<const T*>(p_);

    T f;
    std::memcpy(&f, p_, sizeof(T));
    return f;
  }
};

#if defined(__cpp_lib_bit_cast)
template<class T>
class const_proxy<T, std::enable_if_t<std::is_trivially_copyable_v<T>>> {
private:
  struct bitcastable {
    char data[sizeof(T)];
  };
  const bitcastable* p_ = nullptr;

  // reinterpret_cast means this can't be constexpr.
  // However, the conversion operator can be.
  friend class const_tbs_proxy;
  const_proxy(const char* p) noexcept
    : p_(reinterpret_cast<const bitcastable*>(p))
  {}

public:
  constexpr operator T() const noexcept {
    return std::bit_cast<T>(*p_);
  }
};
#endif // __cpp_lib_bit_cast

template<class T, class Enable = void>
class nonconst_proxy {
private:
  char* p_ = nullptr;

  friend class nonconst_tbs_proxy;
  constexpr nonconst_proxy(char* p) noexcept
    : p_(p)
  {}

public:
  // Not constexpr because of memcpy
  nonconst_proxy& operator=(const T& f) noexcept {
    std::memcpy(p_, &f, sizeof(T));
    return *this;
  }

  // Not constexpr because of memcpy
  operator T () const noexcept {
    T f;
    std::memcpy(&f, p_, sizeof(T));
    return f;
  }
};

#if defined(__cpp_lib_bit_cast)
template<class T>
class nonconst_proxy<T, std::enable_if_t<std::is_trivially_copyable_v<T>>> {
private:
  struct bitcastable {
    char data[sizeof(T)];
  };
  bitcastable* p_ = nullptr;

  // reinterpret_cast means this can't be constexpr.
  // However, the conversion operator can be.
  friend class nonconst_tbs_proxy;
  nonconst_proxy(char* p) noexcept
    : p_(reinterpret_cast<bitcastable*>(p))
  {}

public:
  nonconst_proxy& operator=(const T& f) noexcept {
    std::memcpy(p_, &f, sizeof(T));
    return *this;
  }

  constexpr operator T () const noexcept {
    return std::bit_cast<T>(*p_);
  }
};
#endif // __cpp_lib_bit_cast

class nonconst_tbs_proxy {
private:
  char* p_ = nullptr;

public:
  nonconst_tbs_proxy(char* p) noexcept
    : p_(p), f0(p), i(p + sizeof(float)), f1(p + sizeof(float) + sizeof(int))
  {}

  nonconst_tbs_proxy& operator=(const tbs& s) noexcept {
    this->f0 = s.f0;
    this->i = s.i;
    this->f1 = s.f1;
    return *this;
  }

  operator tbs() const noexcept {
    return {float(f0), std::int32_t(i), float(f1)};
  };

  nonconst_proxy<float> f0;
  nonconst_proxy<std::int32_t> i;
  nonconst_proxy<float> f1;
};

// tbs is a struct, so users want to access its fields
// with the usual dot notation.  The two proxy reference types,
// const_tbs_proxy and nonconst_tbs_proxy, preserve this behavior.

class const_tbs_proxy {
private:
  const char* p_ = nullptr;

public:
  const_tbs_proxy(const char* p) noexcept
    : p_(p), f0(p), i(p + sizeof(float)), f1(p + sizeof(float) + sizeof(int))
  {}

  operator tbs() const noexcept {
    return {float(f0), std::int32_t(i), float(f1)};
  };

  const_proxy<float> f0;
  const_proxy<std::int32_t> i;
  const_proxy<float> f1;
};


struct const_tbs_accessor {
  using offset_policy = const_tbs_accessor;

  using data_handle_type = const char*;
  using element_type = const tbs;
  // In the const reference case, we can use
  // either const_tbs_proxy or tbs (a value).
  //using reference = const_tbs_proxy;
  using reference = tbs;

  constexpr const_tbs_accessor() noexcept = default;

  // Not constexpr because of memcpy
  reference
  access(data_handle_type p, size_t i) const noexcept {
    //return {p + i * sizeof(tbs)}; // for const_tbs_proxy
    tbs t;
    std::memcpy(&t, p + i * sizeof(tbs), sizeof(tbs));
    return t;
  }

  constexpr typename offset_policy::data_handle_type
  offset(data_handle_type p, size_t i) const noexcept {
    return p + i * sizeof(tbs);
  }
};

struct nonconst_tbs_accessor {
  using offset_policy = nonconst_tbs_accessor;

  using data_handle_type = char*;
  using element_type = tbs;
  using reference = nonconst_tbs_proxy;

  constexpr nonconst_tbs_accessor() noexcept = default;

  reference
  access(data_handle_type p, size_t i) const noexcept {
    return {p + i * sizeof(tbs)};
  }

  constexpr typename offset_policy::data_handle_type
  offset(data_handle_type p, size_t i) const noexcept {
    return p + i * sizeof(tbs);
  }
};

int main() {
  constexpr std::size_t num_elements = 5;

  std::array<char, num_elements * sizeof(tbs)> data;
  auto* ptr = reinterpret_cast<tbs*>(data.data());

  std::uninitialized_fill_n(ptr, num_elements, tbs{1.0, 2, 3.0});

  for(std::size_t k = 0; k < num_elements; ++k) {
    assert(ptr[k].f0 == 1.0);
    assert(ptr[k].i == 2);
    assert(ptr[k].f1 == 3.0);
  }

  stdex::mdspan<const tbs, stdex::extents<int, num_elements>,
    stdex::layout_right, const_tbs_accessor> m{data.data()};
  for (std::size_t k = 0; k < num_elements; ++k) {
    assert(m[k].f0 == 1.0f);
    assert(m[k].i == 2);
    assert(m[k].f1 == 3.0f);
  }

  stdex::mdspan<tbs, stdex::extents<int, num_elements>,
    stdex::layout_right, nonconst_tbs_accessor> m_nc{data.data()};
  for (std::size_t k = 0; k < num_elements; ++k) {
    m_nc[k].f0 = 4.0f;
    m_nc[k].i = 5;
    m_nc[k].f1 = 6.0f;
  }

  for (std::size_t k = 0; k < num_elements; ++k) {
    // Be careful using auto with proxy references.  It's fine here,
    // because we're not letting the proxy reference escape the scope.
    auto m_k = m[k];
    assert(m_k.f0 == 4.0f);
    assert(m_k.i == 5);
    assert(m_k.f1 == 6.0f);
  }

  for (std::size_t k = 0; k < num_elements; ++k) {
    auto m_nc_k = m_nc[k];
    m_nc_k.f0 = 7.0f;
    m_nc_k.i = 8;
    m_nc_k.f1 = 9.0f;
  }

  for (std::size_t k = 0; k < num_elements; ++k) {
    auto m_k = m[k];
    assert(m_k.f0 == 7.0f);
    assert(m_k.i == 8);
    assert(m_k.f1 == 9.0f);
  }

  return 0;
}
