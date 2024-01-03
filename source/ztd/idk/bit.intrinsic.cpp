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

#include <ztd/idk/version.hpp>

#include <ztd/idk/bit.hpp>

#include <ztd/idk/endian.h>
#include <ztd/idk/static_assert.h>
#include <ztd/idk/assume_aligned.hpp>

#if ZTD_IS_ON(ZTD_C)
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#else
#include <cstring>
#include <cstddef>
#include <cstdint>
#endif

unsigned int ztdc_count_ones_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_ones(__value);
}
unsigned int ztdc_count_ones_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_ones(__value);
}
unsigned int ztdc_count_ones_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_ones(__value);
}
unsigned int ztdc_count_ones_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_ones(__value);
}
unsigned int ztdc_count_ones_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_ones(__value);
}

unsigned int ztdc_count_zeros_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_zeros(__value);
}
unsigned int ztdc_count_zeros_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_zeros(__value);
}
unsigned int ztdc_count_zeros_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_zeros(__value);
}
unsigned int ztdc_count_zeros_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_zeros(__value);
}
unsigned int ztdc_count_zeros_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_zeros(__value);
}

bool ztdc_has_single_bit_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::has_single_bit(__value);
}
bool ztdc_has_single_bit_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::has_single_bit(__value);
}
bool ztdc_has_single_bit_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::has_single_bit(__value);
}
bool ztdc_has_single_bit_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::has_single_bit(__value);
}
bool ztdc_has_single_bit_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::has_single_bit(__value);
}

#if ZTD_IS_ON(ZTD_BUILTIN_CLZ)
#define _ZTDC_COUNT_LEADING_ZEROES_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX, _BUILTIN_ADJUSTMENT) \
	if (_VALUE == 0)                                                                           \
		return (unsigned int)(sizeof(_VALUE) * CHAR_BIT);                                     \
	return (unsigned int)(__builtin_clz##_BUILTIN_SUFFIX(_VALUE) - _BUILTIN_ADJUSTMENT)
#else
#define _ZTDC_COUNT_LEADING_ZEROES_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX, _BUILTIN_ADJUSTMENT) \
	int __num = 0;                                                                             \
	for (size_t __bit_index = (sizeof((_VALUE)) * CHAR_BIT); __bit_index-- > 0;) {             \
		bool __not_is_set = (_VALUE & (_TYPE)((_TYPE)(1) << __bit_index)) == (_TYPE)(0);      \
		if (__not_is_set) {                                                                   \
			__num += 1;                                                                      \
		}                                                                                     \
		else {                                                                                \
			break;                                                                           \
		}                                                                                     \
	}                                                                                          \
	return __num
#endif

#if ZTD_IS_ON(ZTD_BUILTIN_CTZ)
#define _ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX, _BUILTIN_ADJUSTMENT) \
	if (_VALUE == 0)                                                                            \
		return sizeof(_VALUE) * CHAR_BIT;                                                      \
	return (unsigned int)(__builtin_ctz##_BUILTIN_SUFFIX(_VALUE) - _BUILTIN_ADJUSTMENT)
#else
#define _ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX, _BUILTIN_ADJUSTMENT) \
	unsigned int __num = 0;                                                                     \
	for (size_t __bit_index = 0; __bit_index < (sizeof((_VALUE)) * CHAR_BIT); ++__bit_index) {  \
		bool __not_is_set = (_VALUE & (_TYPE)((_TYPE)(1) << __bit_index)) == (_TYPE)(0);       \
		if (__not_is_set) {                                                                    \
			__num += 1;                                                                       \
		}                                                                                      \
		else {                                                                                 \
			break;                                                                            \
		}                                                                                      \
	}                                                                                           \
	return __num
#endif

unsigned int ztdc_count_leading_zeros_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_LEADING_ZEROES_BODY_I_(
	     unsigned char, __value, , ((sizeof(unsigned int) * CHAR_BIT) - (sizeof(unsigned char) * CHAR_BIT)));
}
unsigned int ztdc_count_leading_zeros_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_LEADING_ZEROES_BODY_I_(
	     unsigned short, __value, , ((sizeof(unsigned int) * CHAR_BIT) - (sizeof(unsigned short) * CHAR_BIT)));
}
unsigned int ztdc_count_leading_zeros_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_LEADING_ZEROES_BODY_I_(unsigned int, __value, , 0);
}
unsigned int ztdc_count_leading_zeros_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_LEADING_ZEROES_BODY_I_(unsigned long, __value, l, 0);
}
unsigned int ztdc_count_leading_zeros_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_LEADING_ZEROES_BODY_I_(unsigned long long, __value, ll, 0);
}

unsigned int ztdc_count_trailing_zeros_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(unsigned char, __value, , 0);
}
unsigned int ztdc_count_trailing_zeros_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(unsigned short, __value, , 0);
}
unsigned int ztdc_count_trailing_zeros_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(unsigned int, __value, , 0);
}
unsigned int ztdc_count_trailing_zeros_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(unsigned long, __value, l, 0);
}
unsigned int ztdc_count_trailing_zeros_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_COUNT_TRAILING_ZEROES_BODY_I_(unsigned long long, __value, ll, 0);
}

