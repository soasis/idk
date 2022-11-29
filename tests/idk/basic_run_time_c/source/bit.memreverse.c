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

#define SELECT_BIT_REVERSE_FUNCTION_(TEST_TYPE, TEST_TYPE_SIZE) ((void (*)(void))(ztdc_memreverse8u##TEST_TYPE_SIZE))
#define SELECT_BIT_REVERSE_FUNCTION(TEST_TYPE)                                             \
	((sizeof(TEST_TYPE) * CHAR_BIT == 8)                                                  \
	          ? SELECT_BIT_REVERSE_FUNCTION_(TEST_TYPE, 8)                                \
	          : ((sizeof(TEST_TYPE) * CHAR_BIT == 16)                                     \
	                    ? SELECT_BIT_REVERSE_FUNCTION_(TEST_TYPE, 16)                     \
	                    : ((sizeof(TEST_TYPE) * CHAR_BIT == 32)                           \
	                              ? SELECT_BIT_REVERSE_FUNCTION_(TEST_TYPE, 32)           \
	                              : ((sizeof(TEST_TYPE) * CHAR_BIT == 64)                 \
	                                        ? SELECT_BIT_REVERSE_FUNCTION_(TEST_TYPE, 64) \
	                                        : SELECT_BIT_REVERSE_FUNCTION_(TEST_TYPE, 64)))))

#define SELECT_BIT_CONSTANT_(TEST_TYPE, TEST_TYPE_SIZE) ZTD_TESTS_DISTINCT_BIT_CONSTANT(TEST_TYPE, TEST_TYPE_SIZE)
#define SELECT_BIT_CONSTANT(TEST_TYPE)                                                                           \
	((sizeof(TEST_TYPE) * CHAR_BIT == 8)                                                                        \
	          ? SELECT_BIT_CONSTANT_(TEST_TYPE, 8)                                                              \
	          : ((sizeof(TEST_TYPE) * CHAR_BIT == 16)                                                           \
	                    ? SELECT_BIT_CONSTANT_(TEST_TYPE, 16)                                                   \
	                    : ((sizeof(TEST_TYPE) * CHAR_BIT == 32)                                                 \
	                              ? SELECT_BIT_CONSTANT_(TEST_TYPE, 32)                                         \
	                              : ((sizeof(TEST_TYPE) * CHAR_BIT == 64) ? SELECT_BIT_CONSTANT_(TEST_TYPE, 64) \
	                                                                      : SELECT_BIT_CONSTANT_(TEST_TYPE, 64)))))

#define SELECT_REVERSE_BIT_CONSTANT_(TEST_TYPE, TEST_TYPE_SIZE) \
	ZTD_TESTS_DISTINCT_BIT_CONSTANT_REVERSE(TEST_TYPE, TEST_TYPE_SIZE)
#define SELECT_REVERSE_BIT_CONSTANT(TEST_TYPE)                                             \
	((sizeof(TEST_TYPE) * CHAR_BIT == 8)                                                  \
	          ? SELECT_REVERSE_BIT_CONSTANT_(TEST_TYPE, 8)                                \
	          : ((sizeof(TEST_TYPE) * CHAR_BIT == 16)                                     \
	                    ? SELECT_REVERSE_BIT_CONSTANT_(TEST_TYPE, 16)                     \
	                    : ((sizeof(TEST_TYPE) * CHAR_BIT == 32)                           \
	                              ? SELECT_REVERSE_BIT_CONSTANT_(TEST_TYPE, 32)           \
	                              : ((sizeof(TEST_TYPE) * CHAR_BIT == 64)                 \
	                                        ? SELECT_REVERSE_BIT_CONSTANT_(TEST_TYPE, 64) \
	                                        : SELECT_REVERSE_BIT_CONSTANT_(TEST_TYPE, 64)))))

#define GENERATE_TEST_CASE(TEST_TYPE)                                                                                \
	TEST_CASE(                                                                                                      \
	     "Ensure that the 8-bit memory reverse algorithm works on appropriately-sized variables for \"" #TEST_TYPE  \
	     "\".",                                                                                                     \
	     "[bit][memreverse][8-bit][small][" #TEST_TYPE "]") {                                                       \
		const TEST_TYPE expected_value         = SELECT_BIT_CONSTANT(TEST_TYPE);                                   \
		const TEST_TYPE expected_reverse_value = SELECT_REVERSE_BIT_CONSTANT(TEST_TYPE);                           \
                                                                                                                     \
		SECTION("raw memory reverse") {                                                                            \
			TEST_TYPE value = expected_value;                                                                     \
			REQUIRE(value == expected_value);                                                                     \
			ztdc_memreverse8(sizeof(value), (unsigned char*)(&value));                                            \
			REQUIRE(value == expected_reverse_value);                                                             \
		}                                                                                                          \
		SECTION("value-based memory reverse") {                                                                    \
			TEST_TYPE value = expected_value;                                                                     \
			REQUIRE(value == expected_value);                                                                     \
			TEST_TYPE reverse_value = ((TEST_TYPE(*)(TEST_TYPE))(SELECT_BIT_REVERSE_FUNCTION(TEST_TYPE)))(value); \
			REQUIRE(value == expected_value);                                                                     \
			REQUIRE(reverse_value == expected_reverse_value);                                                     \
		}                                                                                                          \
	}                                                                                                               \
	ztd_static_assert(1, "")

extern int bit_memreverse_tests(void) {
	BEGIN_TEST("bit.memreverse");
#if CHAR_BIT == 8
	GENERATE_TEST_CASE(unsigned char);
	GENERATE_TEST_CASE(unsigned short);
	GENERATE_TEST_CASE(unsigned int);
	GENERATE_TEST_CASE(unsigned long);
	GENERATE_TEST_CASE(unsigned long long);

	TEST_CASE("Ensure that hte 8-bit memory reverse algorithm works on large memory region.",
	     "[bit][memreverse][8-bit][large]") {
		SECTION("with canonical implementation") {
		}
	}
#endif
	END_TEST();
}


#undef GENERATE_TEST_CASE
#undef SELECT_REVERSE_BIT_CONSTANT_
#undef SELECT_REVERSE_BIT_CONSTANT
#undef SELECT_BIT_CONSTANT_
#undef SELECT_BIT_CONSTANT
