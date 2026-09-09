
#include <gtest/gtest.h>
#include <mdspan/mdspan.hpp>
#include <numeric>
#include <cstdlib>

TEST(TestAlignedAccessor, IsSufficientlyAligned) {
  alignas(4) const char dummy_arr[16] = {};
  ASSERT_TRUE(
      Kokkos::is_sufficiently_aligned<1>(&dummy_arr[1]));
  ASSERT_TRUE(
      Kokkos::is_sufficiently_aligned<1>(&dummy_arr[1]));

  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<2>(&dummy_arr[0]));
  ASSERT_TRUE(!Kokkos::is_sufficiently_aligned<2>(&dummy_arr[1]));

  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<4>(&dummy_arr[0]));
  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<4>(&dummy_arr[4]));
  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<4>(&dummy_arr[8]));
  ASSERT_TRUE(!Kokkos::is_sufficiently_aligned<4>(&dummy_arr[1]));
  ASSERT_TRUE(!Kokkos::is_sufficiently_aligned<4>(&dummy_arr[2]));
  ASSERT_TRUE(!Kokkos::is_sufficiently_aligned<4>(&dummy_arr[3]));
}

// These shouldn't be in the global namespace or they may replace the C version
namespace testing
{
  // https://stackoverflow.com/questions/62962839/stdaligned-alloc-missing-from-visual-studio-2019
  void *aligned_alloc(std::size_t alignment, std::size_t size) {
  #ifdef _MSC_VER
    return _aligned_malloc(size, alignment);  // The arguments are reversed apparently :D
  #else
    return std::aligned_alloc(alignment, size);
  #endif
  }

  void aligned_free(void *ptr) {
  #ifdef _MSC_VER
    _aligned_free(ptr);
  #else
    std::free(ptr);
  #endif
  }

  struct different_align_and_size
  {
    different_align_and_size() = default;
    explicit different_align_and_size(int v) : val(static_cast<double>(v)) {}

    int padd;
    double val;

    friend bool operator==(different_align_and_size lhs, different_align_and_size rhs) {
      return lhs.val == rhs.val;
    }

    different_align_and_size &operator++() noexcept {
      ++val;
      return *this;
    }
  };

  static_assert(sizeof(different_align_and_size) != alignof(different_align_and_size));
}

template <typename T, std::size_t ByteAlignment, std::size_t NumElements>
void test_aligned_accessor() {
  using mdspan_type =
      Kokkos::mdspan<T, Kokkos::extents<std::size_t, NumElements>,
                     Kokkos::layout_right,
                     Kokkos::aligned_accessor<T, ByteAlignment>>;
  auto *buff = reinterpret_cast<T *>(
      testing::aligned_alloc(ByteAlignment, NumElements * sizeof(T)));
  std::iota(buff, buff + NumElements, static_cast<T>(0));
  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<ByteAlignment>(buff));

  auto md = mdspan_type(buff);

  for (std::size_t i = 0; i < NumElements; ++i)
    ASSERT_TRUE(md[i] == static_cast<T>(i));

  // Accessor should be convertible to a default one
  auto md2 = Kokkos::mdspan<T, Kokkos::extents<std::size_t, NumElements>>(md);
  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<ByteAlignment>(md2.data_handle()));

  for (std::size_t i = 0; i < NumElements; ++i)
    ASSERT_TRUE(md2[i] == static_cast<T>(i));

  // Get an offset for the submdspan that should be of the correct alignment
  const std::size_t offset = ByteAlignment / sizeof(T);
  static_assert( NumElements > 2 + offset );
  auto md3 = Kokkos::submdspan(md, std::pair{ offset, NumElements - 2 } );
  ASSERT_TRUE(Kokkos::is_sufficiently_aligned<ByteAlignment>(md3.data_handle()));

  for (std::size_t i = 0; i < NumElements - 2 - offset; ++i )
    ASSERT_TRUE(md3[i] == static_cast<T>(i + offset));

  testing::aligned_free(buff);
}

TEST(TestAlignedAccessor, AlignedAccessor) {
  test_aligned_accessor<double, alignof(double), 10>();
  test_aligned_accessor<double, 2 * alignof(double), 10>();
  test_aligned_accessor<double, 4 * alignof(double), 10>();

  test_aligned_accessor<testing::different_align_and_size, alignof(testing::different_align_and_size), 10>();
  test_aligned_accessor<testing::different_align_and_size, 2 * alignof(testing::different_align_and_size), 10>();
  test_aligned_accessor<testing::different_align_and_size, 4 * alignof(testing::different_align_and_size), 10>();
}
