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

#ifndef ZTD_IDK_SHIFT_JIS_TABLES_HPP
#define ZTD_IDK_SHIFT_JIS_TABLES_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/shift_jis.tables.h>
#include <ztd/ranges/algorithm.hpp>
#include <ztd/ranges/adl.hpp>

#include <cstddef>
#include <optional>
#include <iterator>
#include <algorithm>

#include <ztd/prologue.hpp>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	inline constexpr bool less_than_index_target(
	     const ztd_sjis_index_codepoint_t& __value, ztd_sjis_index_t __target) noexcept {
		return __value[0] < __target;
	}

	inline constexpr ::std::optional<ztd_char32_t> shift_jis_index_to_code_point(
	     ::std::size_t __lookup_index_pointer) noexcept {
		const ztd_sjis_index_t __lookup_index = static_cast<ztd_sjis_index_t>(__lookup_index_pointer);
		auto __it_and_last = ::ztd::ranges::lower_bound(::ztd::ranges::cbegin(ztd_shift_jis_index_code_point_map),
		     ::ztd::ranges::cend(ztd_shift_jis_index_code_point_map), __lookup_index, &::ztd::less_than_index_target);
		if (__it_and_last.current == __it_and_last.last) {
			return ::std::nullopt;
		}
		const ztd_sjis_index_codepoint_t& __index_and_codepoint = *__it_and_last.current;
		if (__index_and_codepoint[0] != __lookup_index) {
			return ::std::nullopt;
		}
		return static_cast<ztd_char32_t>(__index_and_codepoint[1]);
	}

	inline constexpr ::std::optional<::std::size_t> shift_jis_code_point_to_index(ztd_char32_t __code_point) noexcept {
		auto __predicate = [&__code_point](const ztd_sjis_index_codepoint_t& __value) {
			return __code_point == __value[1] && !(__value[0] > 8272 && __value[0] < 8835);
		};
		auto __it_and_last = ::ztd::ranges::find_if(::ztd::ranges::cbegin(ztd_shift_jis_index_code_point_map),
		     ::ztd::ranges::cend(ztd_shift_jis_index_code_point_map), __predicate);
		if (__it_and_last.current == __it_and_last.last) {
			return std::nullopt;
		}
		const ztd_sjis_index_codepoint_t& __index_and_codepoint = *__it_and_last.current;
		return static_cast<::std::size_t>(__index_and_codepoint[0]);
	}

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#include <ztd/epilogue.hpp>

#endif
