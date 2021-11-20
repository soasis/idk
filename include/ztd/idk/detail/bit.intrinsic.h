// =============================================================================
//
// ztd.idk
// Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
// ============================================================================>

#pragma once

#ifndef ZTD_IDK_DETAIL_BIT_INTRINSIC_H
#define ZTD_IDK_DETAIL_BIT_INTRINSIC_H

#include <ztd/idk/version.h>

#include <ztd/idk/static_assert.h>

#if ZTD_IS_ON(ZTD_C_I_)
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include <cstddef>
#include <climits>
#include <cstdint>
#endif

ZTD_EXTERN_C_OPEN_I_

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_onesuc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_onesus(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_onesui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_onesul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_onesull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_zerosuc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_zerosus(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_zerosui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_zerosul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_zerosull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_zerosuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_zerosus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_zerosui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_zerosul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_zerosull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_onesuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_onesus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_onesui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_onesul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_leading_onesull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_zerosuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_zerosus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_zerosui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_zerosul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_zerosull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_onesuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_onesus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_onesui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_onesul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_count_trailing_onesull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_oneuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_oneus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_oneui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_oneul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_oneull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_oneuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_oneus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_oneui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_oneul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_oneull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_zerouc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_zerous(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_zeroui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_zeroul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_leading_zeroull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_zerouc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_zerous(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_zeroui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_zeroul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ int ztdc_first_trailing_zeroull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned char ztdc_rotate_leftuc(
     unsigned char value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned short ztdc_rotate_leftus(
     unsigned short value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned int ztdc_rotate_leftui(
     unsigned int value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long ztdc_rotate_leftul(
     unsigned long value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long long ztdc_rotate_leftull(
     unsigned long long value, int __count) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned char ztdc_rotate_rightuc(
     unsigned char value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned short ztdc_rotate_rightus(
     unsigned short value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned int ztdc_rotate_rightui(
     unsigned int value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long ztdc_rotate_rightul(
     unsigned long value, int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long long ztdc_rotate_rightull(
     unsigned long long value, int __count) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_has_single_bituc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_has_single_bitus(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_has_single_bitui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_has_single_bitul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_has_single_bitull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned char ztdc_bit_flooruc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned short ztdc_bit_floorus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned int ztdc_bit_floorui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long ztdc_bit_floorul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long long ztdc_bit_floorull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned char ztdc_bit_ceiluc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned short ztdc_bit_ceilus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned int ztdc_bit_ceilui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long ztdc_bit_ceilul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long long ztdc_bit_ceilull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned char ztdc_bit_widthuc(
     unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned short ztdc_bit_widthus(
     unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned int ztdc_bit_widthui(
     unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long ztdc_bit_widthul(
     unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_IDK_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ unsigned long long ztdc_bit_widthull(
     unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_EXTERN_C_CLOSE_I_

#if ZTD_IS_ON(ZTD_C_I_)

#define _ZTDC_COUNT_ONES_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                              \
	          : ztdc_count_onesuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_count_onesuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_count_onesus(__VA_ARGS__), unsigned int                   \
	          : ztdc_count_onesui(__VA_ARGS__), unsigned long                  \
	          : ztdc_count_onesul(__VA_ARGS__), unsigned long long             \
	          : ztdc_count_onesull(__VA_ARGS__)))

#define _ZTDC_COUNT_ZEROS_I_(...) ((sizeof(__VA_ARGS__) * CHAR_BIT) - ztdc_count_ones(__VA_ARGS__))

#define _ZTDC_COUNT_LEADING_ZEROS_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                       \
	          : ztdc_count_leading_zerosuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_count_leading_zerosuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_count_leading_zerosus(__VA_ARGS__), unsigned int                   \
	          : ztdc_count_leading_zerosui(__VA_ARGS__), unsigned long                  \
	          : ztdc_count_leading_zerosul(__VA_ARGS__), unsigned long long             \
	          : ztdc_count_leading_zerosull(__VA_ARGS__)))

#define _ZTDC_COUNT_TRAILING_ZEROS_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                        \
	          : ztdc_count_trailing_zerosuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_count_trailing_zerosuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_count_trailing_zerosus(__VA_ARGS__), unsigned int                   \
	          : ztdc_count_trailing_zerosui(__VA_ARGS__), unsigned long                  \
	          : ztdc_count_trailing_zerosul(__VA_ARGS__), unsigned long long             \
	          : ztdc_count_trailing_zerosull(__VA_ARGS__)))

#define _ZTDC_COUNT_LEADING_ONES_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                      \
	          : ztdc_count_leading_onesuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_count_leading_onesuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_count_leading_onesus(__VA_ARGS__), unsigned int                   \
	          : ztdc_count_leading_onesui(__VA_ARGS__), unsigned long                  \
	          : ztdc_count_leading_onesul(__VA_ARGS__), unsigned long long             \
	          : ztdc_count_leading_onesull(__VA_ARGS__)))

#define _ZTDC_COUNT_TRAILING_ONES_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                       \
	          : ztdc_count_trailing_onesuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_count_trailing_onesuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_count_trailing_onesus(__VA_ARGS__), unsigned int                   \
	          : ztdc_count_trailing_onesui(__VA_ARGS__), unsigned long                  \
	          : ztdc_count_trailing_onesul(__VA_ARGS__), unsigned long long             \
	          : ztdc_count_trailing_onesull(__VA_ARGS__)))

#define _ZTDC_FIRST_LEADING_ZERO_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                      \
	          : ztdc_first_leading_zerouc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_first_leading_zerouc(__VA_ARGS__), unsigned short                 \
	          : ztdc_first_leading_zerous(__VA_ARGS__), unsigned int                   \
	          : ztdc_first_leading_zeroui(__VA_ARGS__), unsigned long                  \
	          : ztdc_first_leading_zeroul(__VA_ARGS__), unsigned long long             \
	          : ztdc_first_leading_zeroull(__VA_ARGS__)))

#define _ZTDC_FIRST_TRAILING_ZERO_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                       \
	          : ztdc_first_trailing_zerouc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_first_trailing_zerouc(__VA_ARGS__), unsigned short                 \
	          : ztdc_first_trailing_zerous(__VA_ARGS__), unsigned int                   \
	          : ztdc_first_trailing_zeroui(__VA_ARGS__), unsigned long                  \
	          : ztdc_first_trailing_zeroul(__VA_ARGS__), unsigned long long             \
	          : ztdc_first_trailing_zeroull(__VA_ARGS__)))

#define _ZTDC_FIRST_LEADING_ONE_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                     \
	          : ztdc_first_leading_oneuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_first_leading_oneuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_first_leading_oneus(__VA_ARGS__), unsigned int                   \
	          : ztdc_first_leading_oneui(__VA_ARGS__), unsigned long                  \
	          : ztdc_first_leading_oneul(__VA_ARGS__), unsigned long long             \
	          : ztdc_first_leading_oneull(__VA_ARGS__)))

#define _ZTDC_FIRST_TRAILING_ONE_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                      \
	          : ztdc_first_trailing_oneuc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_first_trailing_oneuc(__VA_ARGS__), unsigned short                 \
	          : ztdc_first_trailing_oneus(__VA_ARGS__), unsigned int                   \
	          : ztdc_first_trailing_oneui(__VA_ARGS__), unsigned long                  \
	          : ztdc_first_trailing_oneul(__VA_ARGS__), unsigned long long             \
	          : ztdc_first_trailing_oneull(__VA_ARGS__)))

