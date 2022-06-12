// =============================================================================
// ztd::fixed_container
//
// Written 2019 - 2022 by ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
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