#undef _ZTDC_COUNT_LEADING_ZEROES_BODY_I_
#undef _ZTDC_COUNT_TRAILING_ZEROES_BODY_I_

unsigned int ztdc_count_leading_ones_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_leading_zeros((unsigned char)~__value);
}
unsigned int ztdc_count_leading_ones_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_leading_zeros((unsigned short)~__value);
}
unsigned int ztdc_count_leading_ones_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_leading_zeros((unsigned int)~__value);
}
unsigned int ztdc_count_leading_ones_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_leading_zeros((unsigned long)~__value);
}
unsigned int ztdc_count_leading_ones_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_leading_zeros((unsigned long long)~__value);
}

unsigned int ztdc_count_trailing_ones_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_trailing_zeros((unsigned char)~__value);
}
unsigned int ztdc_count_trailing_ones_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_trailing_zeros((unsigned short)~__value);
}
unsigned int ztdc_count_trailing_ones_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_trailing_zeros((unsigned int)~__value);
}
unsigned int ztdc_count_trailing_ones_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_trailing_zeros((unsigned long)~__value);
}
unsigned int ztdc_count_trailing_ones_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::count_trailing_zeros((unsigned long long)~__value);
}

#define _ZTDC_ROTATE_LEFT_BODY_I_()                              \
	if (__count == 0) {                                         \
		return __value;                                        \
	}                                                           \
	const unsigned int __width    = sizeof(__value) * CHAR_BIT; \
	const unsigned int __rotation = __count % __width;          \
	return (__value << __rotation) | (__value >> (__width - __rotation))

#define _ZTDC_ROTATE_RIGHT_BODY_I_()                             \
	if (__count == 0) {                                         \
		return __value;                                        \
	}                                                           \
	const unsigned int __width    = sizeof(__value) * CHAR_BIT; \
	const unsigned int __rotation = __count % __width;          \
	return (__value >> __rotation) | (__value << (__width - __rotation))

unsigned char ztdc_rotate_left_uc(unsigned char __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_LEFT_BODY_I_();
}
unsigned short ztdc_rotate_left_us(unsigned short __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_LEFT_BODY_I_();
}
unsigned int ztdc_rotate_left_ui(unsigned int __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_LEFT_BODY_I_();
}
unsigned long ztdc_rotate_left_ul(unsigned long __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_LEFT_BODY_I_();
}
unsigned long long ztdc_rotate_left_ull(unsigned long long __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_LEFT_BODY_I_();
}

unsigned char ztdc_rotate_right_uc(unsigned char __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_RIGHT_BODY_I_();
}
unsigned short ztdc_rotate_right_us(unsigned short __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_RIGHT_BODY_I_();
}
unsigned int ztdc_rotate_right_ui(unsigned int __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_RIGHT_BODY_I_();
}
unsigned long ztdc_rotate_right_ul(unsigned long __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_RIGHT_BODY_I_();
}
unsigned long long ztdc_rotate_right_ull(unsigned long long __value, unsigned int __count) ZTD_CXX_NOEXCEPT_I_ {
	_ZTDC_ROTATE_RIGHT_BODY_I_();
}

#undef _ZTDC_ROTATE_LEFT_BODY_I_
#undef _ZTDC_ROTATE_RIGHT_BODY_I_

#define _ZTDC_BIT_FLOOR_BODY_I_(_TYPE, ...) \
	((__VA_ARGS__ == (_TYPE)0) ? (_TYPE)0 : (((_TYPE)1) << (::ztd::bit_width(__VA_ARGS__) - 1)));

unsigned char ztdc_bit_floor_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return _ZTDC_BIT_FLOOR_BODY_I_(unsigned char, __value);
}
unsigned short ztdc_bit_floor_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return _ZTDC_BIT_FLOOR_BODY_I_(unsigned short, __value);
}
unsigned int ztdc_bit_floor_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return _ZTDC_BIT_FLOOR_BODY_I_(unsigned int, __value);
}
unsigned long ztdc_bit_floor_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return _ZTDC_BIT_FLOOR_BODY_I_(unsigned long, __value);
}
unsigned long long ztdc_bit_floor_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return _ZTDC_BIT_FLOOR_BODY_I_(unsigned long long, __value);
}

#undef _ZTDC_BIT_FLOOR_BODY_I_

#if ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
#pragma warning(push)
#pragma warning(disable : 4333 4293)
#endif

unsigned char ztdc_bit_ceil_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_ceil(__value);
}
unsigned short ztdc_bit_ceil_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_ceil(__value);
}
unsigned int ztdc_bit_ceil_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_ceil(__value);
}
unsigned long ztdc_bit_ceil_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_ceil(__value);
}
unsigned long long ztdc_bit_ceil_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_ceil(__value);
}

#if ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
#pragma GCC diagnostic pop
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
#pragma warning(pop)
#endif