#define _ZTDC_ROTATE_LEFT_I_(_VALUE, ...)                                                \
	(_Generic((_VALUE), char                                                            \
	          : ztdc_rotate_leftuc((unsigned char)(_VALUE), __VA_ARGS__), unsigned char \
	          : ztdc_rotate_leftuc(_VALUE, __VA_ARGS__), unsigned short                 \
	          : ztdc_rotate_leftus(_VALUE, __VA_ARGS__), unsigned int                   \
	          : ztdc_rotate_leftui(_VALUE, __VA_ARGS__), unsigned long                  \
	          : ztdc_rotate_leftul(_VALUE, __VA_ARGS__), unsigned long long             \
	          : ztdc_rotate_leftull(_VALUE, __VA_ARGS__)))

#define _ZTDC_ROTATE_RIGHT_I_(_VALUE, ...)                                                \
	(_Generic((_VALUE), char                                                             \
	          : ztdc_rotate_rightuc((unsigned char)(_VALUE), __VA_ARGS__), unsigned char \
	          : ztdc_rotate_rightuc(_VALUE, __VA_ARGS__), unsigned short                 \
	          : ztdc_rotate_rightus(_VALUE, __VA_ARGS__), unsigned int                   \
	          : ztdc_rotate_rightui(_VALUE, __VA_ARGS__), unsigned long                  \
	          : ztdc_rotate_rightul(_VALUE, __VA_ARGS__), unsigned long long             \
	          : ztdc_rotate_rightull(_VALUE, __VA_ARGS__)))

