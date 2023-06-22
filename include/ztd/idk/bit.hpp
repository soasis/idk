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

#ifndef ZTD_IDK_BIT_HPP
#define ZTD_IDK_BIT_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/binary_digits.hpp>
#include <ztd/idk/assume_aligned.hpp>
#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/to_underlying.hpp>

#include <ztd/idk/detail/bit.load_store.h>
#include <ztd/idk/detail/bit.memreverse.h>
#include <ztd/idk/detail/bit.intrinsic.h>

#if ZTD_IS_ON(ZTD_STD_LIBRARY_BIT)
#include <bit>
#endif

#if ZTD_IS_ON(ZTD_COMPILER_VCXX) && ZTD_IS_ON(ZTD_VCXX_INTRIN_H)
#include <intrin.h>
#endif

#include <climits>
#include <limits>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __idk_detail {
		template <typename _Value>
		constexpr auto __to_bit_underlying(_Value __value) noexcept {
			if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Value>, char>) {
				return static_cast<unsigned char>(__value);
			}
			else {
				return ::ztd::any_to_underlying(__value);
			}
		}

		template <typename _Value>
		constexpr unsigned int __basic_count_ones(_Value __value) noexcept {
			if constexpr (binary_digits_v<_Value> <= 128) {
				__value = __value - ((__value >> 1) & (_Value) ~(_Value)0 / 3);
				__value
				     = (__value & (_Value) ~(_Value)0 / 15 * 3) + ((__value >> 2) & (_Value) ~(_Value)0 / 15 * 3);
				__value = (__value + (__value >> 4)) & (_Value) ~(_Value)0 / 255 * 15;
				return static_cast<unsigned int>(
				     static_cast<_Value>(__value * ((_Value) ~(_Value)0 / 255)) >> (sizeof(_Value) - 1) * CHAR_BIT);
			}
			else {
				unsigned int __num = 0;
				for (::std::size_t __bit_index = 0; __bit_index < binary_digits_v<_Value>; ++__bit_index) {
					bool __is_set = (__value & (static_cast<_Value>(1) << __bit_index)) != static_cast<_Value>(0);
					__num += static_cast<unsigned int>(__is_set);
				}
				return __num;
			}
		}

		template <typename _Value>
		constexpr unsigned int __basic_count_leading_zeros(_Value __value) noexcept {
			int __num = 0;
			for (::std::size_t __bit_index = binary_digits_v<_Value>; __bit_index-- > 0;) {
				bool __not_is_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     == static_cast<_Value>(0);
				if (__not_is_set) {
					__num += 1;
				}
				else {
					break;
				}
			}
			return __num;
		}

		template <typename _Value>
		constexpr unsigned int __basic_count_leading_ones(_Value __value) noexcept {
			unsigned int __num = 0;
			for (::std::size_t __bit_index = binary_digits_v<_Value>; __bit_index-- > 0;) {
				bool __is_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     != static_cast<_Value>(0);
				if (__is_set) {
					__num += 1;
				}
				else {
					break;
				}
			}
			return __num;
		}

		template <typename _Value>
		constexpr unsigned int __basic_count_trailing_zeros(_Value __value) noexcept {
			unsigned int __num = 0;
			for (::std::size_t __bit_index = 0; __bit_index < binary_digits_v<_Value>; ++__bit_index) {
				bool __not_is_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     == static_cast<_Value>(0);
				if (__not_is_set) {
					__num += 1;
				}
				else {
					break;
				}
			}
			return __num;
		}

		template <typename _Value>
		constexpr unsigned int __basic_count_trailing_ones(_Value __value) noexcept {
			unsigned int __num = 0;
			for (::std::size_t __bit_index = 0; __bit_index < binary_digits_v<_Value>; ++__bit_index) {
				bool __is_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     != static_cast<_Value>(0);
				if (__is_set) {
					__num += 1;
				}
				else {
					break;
				}
			}
			return __num;
		}

		template <typename _Value>
		constexpr unsigned int __basic_first_trailing_one(_Value __value) noexcept {
			for (::std::size_t __bit_index = 0; __bit_index < binary_digits_v<_Value>; ++__bit_index) {
				bool __is_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     != static_cast<_Value>(0);
				if (__is_set) {
					return static_cast<unsigned int>(__bit_index + 1);
				}
			}
			return 0;
		}

		template <typename _Value>
		constexpr unsigned int __basic_first_trailing_zero(_Value __value) noexcept {
			for (::std::size_t __bit_index = 0; __bit_index < binary_digits_v<_Value>; ++__bit_index) {
				bool __is_not_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     == static_cast<_Value>(0);
				if (__is_not_set) {
					return static_cast<unsigned int>(__bit_index + 1);
				}
			}
			return 0;
		}

		template <typename _Value>
		constexpr unsigned int __basic_first_leading_one(_Value __value) noexcept {
			for (::std::size_t __bit_index = binary_digits_v<_Value>; __bit_index-- > 0;) {
				bool __is_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     != static_cast<_Value>(0);
				if (__is_set) {
					return static_cast<unsigned int>(binary_digits_v<_Value> - __bit_index);
				}
			}
			return 0;
		}

		template <typename _Value>
		constexpr unsigned int __basic_first_leading_zero(_Value __value) noexcept {
			for (::std::size_t __bit_index = binary_digits_v<_Value>; __bit_index-- > 0;) {
				bool __is_not_set = (__value & static_cast<_Value>(static_cast<_Value>(1) << __bit_index))
				     == static_cast<_Value>(0);
				if (__is_not_set) {
					return static_cast<unsigned int>(binary_digits_v<_Value> - __bit_index);
				}
			}
			return 0;
		}
	} // namespace __idk_detail

	//////
	/// @addtogroup ztd_idk_bit_endian Endian Functions
	///
	/// @{
	//////

	//////
	/// @brief Counts the number of ones in a given unsigned integer.
	///
	/// @param[in] __value The input value.
	///
	/// @returns An `unsigned int` (or suitably large unsigned integer type) with the count.
	template <typename _Value>
	constexpr unsigned int count_ones(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::count_ones(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
#if ZTD_IS_ON(ZTD_STD_LIBRARY_BIT)
			return ::std::popcount(__value);
#elif ZTD_IS_ON(ZTD_BUILTIN_POPCOUNT)
			if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned int>) {
				return __builtin_popcountl(__value);
			}
			else if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned long>) {
				return __builtin_popcountl(__value);
			}
			else if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned long long>) {
				return __builtin_popcountll(__value);
			}
			else {
				return ::ztd::__idk_detail::__basic_count_ones(__value);
			}
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX) && ZTD_IS_ON(ZTD_VCXX_INTRIN_H)
			// WARNING
			// THESE INSTRUCTIONS ARE NOT PORTABLE
			// FIXME: REPLACE WITH SOMETHING MORE PORTABLE,
			// TEST CPUID AND FRIENDS FOR THESE FUNCTIONS,
			// ETC.
			if constexpr (binary_digits_v<_Value> <= 16) {
				return static_cast<unsigned int>(__popcnt16(__value));
			}
			else if constexpr (binary_digits_v<_Value> <= 32) {
				return static_cast<unsigned int>(__popcnt(__value));
			}
			else if constexpr (binary_digits_v<_Value> <= 64) {
				return static_cast<unsigned int>(__popcnt64(__value));
			}
			else {
				return ::ztd::__idk_detail::__basic_count_ones(__value);
			}
