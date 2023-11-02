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

#ifndef ZTD_IDK_IS_ARRAY_HPP
#define ZTD_IDK_IS_ARRAY_HPP

#include <ztd/idk/version.hpp>

#include <type_traits>

#include <ztd/prologue.hpp>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	//////
	/// @brief Whether or not the given type is exactly a `std::array`.
	template <typename _Ty>
	class is_std_array : public ::std::false_type { };

	//////
	/// @brief Whether or not the given type is exactly a `std::array`.
	template <typename _Ty, ::std::size_t _N>
	class is_std_array<::std::array<_Ty, _N>> : public ::std::true_type { };

	//////
	/// @brief Whether or not the given type is exactly a `std::array`.
	template <typename _Ty>
	inline constexpr bool is_std_array_v = is_std_array<_Ty>::value;

	//////
	/// @brief Whether or not the given type is exactly a `std::array`.
	template <typename _Ty>
	inline constexpr bool is_std_or_c_array_v = ::std::is_array_v<_Ty> || is_std_array_v<_Ty>;

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#include <ztd/epilogue.hpp>

#endif
