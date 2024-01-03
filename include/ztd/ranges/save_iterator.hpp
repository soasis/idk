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

#pragma once

#ifndef ZTD_RANGES_SAVE_ITERATOR_HPP
#define ZTD_RANGES_SAVE_ITERATOR_HPP

#include <ztd/ranges/version.hpp>

#include <ztd/ranges/range.hpp>
#include <ztd/ranges/iterator.hpp>

#include <ztd/idk/type_traits.hpp>

#include <ztd/prologue.hpp>

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __rng_detail {
		struct __range_iterator_unsaveable_t {
		} constexpr __range_iterator_unsaveable;
	} // namespace __rng_detail

	//////
	/// @addtogroup ztd_ranges_support Support Classes
	///
	/// @{

	//////
	/// @brief Clones an iterator if it is not aan input or output iterator.
	///
	/// @param __it The iterator to save.
	///
	/// @returns Either an implementation-defined object that indicates the save could not be done, or a move/copy of
	/// the given iterator.
	template <typename _It>
	constexpr auto save_iterator(_It&& __it) noexcept {
		if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_It>, __rng_detail::__range_iterator_unsaveable_t>) {
			return __rng_detail::__range_iterator_unsaveable;
		}
		else if constexpr (::ztd::ranges::is_iterator_input_or_output_iterator_exactly_v<
			                   ::ztd::remove_cvref_t<_It>>) {
			return __rng_detail::__range_iterator_unsaveable;
		}
		else {
			return ::std::forward<_It>(__it);
		}
	}

	//////
	/// @brief Clones an iterator if it is not aan input or output iterator.
	///
	/// @param __it An object returned by a previous call to ztd::ranges::save_iterator.
	/// @param __fallback_it The iterator to return if the given iterator is either an input/output iterator or is the
	/// implementation-defined "unsaveable" object.
	///
	/// @returns Either a clone of the `__it` if possible, or if not returns the `__fallback_it`.
	template <typename _It, typename _FallbackIt>
	constexpr auto restore_iterator(_It&& __it, _FallbackIt&& __fallback_it) noexcept {
		if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_It>, __rng_detail::__range_iterator_unsaveable_t>) {
			return ::std::forward<_FallbackIt>(__fallback_it);
		}
		else if constexpr (::ztd::ranges::is_iterator_input_or_output_iterator_exactly_v<
			                   ::ztd::remove_cvref_t<_It>>) {
			return ::std::forward<_FallbackIt>(__fallback_it);
		}
		else {
			return ::std::forward<_It>(__it);
		}
	}

	template <typename _It>
	inline constexpr bool is_iterator_unsaveable_v
		= ::std::is_same_v<__rng_detail::__range_iterator_unsaveable_t, ::ztd::remove_cvref_t<_It>>;

	//////
	/// @}

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges

#include <ztd/epilogue.hpp>

#endif
