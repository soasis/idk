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

#ifndef ZTD_IDK_DETAIL_BIT_INTRINSIC_H
#define ZTD_IDK_DETAIL_BIT_INTRINSIC_H

#include <ztd/idk/version.h>

#include <ztd/idk/static_assert.h>

#if ZTD_IS_ON(ZTD_C)
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

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_ones_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_ones_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_ones_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_ones_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_ones_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_zeros_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_zeros_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_zeros_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_zeros_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_zeros_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_zeros_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_zeros_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_zeros_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_zeros_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_zeros_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_ones_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_ones_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_ones_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_ones_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_leading_ones_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_zeros_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_zeros_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_zeros_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_zeros_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_zeros_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_ones_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_ones_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_ones_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_ones_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_count_trailing_ones_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_one_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_one_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_one_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_one_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_one_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_one_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_one_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_one_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_one_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_one_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_zero_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_zero_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_zero_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_zero_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_leading_zero_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_zero_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_zero_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_zero_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_zero_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_first_trailing_zero_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned char ztdc_rotate_left_uc(unsigned char value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned short ztdc_rotate_left_us(unsigned short value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned int ztdc_rotate_left_ui(unsigned int value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned long ztdc_rotate_left_ul(unsigned long value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned long long ztdc_rotate_left_ull(unsigned long long value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned char ztdc_rotate_right_uc(unsigned char value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned short ztdc_rotate_right_us(unsigned short value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned int ztdc_rotate_right_ui(unsigned int value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned long ztdc_rotate_right_ul(unsigned long value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
unsigned long long ztdc_rotate_right_ull(unsigned long long value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_has_single_bit_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_has_single_bit_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_has_single_bit_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_has_single_bit_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_has_single_bit_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned char ztdc_bit_floor_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned short ztdc_bit_floor_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_bit_floor_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned long ztdc_bit_floor_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned long long ztdc_bit_floor_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned char ztdc_bit_ceil_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned short ztdc_bit_ceil_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_bit_ceil_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned long ztdc_bit_ceil_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned long long ztdc_bit_ceil_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned char ztdc_bit_width_uc(unsigned char value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned short ztdc_bit_width_us(unsigned short value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned int ztdc_bit_width_ui(unsigned int value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned long ztdc_bit_width_ul(unsigned long value) ZTD_CXX_NOEXCEPT_I_;
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) unsigned long long ztdc_bit_width_ull(unsigned long long value) ZTD_CXX_NOEXCEPT_I_;

ZTD_EXTERN_C_CLOSE_I_

#endif
