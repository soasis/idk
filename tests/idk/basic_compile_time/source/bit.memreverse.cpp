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
	constexpr bool test_compile_time_memreverse8_uN() noexcept {
		constexpr const TestType expected_value         = ztd::tests::get_distinct_bit_constant<TestType>();
		constexpr const TestType expected_reverse_value = ztd::tests::get_distinct_bit_constant_reverse<TestType>();
		static_assert(ztd::memreverse8(expected_value) == expected_reverse_value);
		static_assert(ztd::memreverse8(expected_reverse_value) == expected_value);
		return true;
	}

	constexpr bool test_compile_time_memreverse8() noexcept {
		constexpr const std::array<unsigned char, 8> data { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
		constexpr const std::array<unsigned char, 8> reverse_data { 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00 };

		auto target = data;
		if (!ztd::ranges::equal(target, data)) {
			return false;
		}
		ztd::memreverse8(target.size(), target.data());
		if (!ztd::ranges::equal(target, reverse_data)) {
			return false;
		}

		return true;
	}
} // namespace

static_assert(test_compile_time_memreverse8(), "test_compile_time_memreverse8");
static_assert(test_compile_time_memreverse8_uN<unsigned char>(), "test_compile_time_memreverse8_uN<unsigned char>()");
static_assert(test_compile_time_memreverse8_uN<unsigned short>(), "test_compile_time_memreverse8_uN<unsigned short>()");
static_assert(test_compile_time_memreverse8_uN<unsigned int>(), "test_compile_time_memreverse8_uN<unsigned int>()");
static_assert(test_compile_time_memreverse8_uN<unsigned long>(), "test_compile_time_memreverse8_uN<unsigned long>()");
static_assert(
     test_compile_time_memreverse8_uN<unsigned long long>(), "test_compile_time_memreverse8_uN<unsigned long long>()");
#if ZTD_IS_ON(ZTD_NATIVE_CHAR8_T)
static_assert(test_compile_time_memreverse8_uN<char8_t>(), "test_compile_time_memreverse8_uN<char8_t>()");
#endif
static_assert(test_compile_time_memreverse8_uN<char16_t>(), "test_compile_time_memreverse8_uN<char16_t>()");
static_assert(test_compile_time_memreverse8_uN<char32_t>(), "test_compile_time_memreverse8_uN<char32_t>()");
#if ZTD_IS_ON(ZTD_WCHAR_T_IS_UNSIGNED)
static_assert(test_compile_time_memreverse8_uN<wchar_t>(), "test_compile_time_memreverse8_uN<wchar_t>()");
#endif