#define _ZTDC_HAS_SINGLE_BIT_I_(...)                                                \
	(_Generic((__VA_ARGS__), char                                                  \
	          : ztdc_has_single_bituc((unsigned char)(__VA_ARGS__)), unsigned char \
	          : ztdc_has_single_bituc(__VA_ARGS__), unsigned short                 \
	          : ztdc_has_single_bitus(__VA_ARGS__), unsigned int                   \
	          : ztdc_has_single_bitui(__VA_ARGS__), unsigned long                  \
	          : ztdc_has_single_bitul(__VA_ARGS__), unsigned long long             \
	          : ztdc_has_single_bitull(__VA_ARGS__)))

#define _ZTDC_BIT_WIDTH_I_(...)                                                                                    \
	_Generic((__VA_ARGS__), char                                                                                  \
	         : ((sizeof(unsigned char) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))), unsigned char      \
	         : ((sizeof(unsigned char) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))), unsigned short     \
	         : ((sizeof(unsigned short) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))), unsigned int      \
	         : ((sizeof(unsigned int) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))), unsigned long       \
	         : ((sizeof(unsigned long) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))), unsigned long long \
	         : ((sizeof(unsigned long long) * CHAR_BIT) - ztdc_count_leading_zeros((__VA_ARGS__))))

#define _ZTDC_BIT_CEIL_I_(...)                                   \
	_Generic((__VA_ARGS__), char                                \
	         : ztdc_bit_ceiluc(__VA_ARGS__), unsigned char      \
	         : ztdc_bit_ceiluc(__VA_ARGS__), unsigned short     \
	         : ztdc_bit_ceilus(__VA_ARGS__), unsigned int       \
	         : ztdc_bit_ceilui(__VA_ARGS__), unsigned long      \
	         : ztdc_bit_ceilul(__VA_ARGS__), unsigned long long \
	         : ztdc_bit_ceilull(__VA_ARGS__))

#define _ZTDC_BIT_FLOOR_I_(...)                                   \
	_Generic((__VA_ARGS__), char                                 \
	         : ztdc_bit_flooruc(__VA_ARGS__), unsigned char      \
	         : ztdc_bit_flooruc(__VA_ARGS__), unsigned short     \
	         : ztdc_bit_floorus(__VA_ARGS__), unsigned int       \
	         : ztdc_bit_floorui(__VA_ARGS__), unsigned long      \
	         : ztdc_bit_floorul(__VA_ARGS__), unsigned long long \
	         : ztdc_bit_floorull(__VA_ARGS__))

#else

#include <ztd/idk/type_traits.hpp>

template <typename _Value>
int _ZTDC_COUNT_ONES_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_count_onesuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_count_onesus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_count_onesui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_count_onesul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_count_onesull(__value);
	}
	else {
		static_assert(::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_count_ones");
	}
}

template <typename _Value>
int _ZTDC_COUNT_ZEROS_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char> ||      // cf-hack
	     ::std::is_same_v<_Value, unsigned short> || ::std::is_same_v<_Value, unsigned int> ||      // cf-hack
	     ::std::is_same_v<_Value, unsigned long> || ::std::is_same_v<_Value, unsigned long long>) { // cf-hack
		return ((sizeof(_Value) * CHAR_BIT) - _ZTDC_COUNT_ONES_I_(__value));
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_count_zeros");
	}
}

template <typename _Value>
int _ZTDC_COUNT_LEADING_ZEROS_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_count_leading_zerosuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_count_leading_zerosus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_count_leading_zerosui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_count_leading_zerosul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_count_leading_zerosull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_count_leading_zeros");
	}
}

template <typename _Value>
int _ZTDC_COUNT_TRAILING_ZEROS_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_count_trailing_zerosuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_count_trailing_zerosus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_count_trailing_zerosui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_count_trailing_zerosul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_count_trailing_zerosull(__value);
	}
	else {
		static_assert(::ztd::always_false_v<_Value>,
		     "Only an unsigned integer type can be given to ztdc_count_trailing_zeros");
	}
}

template <typename _Value>
int _ZTDC_COUNT_LEADING_ONES_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_count_leading_onesuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_count_leading_onesus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_count_leading_onesui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_count_leading_onesul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_count_leading_onesull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_count_leading_ones");
	}
}