#else
			return ::ztd::__idk_detail::__basic_count_ones(__value);
#endif // Standard C++20 vs. VC++ vs. Others
		}
	}

	//////
	/// @brief Counts the number of zeros in a given unsigned integer.
	///
	/// @param[in] __value The input value.
	///
	/// @returns an `unsigned int` (or suitably large unsigned integer type) with the count.
	template <typename _Value>
	constexpr unsigned int count_zeros(_Value __value) noexcept {
		return ((sizeof(_Value) * CHAR_BIT) - ::ztd::count_ones(__value));
	}

	template <typename _Value>
	constexpr unsigned int count_leading_zeros(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::count_leading_zeros(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
#if ZTD_IS_ON(ZTD_STD_LIBRARY_BIT)
			return ::std::countl_zero(__value);
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)

#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED) && ZTD_IS_OFF(ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS)
			if (::std::is_constant_evaluated()) {
				return ::ztd::__idk_detail::__basic_count_leading_zeros(__value);
			}
#endif
#if ZTD_IS_ON(ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS)
			if constexpr (binary_digits_v<_Value> <= 32) {
				unsigned long __index;
				auto __scanval = _BitScanReverse(&__index, __value);
				if (__scanval == 0) {
					return binary_digits_v<_Value>;
				}
				return static_cast<unsigned int>(__index);
			}
#if INTPTR_MAX >= INT64_MAX
			else if constexpr (binary_digits_v<_Value> <= 64) {
				unsigned long __index;
				auto __scanval = _BitScanReverse64(&__index, __value);
				if (__scanval == 0) {
					return binary_digits_v<_Value>;
				}
				return static_cast<unsigned int>(__index);
			}
#endif // 64-bit MSVC only
			else {
				return ::ztd::__idk_detail::__basic_count_leading_zeros(__value);
			}
#else
			return ::ztd::__idk_detail::__basic_count_leading_zeros(__value);
#endif // MSVC lacks constexpr bit intrinsics

#else
			if (__value == 0) {
				return static_cast<int>(binary_digits_v<_Value>);
			}
#if ZTD_IS_ON(ZTD_BUILTIN_CLZ)
			if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned int>) {
				return __builtin_clz(__value) - (binary_digits_v<unsigned int> - binary_digits_v<_Value>);
			}
			else if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned long>) {
				return __builtin_clzl(__value) - (binary_digits_v<unsigned long> - binary_digits_v<_Value>);
			}
			else if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned long long>) {
				return __builtin_clzll(__value) - (binary_digits_v<unsigned long long> - binary_digits_v<_Value>);
			}
			else
