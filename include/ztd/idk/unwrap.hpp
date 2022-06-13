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

#ifndef ZTD_IDK_UNWRAP_HPP
#define ZTD_IDK_UNWRAP_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/to_address.hpp>
#include <ztd/idk/contiguous_iterator_tag.hpp>

#include <utility>
#include <iterator>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __idk_detail {
		template <typename _Type>
		using __is_unwrappable_value_test = decltype(unwrap_value(::std::declval<_Type>()));

		template <typename _Type>
		using __is_unwrappable_iter_value_test = decltype(unwrap_iterator_value(::std::declval<_Type>()));
	} // namespace __idk_detail

	//////
	/// @brief Test whether a type can have `unwrap_value(...)` called on it.
	template <typename _Type>
	inline constexpr bool is_unwrappable_value_v
	     = ztd::is_detected_v<__idk_detail::__is_unwrappable_value_test, _Type>;

	//////
	/// @brief Test whether a type can have `unwrap_iterator_value(...)` called on it.
	template <typename _Type>
	inline constexpr bool is_unwrappable_iterator_value_v
	     = ztd::is_detected_v<__idk_detail::__is_unwrappable_iter_value_test, _Type>;

	//////
	/// @brief Unwraps a value, if possible. Otherwise, simply forwards the input value through.
	template <typename _Type>
	constexpr decltype(auto) unwrap(_Type&& __value) noexcept {
		if constexpr (is_unwrappable_value_v<_Type>) {
			return unwrap_value(::std::forward<_Type>(__value));
		}
		else {
			return ::std::forward<_Type>(__value);
		}
	}

	//////
	/// @brief Unwraps either an iterator, or unwraps the value and returns its address, or forwards teh input value
	/// through.
	///
	/// @returns The unwrapped iterator.
	//////
	template <typename _Type>
	constexpr decltype(auto) unwrap_iterator(_Type&& __value) noexcept {
		if constexpr (is_unwrappable_iterator_value_v<_Type>) {
			return unwrap_iterator_value(::std::forward<_Type>(__value));
		}
		else if constexpr (is_unwrappable_value_v<_Type>) {
			return ::std::addressof(unwrap_value(*::std::forward<_Type>(__value)));
		}
		else {
			return ::std::forward<_Type>(__value);
		}
	}

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#endif // ZTD_IDK_UNWRAP_HPP
