// =============================================================================
//
// ztd.idk
// Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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

#include <catch2/catch_all.hpp>

#include <ztd/idk/bit.h>

#include <ztd/idk/size.hpp>
#include <ztd/tests/bit_constant.hpp>
#include <ztd/tests/types.hpp>
#include <ztd/idk/detail/bit.memreverse.impl.h>

#include <random>
#include <vector>
#include <limits>

static auto randomness_seed = std::random_device {}();

static void ztd_idk_basic_run_time_cxx_memreverse8_ushort(
     size_t __n, unsigned short __ptr[ZTD_PTR_EXTENT(__n)]) ZTD_CXX_NOEXCEPT_I_ {
	__ZTDC_MEMREVERSE8_IMPL(unsigned short, __n, __ptr);
}


static void ztd_idk_basic_run_time_cxx_memreverse8_uint(
     size_t __n, unsigned int __ptr[ZTD_PTR_EXTENT(__n)]) ZTD_CXX_NOEXCEPT_I_ {
	__ZTDC_MEMREVERSE8_IMPL(unsigned int, __n, __ptr);
}


static void ztd_idk_basic_run_time_cxx_memreverse8_ulong(
     size_t __n, unsigned long __ptr[ZTD_PTR_EXTENT(__n)]) ZTD_CXX_NOEXCEPT_I_ {
	__ZTDC_MEMREVERSE8_IMPL(unsigned long, __n, __ptr);
}


static void ztd_idk_basic_run_time_cxx_memreverse8_ullong(
     size_t __n, unsigned long long __ptr[ZTD_PTR_EXTENT(__n)]) ZTD_CXX_NOEXCEPT_I_ {
	__ZTDC_MEMREVERSE8_IMPL(unsigned long long, __n, __ptr);
}

#if ZTD_IS_ON(ZTD___UINT128_T)
static void ztd_idk_basic_run_time_cxx_memreverse8_uint128_t(
     size_t __n, __uint128_t __ptr[ZTD_PTR_EXTENT(__n)]) ZTD_CXX_NOEXCEPT_I_ {
	__ZTDC_MEMREVERSE8_IMPL(__uint128_t, __n, __ptr);
}
#endif

#if ZTD_IS_ON(ZTD___UINT256_T)
static void ztd_idk_basic_run_time_cxx_memreverse8_uint256_t(
     size_t __n, __uint256_t __ptr[ZTD_PTR_EXTENT(__n)]) ZTD_CXX_NOEXCEPT_I_ {
	__ZTDC_MEMREVERSE8_IMPL(__uint256_t, __n, __ptr);
}
#endif