#endif
			{
				return ::ztd::__idk_detail::__basic_count_leading_zeros(__value);
			}
#endif
		}
	}

	template <typename _Value>
	constexpr unsigned int count_trailing_zeros(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::count_trailing_zeros(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
#if ZTD_IS_ON(ZTD_STD_LIBRARY_BIT)
			return static_cast<unsigned int>(::std::countr_zero(__value));
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED) && ZTD_IS_OFF(ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS)
			if (::std::is_constant_evaluated()) {
				return ::ztd::__idk_detail::__basic_count_trailing_zeros(__value);
			}
			else
#endif
			{
#if ZTD_IS_ON(ZTD_VCXX_INTRIN_H)
				if constexpr (binary_digits_v<_Value> <= 32) {
					unsigned long __index = {};
					auto __scanval        = _BitScanForward(&__index, __value);
					if (__scanval == 0) {
						return binary_digits_v<_Value>;
					}
					return static_cast<unsigned int>(__index);
				}
#if (INTPTR_MAX >= INT64_MAX)
				else if constexpr (binary_digits_v<_Value> <= 64) {
					// _BitScanX64 does not exist in 32-bit
					unsigned long __index = {};
					auto __scanval        = _BitScanForward64(&__index, __value);
					if (__scanval == 0) {
						return binary_digits_v<_Value>;
					}
					return static_cast<unsigned int>(__index);
				}
#endif // 64-bit MSVC only
				else {
					return ::ztd::__idk_detail::__basic_count_trailing_zeros(__value);
				}
#else
				return ::ztd::__idk_detail::__basic_count_trailing_zeros(__value);
#endif // MSVC lacks constexpr
			}
#else
			if (__value == 0) {
				return static_cast<unsigned int>(binary_digits_v<_Value>);
			}
#if ZTD_IS_ON(ZTD_BUILTIN_CTZ)
			if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned int>) {
				return static_cast<unsigned int>(__builtin_ctz(__value));
			}
			else if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned long>) {
				return static_cast<unsigned int>(__builtin_ctzl(__value));
			}
			else if constexpr (binary_digits_v<_Value> <= binary_digits_v<unsigned long long>) {
				return static_cast<unsigned int>(__builtin_ctzll(__value));
			}
			else
#endif
			{
				return ::ztd::__idk_detail::__basic_count_trailing_zeros(__value);
			}
