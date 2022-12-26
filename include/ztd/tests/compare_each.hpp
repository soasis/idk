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

#pragma once

#ifndef ZTD_IDK_TESTS_RESULT_COMPARE_HPP
#define ZTD_IDK_TESTS_RESULT_COMPARE_HPP

#include <catch2/catch_all.hpp>

namespace ztd { namespace tests {

	template <typename Result, typename Expected>
	void compare_each(Result& result, Expected& expected) {
		std::size_t result_size   = result.size();
		std::size_t expected_size = expected.size();
		for (std::size_t index = 0; index < expected_size; ++index) {
			REQUIRE(result_size > index);
			const auto& result_c   = result[index];
			const auto& expected_c = expected[index];
			if (result_c != expected_c) {
				REQUIRE(result_c == expected_c);
			}
			REQUIRE(result_c == expected_c);
		}
		REQUIRE(result_size == expected_size);
		REQUIRE(result == expected);
	}

}} // namespace ztd::tests

#endif
