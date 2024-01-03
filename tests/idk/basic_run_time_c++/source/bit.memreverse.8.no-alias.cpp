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

#include <ztd/idk/bit.hpp>

#include <ztd/tests/bit_constant.hpp>
#include <ztd/tests/types.hpp>
#include <ztd/idk/detail/bit.memreverse.impl.h>

#include <random>
#include <vector>
#include <limits>

static auto randomness_seed = std::random_device {}();

TEMPLATE_LIST_TEST_CASE(
     "Ensure that the 8-bit memory reverse algorithm works even if they work over a different base unit that is a "
     "multiple of 8.",
     "[bit][memreverse][N-bit][cpp]", ztd::tests::unsigned_integer_and_character_types_list) {
	const TestType expected_value         = ztd::tests::get_distinct_bit_constant<TestType>();
	const TestType expected_reverse_value = ztd::tests::get_distinct_bit_constant_reverse<TestType>();

	// this one work for all types, since it's "unsigned char"-based.
	SECTION("unsigned char-based") {
		TestType value = expected_value;
		REQUIRE(value == expected_value); // quick silliness check
		ztd::memreverse8(sizeof(value), reinterpret_cast<unsigned char*>(&value));
		REQUIRE(value == expected_reverse_value);
	}
}
