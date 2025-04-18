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

#ifndef ZTD_RANGES_SAVE_RANGE_HPP
#define ZTD_RANGES_SAVE_RANGE_HPP

#include <ztd/ranges/version.hpp>

#include <ztd/ranges/save_iterator.hpp>
#include <ztd/ranges/range.hpp>
#include <ztd/ranges/iterator.hpp>

#include <ztd/idk/type_traits.hpp>

#include <ztd/prologue.hpp>

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	//////
	/// @addtogroup ztd_ranges_support Support Classes
	///
	/// @{

	//////
	/// @brief Clones a range if it is not aan input or output range.
	///
	/// @param __range The range to save.
	///
	/// @returns Either an implementation-defined object that indicates the save could not be done, or a move/copy of
	/// the given range.
	template <typename _Range>
	constexpr auto save_range(_Range&& __range) noexcept {
		if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Range>, __rng_detail::__range_iterator_unsaveable_t>) {
			return __rng_detail::__range_iterator_unsaveable;
		}
		else if constexpr (::ztd::ranges::is_range_input_or_output_range_exactly_v<::ztd::remove_cvref_t<_Range>>) {
			return __rng_detail::__range_iterator_unsaveable;
		}
		else {
			return ::std::forward<_Range>(__range);
		}
	}

	//////
	/// @brief Clones a range if it is not aan input or output range.
	///
	/// @param __range An object returned by a previous call to ztd::ranges::save_range.
	/// @param __fallback_range The range to return if the given range is either an input/output range or is the
	/// implementation-defined "unsaveable" object.
	///
	/// @returns Either a clone of the `__range` if possible, or if not returns the `__fallback_range`.
	template <typename _Range, typename _FallbackRange>
	constexpr auto restore_range(_Range&& __range, _FallbackRange&& __fallback_range) noexcept {
		if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Range>, __rng_detail::__range_iterator_unsaveable_t>) {
			return ::std::forward<_FallbackRange>(__fallback_range);
		}
		else if constexpr (::ztd::ranges::is_range_input_or_output_range_exactly_v<::ztd::remove_cvref_t<_Range>>) {
			return ::std::forward<_FallbackRange>(__fallback_range);
		}
		else {
			return ::std::forward<_Range>(__range);
		}
	}

	template <typename _It>
	inline constexpr bool is_range_unsaveable_v = is_iterator_unsaveable_v<::ztd::remove_cvref_t<_It>>;

	//////
	/// @}

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges

#include <ztd/epilogue.hpp>

#endif