template <typename _Value>
int _ZTDC_COUNT_TRAILING_ONES_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_count_trailing_onesuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_count_trailing_onesus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_count_trailing_onesui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_count_trailing_onesul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_count_trailing_onesull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_count_trailing_ones");
	}
}

template <typename _Value>
int _ZTDC_FIRST_LEADING_ZERO_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_first_leading_zerouc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_first_leading_zerous(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_first_leading_zeroui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_first_leading_zeroul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_first_leading_zeroull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_first_leading_zero");
	}
}

template <typename _Value>
int _ZTDC_FIRST_TRAILING_ZERO_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_first_trailing_zerouc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_first_trailing_zerous(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_first_trailing_zeroui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_first_trailing_zeroul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_first_trailing_zeroull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_first_trailing_zero");
	}
}

template <typename _Value>
int _ZTDC_FIRST_LEADING_ONE_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_first_leading_oneuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_first_leading_oneus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_first_leading_oneui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_first_leading_oneul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_first_leading_oneull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_first_leading_one");
	}
}

template <typename _Value>
int _ZTDC_FIRST_TRAILING_ONE_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_first_trailing_oneuc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_first_trailing_oneus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_first_trailing_oneui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_first_trailing_oneul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_first_trailing_oneull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_first_trailing_one");
	}
}

template <typename _Value>
int _ZTDC_ROTATE_LEFT_I_(_Value __value, int __rotation) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_rotate_leftuc(static_cast<unsigned char>(__value), __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_rotate_leftus(__value, __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_rotate_leftui(__value, __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_rotate_leftul(__value, __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_rotate_leftull(__value, __rotation);
	}
	else {
		static_assert(::ztd::always_false_v<_Value>,
		     "Only an unsigned integer type can be given to ztdc_rotate_left as the value");
	}
}

template <typename _Value>
int _ZTDC_ROTATE_RIGHT_I_(_Value __value, int __rotation) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_rotate_rightuc(static_cast<unsigned char>(__value), __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_rotate_rightus(__value, __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_rotate_rightui(__value, __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_rotate_rightul(__value, __rotation);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_rotate_rightull(__value, __rotation);
	}
	else {
		static_assert(::ztd::always_false_v<_Value>,
		     "Only an unsigned integer type can be given to ztdc_rotate_right as the value");
	}
}

template <typename _Value>
int _ZTDC_HAS_SINGLE_BIT_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_has_single_bituc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_has_single_bitus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_has_single_bitui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_has_single_bitul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_has_single_bitull(__value);
	}
	else {
		static_assert(
		     ::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_has_single_bit");
	}
}

template <typename _Value>
int _ZTDC_BIT_WIDTH_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char> ||      // cf-hack
	     ::std::is_same_v<_Value, unsigned short> || ::std::is_same_v<_Value, unsigned int> ||      // cf-hack
	     ::std::is_same_v<_Value, unsigned long> || ::std::is_same_v<_Value, unsigned long long>) { // cf-hack
		return ((sizeof(__value) * CHAR_BIT) - ztdc_count_leading_zeros(__value));
	}
	else {
		static_assert(::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_bit_width");
	}
}

template <typename _Value>
int _ZTDC_BIT_CEIL_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_bit_ceiluc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_bit_ceilus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_bit_ceilui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_bit_ceilul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_bit_ceilull(__value);
	}
	else {
		static_assert(::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_bit_ceil");
	}
}

template <typename _Value>
int _ZTDC_BIT_FLOOR_I_(_Value __value) noexcept {
	if constexpr (::std::is_same_v<_Value, char> || ::std::is_same_v<_Value, unsigned char>) {
		return ztdc_bit_flooruc(static_cast<unsigned char>(__value));
	}
	else if constexpr (::std::is_same_v<_Value, unsigned short>) {
		return ztdc_bit_floorus(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned int>) {
		return ztdc_bit_floorui(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long>) {
		return ztdc_bit_floorul(__value);
	}
	else if constexpr (::std::is_same_v<_Value, unsigned long long>) {
		return ztdc_bit_floorull(__value);
	}
	else {
		static_assert(::ztd::always_false_v<_Value>, "Only an unsigned integer type can be given to ztdc_bit_floor");
	}
}
#endif // C vs. C++ only

#endif // ZTD_IDK_DETAIL_BIT_INTRINSIC_H
