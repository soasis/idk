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

#ifndef ZTD_IDK_DETAIL_UNICODE_H
#define ZTD_IDK_DETAIL_UNICODE_H

#include <ztd/idk/version.h>

#include <ztd/idk/charN_t.h>

#include <ztd/prologue.hpp>

ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_last_unicode_code_point = 0x10FFFF;
ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_first_lead_surrogate    = 0xD800;
ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_last_lead_surrogate     = 0xDBFF;
ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_first_trail_surrogate   = 0xDC00;
ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_last_trail_surrogate    = 0xDFFF;
ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_first_surrogate
     = __ztd_idk_detail_first_lead_surrogate;
ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_char32_t __ztd_idk_detail_last_surrogate
     = __ztd_idk_detail_last_trail_surrogate;

inline ZTD_CONSTEXPR_IF_CXX_I_ bool __ztd_idk_detail_is_lead_surrogate(ztd_char32_t __value) ZTD_NOEXCEPT_IF_CXX_I_ {
	return __value >= __ztd_idk_detail_first_lead_surrogate && __value <= __ztd_idk_detail_last_lead_surrogate;
}
inline ZTD_CONSTEXPR_IF_CXX_I_ bool __ztd_idk_detail_is_trail_surrogate(ztd_char32_t __value) ZTD_NOEXCEPT_IF_CXX_I_ {
	return __value >= __ztd_idk_detail_first_trail_surrogate && __value <= __ztd_idk_detail_last_trail_surrogate;
}
inline ZTD_CONSTEXPR_IF_CXX_I_ bool __ztd_idk_detail_is_surrogate(ztd_char32_t __value) ZTD_NOEXCEPT_IF_CXX_I_ {
	return __value >= __ztd_idk_detail_first_surrogate && __value <= __ztd_idk_detail_last_surrogate;
}
inline ZTD_CONSTEXPR_IF_CXX_I_ bool __ztd_idk_detail_is_lead_utf8(ztd_char8_t __value) ZTD_NOEXCEPT_IF_CXX_I_ {
	return (__value & static_cast<ztd_char8_t>(0b11000000)) == static_cast<ztd_char8_t>(0b10000000);
}
inline ZTD_CONSTEXPR_IF_CXX_I_ bool __ztd_idk_detail_is_single_or_lead_utf8(
     ztd_char8_t __value) ZTD_NOEXCEPT_IF_CXX_I_ {
	return __value <= static_cast<ztd_char8_t>(0x7F) || __ztd_idk_detail_is_lead_utf8(__value);
}

#include <ztd/epilogue.hpp>

#endif // ZTD_IDK_DETAIL_UNICODE_H