#endif
		}
	}

	//////
	/// @brief Counts the number of leading ones in a given unsigned integer.
	///
	/// @param[in] __value The input value.
	///
	/// @returns an `unsigned int` (or suitably large unsigned integer type) with the count.
	template <typename _Value>
	constexpr unsigned int count_leading_ones(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::count_leading_ones(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::__idk_detail::__basic_count_leading_ones(__value);
		}
	}

	//////
	/// @brief Counts the number of trailing ones in a given unsigned integer.
	///
	/// @param[in] __value The input value.
	///
	/// @returns an `unsigned int` (or suitably large unsigned integer type) with the count.
	template <typename _Value>
	constexpr unsigned int count_trailing_ones(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::count_trailing_ones(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::__idk_detail::__basic_count_trailing_ones(__value);
		}
	}

	//////
	/// @brief Finds the first trailing zero in a given unsigned integer value.
	///
	/// @param[in] __value The input value.
	///
	/// @returns If the bit is not found, returns `0`. Otherwise, returns an `unsigned int` (or suitably large unsigned
	/// integer type) indicating the index of the found bit, **plus one**.
	template <typename _Value>
	constexpr unsigned int first_leading_zero(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::first_leading_zero(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::__idk_detail::__basic_first_leading_zero(__value);
		}
	}

	//////
	/// @brief Finds the first trailing zero in a given unsigned integer value.
	///
	/// @param[in] __value The input value.
	///
	/// @returns If the bit is not found, returns `0`. Otherwise, returns an `unsigned int` (or suitably large unsigned
	/// integer type) indicating the index of the found bit, **plus one**.
	template <typename _Value>
	constexpr unsigned int first_trailing_zero(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::first_trailing_zero(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::__idk_detail::__basic_first_trailing_zero(__value);
		}
	}


	//////
	/// @brief Finds the first leading one in a given unsigned integer value.
	///
	/// @param[in] __value The input value.
	///
	/// @returns If the bit is not found, returns `0`. Otherwise, returns an `unsigned int` (or suitably large unsigned
	/// integer type) indicating the index of the found bit, **plus one**.
	template <typename _Value>
	constexpr unsigned int first_leading_one(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::first_leading_one(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::__idk_detail::__basic_first_leading_one(__value);
		}
	}


	//////
	/// @brief Finds the first trailing one in a given unsigned integer value.
	///
	/// @param[in] __value The input value.
	///
	/// @returns If the bit is not found, returns `0`. Otherwise, returns an `unsigned int` (or suitably large unsigned
	/// integer type) indicating the index of the found bit, **plus one**.
	template <typename _Value>
	constexpr unsigned int first_trailing_one(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::first_trailing_one(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::__idk_detail::__basic_first_trailing_one(__value);
		}
	}

	//////
	/// @brief Performs a cyclical shift left.
	///
	/// @param[in] __value The value to perform the cyclical shift left.
	/// @param[in] __count The rotation value.
	template <typename _Value>
	constexpr unsigned int rotate_left(_Value __value, unsigned int __count) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::rotate_left(::ztd::__idk_detail::__to_bit_underlying(__value), __count);
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			if (__count == 0) {
				return __value;
			}
			const unsigned int __width    = sizeof(__value) * CHAR_BIT;
			const unsigned int __rotation = __count % __width;
			return (__value << __rotation) | (__value >> (__width - __rotation));
		}
	}

	//////
	/// @brief Performs a cyclical shift right.
	///
	/// @param[in] __value The value to perform the cyclical shift right.
	/// @param[in] __count The rotation value.
	template <typename _Value>
	constexpr unsigned int rotate_right(_Value __value, unsigned int __count) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::rotate_left(::ztd::__idk_detail::__to_bit_underlying(__value), __count);
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			if (__count == 0) {
				return __value;
			}
			const unsigned int __width    = sizeof(__value) * CHAR_BIT;
			const unsigned int __rotation = __count % __width;
			return (__value >> __rotation) | (__value << (__width - __rotation));
		}
	}

	//////
	/// @brief Returns whether or not there is a single bit set in this unsigned integer value (this making it a power
	/// of 2).
	///
	/// @param[in] __value The input value.
	template <typename _Value>
	constexpr bool has_single_bit(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::has_single_bit(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			return ::ztd::count_ones(__value) == 1u;
		}
	}

	//////
	/// @brief Returns the number of bits needed to represent the value exactly.
	///
	/// @param[in] __value The input value.
	template <typename _Value>
	constexpr unsigned int bit_width(_Value __value) noexcept {
		using _UValue = ::ztd::remove_cvref_t<_Value>;
		if constexpr (::std::is_enum_v<_UValue> || ::std::is_same_v<char, _UValue>) {
			return ::ztd::has_single_bit(::ztd::__idk_detail::__to_bit_underlying(__value));
		}
		else {
			static_assert(::std::is_unsigned_v<_UValue>, "bit functions only handle unsigned types");
			if (__value == static_cast<_Value>(0)) {
				return static_cast<_Value>(0);
			}
			return ((sizeof(__value) * CHAR_BIT) - ::ztd::count_leading_zeros(__value));
		}
	}

	//////
	/// @brief Returns the value that is the next power of 2.
	///
	/// @param[in] __value The input value.
	///
	/// @returns `1` when the input value is less than or equal to `1`. Otherwise, produces the power of 2 that is
	/// higher than the input value.
	template <typename _Value>
	constexpr auto bit_ceil(_Value __value) noexcept {
		// integer promotion rules means we need to
		// precisely calculate the bit ceiling here >___>
		using _UValue         = ::ztd::remove_cvref_t<_Value>;
		using _PromotedUValue = ::ztd::remove_cvref_t<decltype(+(_Value)0)>;
		if constexpr (::std::is_same_v<_PromotedUValue, _UValue>) {
			if (__value <= static_cast<_Value>(1)) {
				return static_cast<_Value>(1);
			}
			return static_cast<_Value>(1u << (::ztd::bit_width(static_cast<_Value>(__value - 1))));
		}
		else {
			if (__value <= static_cast<_Value>(1)) {
				return static_cast<_Value>(1);
			}
			return static_cast<_Value>(
			     static_cast<_Value>(1u << (::ztd::bit_width(static_cast<_Value>((__value)-1))
			                              + ((sizeof(unsigned int) * CHAR_BIT) - (sizeof(_Value) * CHAR_BIT))))
			     >> ((sizeof(unsigned int) * CHAR_BIT) - (sizeof(_Value) * CHAR_BIT)));
		}
	}


	//////
	/// @brief Returns the value that is the greatest power of 2 that is less than the input value.
	///
	/// @param[in] __value The input value.
	///
	/// @returns `0` when the input value is `0`. Otherwise, produces the greatest power of 2 that is less than the
	/// input value.
	template <typename _Value>
	constexpr auto bit_floor(_Value __value) noexcept {
		if (__value == static_cast<_Value>(0)) {
			return static_cast<_Value>(0);
		}
		else {
			return static_cast<_Value>(static_cast<_Value>(1) << (::ztd::bit_width(__value) - 1));
		}
	}

	//////
	/// @}
	//////

	//////
	/// @addtogroup ztd_idk_bit_endian Endian Functions
	///
	/// @{
	//////

	//////
	/// @brief Reverses each 8-bit byte in a region of memory.
	///
	/// @param[in] __n The number of bytes to reverse.
	/// @param[in] __ptr The pointer whose 8-bit bytes will be reversed.
	///
	/// @remarks Constraints:
	/// - `CHAR_BIT` is a multiple of 8.
	///
	/// Each 8-bit byte is considered according to `0xFF << multiple-of-8`, where `multiple-of-8` is a multiple of in
	/// the range [0, `CHAR_BIT`).
	//////
	constexpr void memreverse8(size_t __ptr_size, unsigned char __ptr[]) noexcept {
		using _TYPE = unsigned char;
		for (size_t __index = 0, __limit = ((__ptr_size * (sizeof(_TYPE) * CHAR_BIT)) / 2); __index < __limit;) {
			const size_t __ptr_index         = __index / (sizeof(_TYPE) * CHAR_BIT);
			const size_t __reverse_ptr_index = __ptr_size - 1 - __ptr_index;
			_TYPE* __p                       = __ptr + __ptr_index;
			_TYPE* __reverse_p               = __ptr + __reverse_ptr_index;
			const _TYPE __b_temp             = *__p;
			const _TYPE __reverse_b_temp     = *__reverse_p;
			*__p                             = 0;
			*__reverse_p                     = 0;
			for (size_t __bit_index = 0, __bit_limit = ((sizeof(_TYPE) * CHAR_BIT)); __bit_index < __bit_limit;
			     __bit_index += 8) {
				const size_t __reverse_bit_index = (sizeof(_TYPE) * CHAR_BIT) - 8 - __bit_index;
				const _TYPE __bit_mask           = ((_TYPE)0xFF) << __bit_index;
				const _TYPE __reverse_bit_mask   = ((_TYPE)0xFF) << __reverse_bit_index;
				*__p |= (((__reverse_b_temp & __reverse_bit_mask) >> __reverse_bit_index) << __bit_index);
				*__reverse_p |= (((__b_temp & __bit_mask) >> __bit_index) << __reverse_bit_index);
				__index += 8;
			}
		}
	}

	//////
	/// @brief Reverses the 8-bits of a given _N_-width integer type.
	///
	/// @param[in] __value The exact-width integer value to be reversed.
	///
	/// @remarks Equivalent to: `memreverse8(sizeof(__value), (unsigned char*)(&__value)); return __value;`.
	//////
	template <typename _Integralish>
	constexpr _Integralish memreverse8(_Integralish __value) noexcept {
		using _UIntegralish       = ::ztd::remove_cvref_t<_Integralish>;
		_UIntegralish* __ptr      = &__value;
		unsigned char* __byte_ptr = static_cast<_UIntegralish*>(__byte_ptr);
		unsigned char* __aligned_byte_ptr
		     = static_cast<unsigned char*>(ZTD_ASSUME_ALIGNED(alignof(_Integralish), __byte_ptr));
		memreverse8(sizeof(__value), __aligned_byte_ptr);
		return __value;
	}


	//////
	/// @brief Stores an 8-bit byte-specific unsigned integer in little endian format in the array pointed to by
	/// `__ptr` by reading from `__value`.
	///
	/// @param[in] __value The value to be stored.
	/// @param[in] __ptr A non-null pointer to the at least `N / CHAR_BIT` elements.
	///
	/// @par Constraints
	/// - `CHAR_BIT` is a multiple if 8.
	/// - _N_ is a multiple of 8.
	///
	/// @remarks Only stores _N_ bits, as if by performing `__value = __value & (UINTN_MAX)` first. Each 8-bit byte is
	/// considered according to `0xFF << multiple-of-8`, where `multiple-of-8` is a multiple of in the range [0,
	/// `CHAR_BIT`).
	template <typename _Integralish>
	constexpr void store8_le(_Integralish __value, unsigned char __ptr[]) noexcept {
		for (::std::size_t __index = 0; __index < sizeof(_Integralish); ++__index) {
			__ptr[__index] = static_cast<unsigned char>((__value >> (__index * CHAR_BIT)) & UCHAR_MAX);
		}
	}

	//////
	/// @brief Stores an 8-bit byte-specific unsigned integer in big endian format in the array pointed to by `__ptr`
	/// by reading from `__value`.
	///
	/// @param[in] __value The value to be stored.
	/// @param[in] __ptr A non-null pointer to the at least `N / CHAR_BIT` elements.
	///
	/// @par Constraints
	/// - `CHAR_BIT` is a multiple if 8.
	/// - _N_ is a multiple of 8.
	///
	/// @remarks Only stores _N_ bits, as if by performing `__value = __value & (UINTN_MAX)` first. Each 8-bit byte is
	/// considered according to `0xFF << multiple-of-8`, where `multiple-of-8` is a multiple of in the range [0,
	/// `CHAR_BIT`).
	template <typename _Integralish>
	constexpr void store8_be(_Integralish __value, unsigned char __ptr[]) noexcept {
		for (::std::size_t __index = sizeof(_Integralish), __ptr_index = 0; __index-- > 0; ++__ptr_index) {
			__ptr[__ptr_index] = static_cast<unsigned char>((__value >> (__index * CHAR_BIT)) & UCHAR_MAX);
		}
	}

	//////
	/// @brief Loads an 8-bit byte-specific unsigned integer in little endian format in the array pointed to by `__ptr`
	/// by reading from `__value`.
	///
	/// @param[in] __ptr A non-null pointer to the at least `N / CHAR_BIT` elements.
	///
	/// @par Constraints
	/// - `CHAR_BIT` is a multiple if 8.
	/// - _N_ is a multiple of 8.
	///
	/// @remarks Only loads _N_ bits and leaves the rest at 0. Each 8-bit byte is considered according to `0xFF <<
	/// multiple-of-8`, where `multiple-of-8` is a multiple of in the range [0, `CHAR_BIT`).
	template <typename _Integralish>
	constexpr _Integralish load8_le(const unsigned char __ptr[]) noexcept {
		_Integralish __value = {};
		for (::std::size_t __index = 0; __index < sizeof(_Integralish); ++__index) {
			__value
			     |= static_cast<_Integralish>((static_cast<_Integralish>(__ptr[__index]) << (__index * CHAR_BIT)));
		}
		return __value;
	}

	//////
	/// @brief Loads an 8-bit byte-specific unsigned integer in big endian format in the array pointed to by `__ptr` by
	/// reading from `__value`.
	///
	/// @param[in] __ptr A non-null pointer to the at least `N / CHAR_BIT` elements.
	///
	/// @par Constraints
	/// - `CHAR_BIT` is a multiple if 8.
	/// - _N_ is a multiple of 8.
	///
	/// @remarks Only loads _N_ bits and leaves the rest at 0. Each 8-bit byte is considered according to `0xFF <<
	/// multiple-of-8`, where `multiple-of-8` is a multiple of in the range [0, `CHAR_BIT`).
	template <typename _Integralish>
	constexpr _Integralish load8_be(const unsigned char __ptr[]) noexcept {
		_Integralish __value = {};
		for (::std::size_t __index = sizeof(_Integralish), __ptr_index = 0; __index-- > 0; ++__ptr_index) {
			__value |= static_cast<_Integralish>(
			     (static_cast<_Integralish>(__ptr[__ptr_index]) << (__index * CHAR_BIT)));
		}
		return __value;
	}

	//////
	/// @copydoc store8_le
	///
	/// @par Precondition
	/// The input pointer `__ptr` has an alignment suitable to be treated as an integral type of width _N_.
	template <typename _Integralish>
	constexpr void store8_aligned_le(_Integralish __value, unsigned char __ptr[]) noexcept {
		::ztd::store8_le(__value, ZTD_ASSUME_ALIGNED(alignof(_Integralish), __ptr));
	}

	//////
	/// @copydoc store8_be
	///
	/// @par Precondition
	/// The input pointer `__ptr` has an alignment suitable to be treated as an integral type of width _N_.
	template <typename _Integralish>
	constexpr void store8_aligned_be(_Integralish __value, unsigned char __ptr[]) noexcept {
		::ztd::store8_be(__value, ZTD_ASSUME_ALIGNED(alignof(_Integralish), __ptr));
	}

	//////
	/// @copydoc load8_le
	///
	/// @par Precondition
	/// The input pointer `__ptr` has an alignment suitable to be treated as an integral type of width _N_.
	template <typename _Integralish>
	constexpr _Integralish load8_aligned_le(const unsigned char __ptr[]) noexcept {
		return ::ztd::load8_le<_Integralish>(__ptr);
	}

	//////
	/// @copydoc load8_be
	///
	/// @par Precondition
	/// The input pointer `__ptr` has an alignment suitable to be treated as an integral type of width _N_.
	template <typename _Integralish>
	constexpr _Integralish load8_aligned_be(const unsigned char __ptr[]) noexcept {
		return ::ztd::load8_be<_Integralish>(__ptr);
	}

	//////
	/// @}
	//////

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

// Include it, only after we have all the other declarations done and closed out
#include <ztd/idk/bit.h>

#endif
