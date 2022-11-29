// =============================================================================
//
// ztd.idk
// Copyright © 2022 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================ //

#include "c_test.h"

#include <ztd/idk/bit.h>

#include <ztd/tests/bit_constant.h>

#define SELECT_BIT_REVERSE_FUNCTION(TEST_TYPE_SIZE) ztdc_memreverse8u##TEST_TYPE_SIZE
#define MAKE_TEMPLATE_TEST_CASE(TEST_TYPE, TEST_TYPE_SIZE)                                                             \
	TEST_CASE(                                                                                                        \
	     "Ensure that the 8-bit memory reverse algorithm works on appropriately-sized variables for \"" #TEST_TYPE    \
	     "\".",                                                                                                       \
	     "[bit][memreverse][8-bit][small][" #TEST_TYPE "]") {                                                         \
		const TEST_TYPE expected_value         = ZTD_TESTS_DISTINCT_BIT_CONSTANT(TEST_TYPE, TEST_TYPE_SIZE);         \
		const TEST_TYPE expected_reverse_value = ZTD_TESTS_DISTINCT_BIT_CONSTANT_REVERSE(TEST_TYPE, TEST_TYPE_SIZE); \
                                                                                                                       \
		SECTION("raw memory reverse") {                                                                              \
			TEST_TYPE value = expected_value;                                                                       \
			REQUIRE(value == expected_value);                                                                       \
			ztdc_memreverse8(sizeof(value), (unsigned char*)(&value));                                              \
			REQUIRE(value == expected_reverse_value);                                                               \
		}                                                                                                            \
		SECTION("value-based memory reverse") {                                                                      \
			TEST_TYPE value = expected_value;                                                                       \
			REQUIRE(value == expected_value);                                                                       \
			TEST_TYPE reverse_value = SELECT_BIT_REVERSE_FUNCTION(TEST_TYPE_SIZE)(value);                           \
			REQUIRE(value == expected_value);                                                                       \
			REQUIRE(reverse_value == expected_reverse_value);                                                       \
		}                                                                                                            \
	}                                                                                                                 \
	ztd_static_assert(1, "")

extern int bit_memreverse_tests(void) {
	BEGIN_TEST("bit.memreverse");
#if CHAR_BIT == 8
	MAKE_TEMPLATE_TEST_CASE(unsigned char, 8);
	MAKE_TEMPLATE_TEST_CASE(unsigned short, 16);
	MAKE_TEMPLATE_TEST_CASE(unsigned int, 32);
	MAKE_TEMPLATE_TEST_CASE(unsigned long, 32);
	MAKE_TEMPLATE_TEST_CASE(unsigned long long, 64);

	TEST_CASE("Ensure that hte 8-bit memory reverse algorithm works on large memory region.",
	     "[bit][memreverse][8-bit][large]") {
		SECTION("with canonical implementation") {
		}
	}
#endif
	END_TEST();
}


#undef MAKE_TEMPLATE_TEST_CASE
#undef SELECT_BIT_REVERSE_FUNCTION
