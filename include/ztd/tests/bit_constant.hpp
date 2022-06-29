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

#pragma once

#ifndef ZTD_IDK_TESTS_BIT_CONSTANT_HPP
#define ZTD_IDK_TESTS_BIT_CONSTANT_HPP

#include <ztd/version.hpp>

#include <ztd/idk/type_traits.hpp>

#include <cstddef>

namespace ztd { namespace tests {

	template <typename T>
	T get_distinct_bit_constant() noexcept {
		constexpr std::size_t N = sizeof(T) * CHAR_BIT;
		if constexpr (N == 8) {
			return static_cast<T>(0x10);
		}
		else if constexpr (N == 16) {
			return static_cast<T>(0x1023);
		}
		else if constexpr (N == 24) {
			return static_cast<T>(0x102345);
		}
		else if constexpr (N == 32) {
			return static_cast<T>(0x10234567);
		}
		else if constexpr (N == 40) {
			return static_cast<T>(0x1023456789);
		}
		else if constexpr (N == 48) {
			return static_cast<T>(0x1023456789AB);
		}
		else if constexpr (N == 56) {
			return static_cast<T>(0x1023456789ABCD);
		}
		else if constexpr (N == 64) {
			return static_cast<T>(0x1023456789ABCDEF);
		}
		else {
			static_assert(ztd::always_false_v<T>, "unusable bit size for the given type");
		}
	}

	template <typename T>
	T get_distinct_bit_constant_reverse() noexcept {
		constexpr std::size_t N = sizeof(T) * CHAR_BIT;
		if constexpr (N == 8) {
			return static_cast<T>(0x10);
		}
		else if constexpr (N == 16) {
			return static_cast<T>(0x2310);
		}
		else if constexpr (N == 24) {
			return static_cast<T>(0x452310);
		}
		else if constexpr (N == 32) {
			return static_cast<T>(0x67452310);
		}
		else if constexpr (N == 40) {
			return static_cast<T>(0x8967452310);
		}
		else if constexpr (N == 48) {
			return static_cast<T>(0xAB8967452310);
		}
		else if constexpr (N == 56) {
			return static_cast<T>(0xCDAB8967452310);
		}
		else if constexpr (N == 64) {
			return static_cast<T>(0xEFCDAB8967452310);
		}
		else {
			static_assert(ztd::always_false_v<T>, "unusable bit size for the given type");
		}
	}

}} // namespace ztd::tests

#endif // ZTD_IDK_TESTS_BIT_CONSTANT_HPP
