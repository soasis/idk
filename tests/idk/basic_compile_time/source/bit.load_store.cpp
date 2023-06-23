// =============================================================================
//
// ztd.idk
// Copyright © 2022-2023 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.idk licenses may use this file in
// accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License") for non-commercial use; you may not use this
// file except in compliance with the License. You may obtain a copy of the
// License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================ //

#include <ztd/idk/bit.hpp>

#include <ztd/tests/bit_constant.hpp>
#include <ztd/ranges/algorithm.hpp>

#include <array>
#include <cstdint>

namespace {
	template <typename TestType>
	constexpr bool test_compile_time_load_store_uN() noexcept {
		constexpr const TestType expected_value = ztd::tests::get_distinct_bit_constant<TestType>();
		std::array<unsigned char, sizeof(TestType)> data_le {};
		std::array<unsigned char, sizeof(TestType)> data_be {};

		ztd::store8_le(expected_value, data_le.data());
		ztd::store8_be(expected_value, data_be.data());

		const TestType value_le = ztd::load8_le<TestType>(data_le.data());
		const TestType value_be = ztd::load8_be<TestType>(data_be.data());

		if (value_le != expected_value) {
			return false;
		}
		if (value_be != expected_value) {
			return false;
		}

		return true;
	}
} // namespace

static_assert(test_compile_time_load_store_uN<unsigned char>(), "test_compile_time_load_store_uN<unsigned char>()");
static_assert(test_compile_time_load_store_uN<unsigned short>(), "test_compile_time_load_store_uN<unsigned short>()");
static_assert(test_compile_time_load_store_uN<unsigned int>(), "test_compile_time_load_store_uN<unsigned int>()");
static_assert(test_compile_time_load_store_uN<unsigned long>(), "test_compile_time_load_store_uN<unsigned long>()");
static_assert(
     test_compile_time_load_store_uN<unsigned long long>(), "test_compile_time_load_store_uN<unsigned long long>()");
#if ZTD_IS_ON(ZTD_NATIVE_CHAR8_T)
static_assert(test_compile_time_load_store_uN<char8_t>(), "test_compile_time_load_store_uN<char8_t>()");
#endif
static_assert(test_compile_time_load_store_uN<char16_t>(), "test_compile_time_load_store_uN<char16_t>()");
static_assert(test_compile_time_load_store_uN<char32_t>(), "test_compile_time_load_store_uN<char32_t>()");
static_assert(test_compile_time_load_store_uN<wchar_t>(), "test_compile_time_load_store_uN<wchar_t>()");