unsigned char ztdc_bit_width_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_width(__value);
}
unsigned short ztdc_bit_width_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_width(__value);
}
unsigned int ztdc_bit_width_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_width(__value);
}
unsigned long ztdc_bit_width_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_width(__value);
}
unsigned long long ztdc_bit_width_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ::ztd::bit_width(__value);
}

#if ZTD_IS_ON(ZTD_BUILTIN_CLZ)
#define _ZTD_FIRST_LEADING_ONE_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX, _BUILTIN_ADJUSTMENT) \
	if (_VALUE == 0) {                                                                     \
		return 0;                                                                         \
	}                                                                                      \
	return __builtin_clz##_BUILTIN_SUFFIX(_VALUE) + 1 - (_BUILTIN_ADJUSTMENT);
#else
#define _ZTD_FIRST_LEADING_ONE_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX, _BUILTIN_ADJUSTMENT) \
	for (size_t __bit_index = (sizeof(_VALUE) * CHAR_BIT); __bit_index-- > 0;) {           \
		bool __is_set = (_VALUE & (_TYPE)(((_TYPE)1) << __bit_index)) != ((_TYPE)0);      \
		if (__is_set) {                                                                   \
			return (unsigned int)((sizeof(_VALUE) * CHAR_BIT) - __bit_index);            \
		}                                                                                 \
	}                                                                                      \
	return 0
#endif

unsigned int ztdc_first_leading_one_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_LEADING_ONE_BODY_I_(
	     unsigned char, __value, , ((sizeof(unsigned int) * CHAR_BIT) - (sizeof(unsigned char) * CHAR_BIT)));
}
unsigned int ztdc_first_leading_one_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_LEADING_ONE_BODY_I_(
	     unsigned short, __value, , ((sizeof(unsigned int) * CHAR_BIT) - (sizeof(unsigned short) * CHAR_BIT)));
}
unsigned int ztdc_first_leading_one_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_LEADING_ONE_BODY_I_(unsigned int, __value, , 0);
}
unsigned int ztdc_first_leading_one_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_LEADING_ONE_BODY_I_(unsigned long, __value, l, 0);
}
unsigned int ztdc_first_leading_one_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_LEADING_ONE_BODY_I_(unsigned long long, __value, ll, 0);
}

#undef _ZTD_FIRST_LEADING_ONE_BODY_I_

#if ZTD_IS_ON(ZTD_BUILTIN_FFS)
#define _ZTD_FIRST_TRAILING_ONE_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX) \
	return (unsigned int)__builtin_ffs##_BUILTIN_SUFFIX(_VALUE)
#else
#define _ZTD_FIRST_TRAILING_ONE_BODY_I_(_TYPE, _VALUE, _BUILTIN_SUFFIX)                       \
	for (size_t __bit_index = 0; __bit_index < (sizeof(_VALUE) * CHAR_BIT); ++__bit_index) { \
		bool __is_set = (_VALUE & (_TYPE)(((_TYPE)1) << __bit_index)) != ((_TYPE)0);        \
		if (__is_set) {                                                                     \
			return (unsigned int)(__bit_index + 1);                                        \
		}                                                                                   \
	}                                                                                        \
	return 0
#endif

unsigned int ztdc_first_trailing_one_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_TRAILING_ONE_BODY_I_(unsigned char, __value, );
}
unsigned int ztdc_first_trailing_one_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_TRAILING_ONE_BODY_I_(unsigned short, __value, );
}
unsigned int ztdc_first_trailing_one_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_TRAILING_ONE_BODY_I_(unsigned int, __value, );
}
unsigned int ztdc_first_trailing_one_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_TRAILING_ONE_BODY_I_(unsigned long, __value, l);
}
unsigned int ztdc_first_trailing_one_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	_ZTD_FIRST_TRAILING_ONE_BODY_I_(unsigned long long, __value, ll);
}

#undef _ZTD_FIRST_TRAILING_ONE_BODY_I_

unsigned int ztdc_first_leading_zero_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_leading_one_uc((unsigned char)~__value);
}
unsigned int ztdc_first_leading_zero_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_leading_one_us((unsigned short)~__value);
}
unsigned int ztdc_first_leading_zero_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_leading_one_ui((unsigned int)~__value);
}
unsigned int ztdc_first_leading_zero_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_leading_one_ul((unsigned long)~__value);
}
unsigned int ztdc_first_leading_zero_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_leading_one_ull((unsigned long long)~__value);
}

unsigned int ztdc_first_trailing_zero_uc(unsigned char __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_trailing_one_uc((unsigned char)~__value);
}
unsigned int ztdc_first_trailing_zero_us(unsigned short __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_trailing_one_us((unsigned short)~__value);
}
unsigned int ztdc_first_trailing_zero_ui(unsigned int __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_trailing_one_ui((unsigned int)~__value);
}
unsigned int ztdc_first_trailing_zero_ul(unsigned long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_trailing_one_ul((unsigned long)~__value);
}
unsigned int ztdc_first_trailing_zero_ull(unsigned long long __value) ZTD_CXX_NOEXCEPT_I_ {
	return ztdc_first_trailing_one_ull((unsigned long long)~__value);
}
