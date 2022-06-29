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

#ifndef ZTD_IDK_DETAIL_BIT_MEMREVERSE_IMPL_H
#define ZTD_IDK_DETAIL_BIT_MEMREVERSE_IMPL_H

#include <ztd/idk/version.h>

#include <ztd/idk/bit.h>

#include <ztd/idk/extent.h>
#include <ztd/idk/static_assert.h>

#if ZTD_IS_ON(ZTD_C_I_)
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#else
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <climits>
#endif

#define __ZTDC_MEMREVERSE8_IMPL(_TYPE, _PTR_COUNT, _PTR)                                               \
	for (size_t index = 0, limit = ((_PTR_COUNT * (sizeof(_TYPE) * CHAR_BIT)) / 2); index < limit;) { \
		const size_t ptr_index         = index / CHAR_BIT;                                           \
		const size_t reverse_ptr_index = _PTR_COUNT - 1 - ptr_index;                                 \
		_TYPE* p                       = _PTR + ptr_index;                                           \
		_TYPE* reverse_p               = _PTR + reverse_ptr_index;                                   \
		const _TYPE b_temp             = *p;                                                         \
		const _TYPE reverse_b_temp     = *reverse_p;                                                 \
		*p                             = 0;                                                          \
		*reverse_p                     = 0;                                                          \
		for (size_t bit_index = 0, bit_limit = ((sizeof(_TYPE) * CHAR_BIT)); bit_index < bit_limit;  \
		     bit_index += 8) {                                                                       \
			const size_t reverse_bit_index = (sizeof(_TYPE) * CHAR_BIT) - 8 - bit_index;            \
			const _TYPE bit_mask           = ((_TYPE)0xFF) << bit_index;                            \
			const _TYPE reverse_bit_mask   = ((_TYPE)0xFF) << reverse_bit_index;                    \
			*p |= (((reverse_b_temp & reverse_bit_mask) >> reverse_bit_index) << bit_index);        \
			*reverse_p |= (((b_temp & bit_mask) >> bit_index) << reverse_bit_index);                \
			index += 8;                                                                             \
		}                                                                                            \
	}                                                                                                 \
	ztd_static_assert(true, "end-of-macro")

#endif // ZTD_IDK_DETAIL_BIT_MEMREVERSE_IMPL_H
