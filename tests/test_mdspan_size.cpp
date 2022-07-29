/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include <experimental/mdspan>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <vector>

#include <gtest/gtest.h>

namespace {

namespace stdex = std::experimental;

template<class Extents>
std::size_t product_of_extents(const Extents& e)
{
  size_t prod = 1;
  for(std::size_t r = 0; r < e.rank(); ++r) {
    prod *= static_cast<std::size_t>(e.extent(r));
  }
  return prod;
}

template<class Extents>
void test_mdspan_size(std::vector<char>& storage, Extents&& e)
{
  const std::size_t min_storage_size = product_of_extents(e);
  if(storage.size() < min_storage_size) {
    storage.resize(min_storage_size);
  }
  using extents_type = std::remove_cv_t<std::remove_reference_t<Extents>>;
  stdex::mdspan<char, extents_type> m(storage.data(), std::forward<Extents>(e));

  static_assert(std::is_same<decltype(m.size()), std::size_t>::value,
		"The return type of mdspan::size() must be size_t.");

  // m.size() must not overflow, as long as the product of extents
  // is representable as a value of type size_t.
  ASSERT_EQ( min_storage_size, m.size() );
}

TEST(TestMdspan, MdspanSizeReturnTypeAndPrecondition)
{
  std::vector<char> storage;

  static_assert(std::numeric_limits<std::int8_t>::max() == 127, "max int8_t != 127");
  test_mdspan_size(storage, stdex::extents<std::int8_t, 12, 11>{}); // 12 * 11 == 132

  static_assert(std::numeric_limits<std::uint8_t>::max() == 255, "max uint8_t != 255");
  test_mdspan_size(storage, stdex::extents<std::uint8_t, 16, 17>{}); // 16 * 17 == 272
}

} // namespace (anonymous)