TEMPLATE_LIST_TEST_CASE(
     "Ensure that the 8-bit memory reverse algorithm works even if they work over a different base unit that is a "
     "multiple of 8.",
     "[bit][memreverse][N-bit][c]", ztd::tests::unsigned_integer_and_character_types_list) {
	const TestType expected_value         = ztd::tests::get_distinct_bit_constant<TestType>();
	const TestType expected_reverse_value = ztd::tests::get_distinct_bit_constant_reverse<TestType>();

	// this one work for all types, since it's "unsigned char"-based.
	SECTION("unsigned char-based") {
		TestType value = expected_value;
		REQUIRE(value == expected_value); // quick silliness check
		unsigned char value_arr[sizeof(value) / sizeof(unsigned char)];
		std::memcpy(value_arr, &value, sizeof(value));
		ztdc_memreverse8(ztdc_c_array_size(value_arr), value_arr);
		std::memcpy(&value, value_arr, sizeof(value));
		REQUIRE(value == expected_reverse_value);
	}

	if constexpr ((sizeof(TestType) % sizeof(unsigned short)) == 0) {
		// for all types which are a multiple of the size of unsigned short,
		// test the unsigned short-based type, to verify the implementation is correct
		SECTION("unsigned short-based") {
			TestType value = expected_value;
			REQUIRE(value == expected_value); // quick silliness check
			unsigned short value_arr[sizeof(value) / sizeof(unsigned short)];
			std::memcpy(value_arr, &value, sizeof(value));
			ztd_idk_basic_run_time_cxx_memreverse8_ushort(ztdc_c_array_size(value_arr), value_arr);
			std::memcpy(&value, value_arr, sizeof(value));
			REQUIRE(value == expected_reverse_value);
		}
	}

	if constexpr ((sizeof(TestType) % sizeof(unsigned int)) == 0) {
		// for all types which are a multiple of the size of unsigned int,
		// test the unsigned int-based type, to verify the implementation is correct
		SECTION("unsigned int-based") {
			TestType value = expected_value;
			REQUIRE(value == expected_value); // quick silliness check
			unsigned int value_arr[sizeof(value) / sizeof(unsigned int)];
			std::memcpy(value_arr, &value, sizeof(value));
			ztd_idk_basic_run_time_cxx_memreverse8_uint(ztdc_c_array_size(value_arr), value_arr);
			std::memcpy(&value, value_arr, sizeof(value));
			REQUIRE(value == expected_reverse_value);
		}
	}

	if constexpr ((sizeof(TestType) % sizeof(unsigned long)) == 0) {
		// for all types which are a multiple of the size of unsigned long,
		// test the unsigned long-based type, to verify the implementation is correct
		SECTION("unsigned long-based") {
			TestType value = expected_value;
			REQUIRE(value == expected_value); // quick silliness check
			unsigned long value_arr[sizeof(value) / sizeof(unsigned long)];
			std::memcpy(value_arr, &value, sizeof(value));
			ztd_idk_basic_run_time_cxx_memreverse8_ulong(ztdc_c_array_size(value_arr), value_arr);
			std::memcpy(&value, value_arr, sizeof(value));
			REQUIRE(value == expected_reverse_value);
		}
	}

	if constexpr ((sizeof(TestType) % sizeof(unsigned long long)) == 0) {
		// for all types which are a multiple of the size of unsigned long long,
		// test the unsigned long long-based type, to verify the implementation is correct
		SECTION("unsigned long long-based") {
			TestType value = expected_value;
			REQUIRE(value == expected_value); // quick silliness check
			unsigned long long value_arr[sizeof(value) / sizeof(unsigned long long)];
			std::memcpy(value_arr, &value, sizeof(value));
			ztd_idk_basic_run_time_cxx_memreverse8_ullong(ztdc_c_array_size(value_arr), value_arr);
			std::memcpy(&value, value_arr, sizeof(value));
			REQUIRE(value == expected_reverse_value);
		}
	}

#if ZTD_IS_ON(ZTD___UINT128_T)
	if constexpr ((sizeof(TestType) % sizeof(__uint128_t)) == 0) {
		// for all types which are a multiple of the size of __uint128_t,
		// test the __uint128_t-based type, to verify the implementation is correct
		SECTION("__uint128_t-based") {
			TestType value = expected_value;
			REQUIRE(value == expected_value); // quick silliness check
			__uint128_t value_arr[sizeof(value) / sizeof(__uint128_t)];
			std::memcpy(value_arr, &value, sizeof(value));
			ztd_idk_basic_run_time_cxx_memreverse8_uint128_t(ztdc_c_array_size(value_arr), value_arr);
			std::memcpy(&value, value_arr, sizeof(value));
			REQUIRE(value == expected_reverse_value);
		}
	}
#endif

#if ZTD_IS_ON(ZTD___UINT256_T)
	if constexpr ((sizeof(TestType) % sizeof(__uint256_t)) == 0) {
		// for all types which are a multiple of the size of __uint256_t,
		// test the __uint256_t-based type, to verify the implementation is correct
		SECTION("__uint256_t-based") {
			TestType value = expected_value;
			REQUIRE(value == expected_value); // quick silliness check
			__uint256_t value_arr[sizeof(value) / sizeof(__uint256_t)];
			std::memcpy(value_arr, &value, sizeof(value));
			ztd_idk_basic_run_time_cxx_memreverse8_uint256_t(ztdc_c_array_size(value_arr), value_arr);
			std::memcpy(&value, value_arr, sizeof(value));
			REQUIRE(value == expected_reverse_value);
		}
	}
#endif
}
