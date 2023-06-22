
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

#ifndef ZTD_IDK_DETAIL_BIT_INTRINSIC_GENERIC_H
#define ZTD_IDK_DETAIL_BIT_INTRINSIC_GENERIC_H

#include <ztd/idk/version.h>

#include <ztd/idk/detail/bit.intrinsic.h>

#if ZTD_IS_ON(ZTD_C)

#if ZTD_IS_ON(ZTD_BUILTIN_POPCOUNT)
#define _ZTDC_COUNT_ONES_I_(...)              \
	((unsigned int)_Generic((__VA_ARGS__),   \
	     char: __builtin_popcount,           \
	     unsigned char: __builtin_popcount,  \
	     unsigned short: __builtin_popcount, \
	     unsigned int: __builtin_popcount,   \
	     unsigned long: __builtin_popcountl, \
	     unsigned long long: __builtin_popcountll)(__VA_ARGS__))
#else
#define _ZTDC_COUNT_ONES_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                     \
	     char: ztdc_count_ones_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_count_ones_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_count_ones_us(__VA_ARGS__),        \
	     unsigned int: ztdc_count_ones_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_count_ones_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_count_ones_ull(__VA_ARGS__)))
#endif

#define _ZTDC_COUNT_ZEROS_I_(...) ((sizeof(__VA_ARGS__) * CHAR_BIT) - ztdc_count_ones(__VA_ARGS__))

#define _ZTDC_COUNT_LEADING_ZEROS_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                              \
	     char: ztdc_count_leading_zeros_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_count_leading_zeros_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_count_leading_zeros_us(__VA_ARGS__),        \
	     unsigned int: ztdc_count_leading_zeros_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_count_leading_zeros_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_count_leading_zeros_ull(__VA_ARGS__)))

#define _ZTDC_COUNT_TRAILING_ZEROS_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                               \
	     char: ztdc_count_trailing_zeros_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_count_trailing_zeros_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_count_trailing_zeros_us(__VA_ARGS__),        \
	     unsigned int: ztdc_count_trailing_zeros_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_count_trailing_zeros_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_count_trailing_zeros_ull(__VA_ARGS__)))

#define _ZTDC_COUNT_LEADING_ONES_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                             \
	     char: ztdc_count_leading_ones_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_count_leading_ones_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_count_leading_ones_us(__VA_ARGS__),        \
	     unsigned int: ztdc_count_leading_ones_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_count_leading_ones_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_count_leading_ones_ull(__VA_ARGS__)))

#define _ZTDC_COUNT_TRAILING_ONES_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                              \
	     char: ztdc_count_trailing_ones_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_count_trailing_ones_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_count_trailing_ones_us(__VA_ARGS__),        \
	     unsigned int: ztdc_count_trailing_ones_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_count_trailing_ones_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_count_trailing_ones_ull(__VA_ARGS__)))

#define _ZTDC_FIRST_LEADING_ZERO_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                             \
	     char: ztdc_first_leading_zero_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_first_leading_zero_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_first_leading_zero_us(__VA_ARGS__),        \
	     unsigned int: ztdc_first_leading_zero_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_first_leading_zero_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_first_leading_zero_ull(__VA_ARGS__)))

#define _ZTDC_FIRST_TRAILING_ZERO_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                              \
	     char: ztdc_first_trailing_zero_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_first_trailing_zero_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_first_trailing_zero_us(__VA_ARGS__),        \
	     unsigned int: ztdc_first_trailing_zero_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_first_trailing_zero_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_first_trailing_zero_ull(__VA_ARGS__)))

#define _ZTDC_FIRST_LEADING_ONE_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                            \
	     char: ztdc_first_leading_one_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_first_leading_one_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_first_leading_one_us(__VA_ARGS__),        \
	     unsigned int: ztdc_first_leading_one_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_first_leading_one_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_first_leading_one_ull(__VA_ARGS__)))

#define _ZTDC_FIRST_TRAILING_ONE_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                             \
	     char: ztdc_first_trailing_one_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_first_trailing_one_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_first_trailing_one_us(__VA_ARGS__),        \
	     unsigned int: ztdc_first_trailing_one_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_first_trailing_one_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_first_trailing_one_ull(__VA_ARGS__)))

#define _ZTDC_ROTATE_LEFT_I_(_VALUE, ...)                                  \
	(_Generic((_VALUE),                                                   \
	     char: ztdc_rotate_left_uc((unsigned char)(_VALUE), __VA_ARGS__), \
	     unsigned char: ztdc_rotate_left_uc(_VALUE, __VA_ARGS__),         \
	     unsigned short: ztdc_rotate_left_us(_VALUE, __VA_ARGS__),        \
	     unsigned int: ztdc_rotate_left_ui(_VALUE, __VA_ARGS__),          \
	     unsigned long: ztdc_rotate_left_ul(_VALUE, __VA_ARGS__),         \
	     unsigned long long: ztdc_rotate_left_ull(_VALUE, __VA_ARGS__)))

