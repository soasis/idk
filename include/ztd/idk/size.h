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

#ifndef ZTD_IDK_SIZE_H
#define ZTD_IDK_SIZE_H

#include <ztd/idk/charN_t.h>

#if ZTD_IS_ON(ZTD_CXX)
#include <climits>
#include <cstddef>
#else
#include <limits.h>
#include <stddef.h>
#endif

#define ztd_c_array_size(...) (sizeof((__VA_ARGS__)) / sizeof(*(__VA_ARGS__)))
#define ztd_c_string_array_size(...) (ztd_c_array_size(__VA_ARGS__) - 1)

#define ztd_c_array_byte_size(...) (ztd_c_array_size(__VA_ARGS__) * sizeof(*(__VA_ARGS__)))
#define ztd_c_string_array_byte_size(...) (ztd_c_string_array_size(__VA_ARGS__) * sizeof(*(__VA_ARGS__)))

#define ztd_c_array_bit_size(...) (ztd_c_array_byte_size(__VA_ARGS__) * CHAR_BIT)
#define ztd_c_string_array_bit_size(...) (ztd_c_string_array_byte_size(__VA_ARGS__) * CHAR_BIT)

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size(const char* __ptr) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_uc(const unsigned char* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c8(const ztd_char8_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c16(const ztd_char16_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c32(const ztd_char32_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

#endif
