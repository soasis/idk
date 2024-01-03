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

#ifndef ZTD_IDK_BINARY_DIGITS_HPP
#define ZTD_IDK_BINARY_DIGITS_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/type_traits.hpp>

#include <cstddef>
#include <cstdint>
#include <limits>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __idk_detail {

		template <typename _Type, typename = void>
		class __un_binary_digits { };

		template <typename _Type>
		class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_integral_v<_Type>>>
		: public ::std::integral_constant<::std::size_t, ::std::numeric_limits<_Type>::digits> { };

		template <typename _Type>
		class __un_binary_digits<_Type, ::std::enable_if_t<::std::is_enum_v<_Type>>>
		: public ::std::integral_constant<::std::size_t,
		       ::std::numeric_limits<::std::underlying_type_t<_Type>>::digits> { };

		template <typename, typename = void>
		class __un_bit_mask_type { };

		template <typename _Type>
		class __un_bit_mask_type<_Type, std::enable_if_t<std::is_integral_v<_Type> || std::is_enum_v<_Type>>> {
		public:
			using type = _Type;
		};

	} // namespace __idk_detail

	template <typename _Type>
	class binary_digits
	: public __idk_detail::__un_binary_digits<::std::remove_cv_t<::std::remove_reference_t<_Type>>> { };

	template <typename _Type>
	inline constexpr auto binary_digits_v = binary_digits<_Type>::value;

	template <typename _Type>
	inline constexpr auto max_binary_index_v = binary_digits_v<_Type> - 1;

	template <typename _Type, typename _SizeType>
	constexpr _SizeType bit_to_element_size(_SizeType __bit_size) noexcept {
		return static_cast<_SizeType>((__bit_size + max_binary_index_v<_Type>) / binary_digits_v<_Type>);
	}

	template <typename _Type, typename _SizeType>
	constexpr _SizeType element_to_bit_size(_SizeType __element_size) noexcept {
		return static_cast<_SizeType>(__element_size * binary_digits_v<_Type>);
	}

	template <typename _Type>
	class bit_mask_type
	: public __idk_detail::__un_bit_mask_type<::std::remove_cv_t<::std::remove_reference_t<_Type>>> { };

	template <typename _Type>
	using bit_mask_type_t = typename bit_mask_type<_Type>::type;

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#endif // ITSY_BITSY_BINARY_DIGITS_HPP