#define _ZTDC_ROTATE_RIGHT_I_(_VALUE, ...)                                  \
	(_Generic((_VALUE),                                                    \
	     char: ztdc_rotate_right_uc((unsigned char)(_VALUE), __VA_ARGS__), \
	     unsigned char: ztdc_rotate_right_uc(_VALUE, __VA_ARGS__),         \
	     unsigned short: ztdc_rotate_right_us(_VALUE, __VA_ARGS__),        \
	     unsigned int: ztdc_rotate_right_ui(_VALUE, __VA_ARGS__),          \
	     unsigned long: ztdc_rotate_right_ul(_VALUE, __VA_ARGS__),         \
	     unsigned long long: ztdc_rotate_right_ull(_VALUE, __VA_ARGS__)))

#define _ZTDC_HAS_SINGLE_BIT_I_(...)                                  \
	(_Generic((__VA_ARGS__),                                         \
	     char: ztdc_has_single_bit_uc((unsigned char)(__VA_ARGS__)), \
	     unsigned char: ztdc_has_single_bit_uc(__VA_ARGS__),         \
	     unsigned short: ztdc_has_single_bit_us(__VA_ARGS__),        \
	     unsigned int: ztdc_has_single_bit_ui(__VA_ARGS__),          \
	     unsigned long: ztdc_has_single_bit_ul(__VA_ARGS__),         \
	     unsigned long long: ztdc_has_single_bit_ull(__VA_ARGS__)))

#define _ZTDC_BIT_WIDTH_I_(...)                                                                            \
	_Generic((__VA_ARGS__),                                                                               \
	     char: ((sizeof(unsigned char) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))),            \
	     unsigned char: ((sizeof(unsigned char) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))),   \
	     unsigned short: ((sizeof(unsigned short) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))), \
	     unsigned int: ((sizeof(unsigned int) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))),     \
	     unsigned long: ((sizeof(unsigned long) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))),   \
	     unsigned long long: ((sizeof(unsigned long long) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))))

#define _ZTDC_BIT_CEIL_I_(...)                           \
	_Generic((__VA_ARGS__),                             \
	     char: ztdc_bit_ceil_uc(__VA_ARGS__),           \
	     unsigned char: ztdc_bit_ceil_uc(__VA_ARGS__),  \
	     unsigned short: ztdc_bit_ceil_us(__VA_ARGS__), \
	     unsigned int: ztdc_bit_ceil_ui(__VA_ARGS__),   \
	     unsigned long: ztdc_bit_ceil_ul(__VA_ARGS__),  \
	     unsigned long long: ztdc_bit_ceil_ull(__VA_ARGS__))

#define _ZTDC_BIT_FLOOR_I_(...)                           \
	_Generic((__VA_ARGS__),                              \
	     char: ztdc_bit_floor_uc(__VA_ARGS__),           \
	     unsigned char: ztdc_bit_floor_uc(__VA_ARGS__),  \
	     unsigned short: ztdc_bit_floor_us(__VA_ARGS__), \
	     unsigned int: ztdc_bit_floor_ui(__VA_ARGS__),   \
	     unsigned long: ztdc_bit_floor_ul(__VA_ARGS__),  \
	     unsigned long long: ztdc_bit_floor_ull(__VA_ARGS__))

#else

#include <ztd/idk/bit.hpp>

#define _ZTDC_COUNT_ONES_I_(...) ::ztd::count_ones(__VA_ARGS__)

#define _ZTDC_COUNT_ZEROS_I_(...) ::ztd::count_zeros(__VA_ARGS__)

#define _ZTDC_COUNT_LEADING_ZEROS_I_(...) ::ztd::count_leading_zeros(__VA_ARGS__)

#define _ZTDC_COUNT_TRAILING_ZEROS_I_(...) ::ztd::count_trailing_zeros(__VA_ARGS__)

#define _ZTDC_COUNT_LEADING_ONES_I_(...) ::ztd::count_leading_ones(__VA_ARGS__)

#define _ZTDC_COUNT_TRAILING_ONES_I_(...) ::ztd::count_trailing_ones(__VA_ARGS__)

#define _ZTDC_FIRST_LEADING_ZERO_I_(...) ::ztd::first_leading_zero(__VA_ARGS__)

#define _ZTDC_FIRST_TRAILING_ZERO_I_(...) ::ztd::first_trailing_zero(__VA_ARGS__)

#define _ZTDC_FIRST_LEADING_ONE_I_(...) ::ztd::first_leading_one(__VA_ARGS__)

#define _ZTDC_FIRST_TRAILING_ONE_I_(...) ::ztd::first_trailing_one(__VA_ARGS__)

#define _ZTDC_ROTATE_LEFT_I_(...) ::ztd::rotate_left(__VA_ARGS__)

#define _ZTDC_ROTATE_RIGHT_I_(...) ::ztd::rotate_right(__VA_ARGS__)

#define _ZTDC_HAS_SINGLE_BIT_I_(...) ::ztd::single_bit(__VA_ARGS__)

#define _ZTDC_BIT_WIDTH_I_(...) ::ztd::bit_width(__VA_ARGS__)

#define _ZTDC_BIT_CEIL_I_(...) ::ztd::bit_ceil(__VA_ARGS__)

#define _ZTDC_BIT_FLOOR_I_(...) ::ztd::bit_floor(__VA_ARGS__)

#endif // C vs. C++ only

#endif
