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

#ifndef ZTD_IDK_DETAIL_ENCODING_TABLES_UTILITIES_HPP
#define ZTD_IDK_DETAIL_ENCODING_TABLES_UTILITIES_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/encoding_types.tables.h>

#include <cstddef>
#include <optional>
#include <iterator>

#include <ztd/prologue.hpp>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __idk_detail {
		using __lookup_index_to_code_point_function = ::std::optional<ztd_char32_t>(::std::size_t);
		using __lookup_code_point_to_index_function = ::std::optional<::std::size_t>(ztd_char32_t);

		inline constexpr bool less_than_index_target(
		     const ztd_encoding_index16_code_point_t& __value, ztd_encoding_index16_t __target) noexcept {
			return __value[0] < __target;
		}
	} // namespace __idk_detail

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#include <ztd/epilogue.hpp>

#endif
