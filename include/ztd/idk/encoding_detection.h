// =============================================================================
//
// ztd.cuneicode
// Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.cuneicode licenses may use this file
// in accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================

#ifndef ZTD_IDK_ENCODING_DETECTION_H
#define ZTD_IDK_ENCODING_DETECTION_H

#pragma once

#include <ztd/idk/version.h>

#if ZTD_IS_ON(ZTD_C)
#include <stdbool.h>
#endif // C++

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_execution_encoding_utf8(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_execution_encoding_utf16(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_execution_encoding_utf32(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_execution_encoding_unicode(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_wide_execution_encoding_unicode(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_wide_execution_encoding_utf8(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_wide_execution_encoding_utf16(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) bool ztdc_is_wide_execution_encoding_utf32(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) const char* ztdc_literal_encoding_name(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) const char* ztdc_wide_literal_encoding_name(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) const char* ztdc_execution_encoding_name(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);
ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE) const char* ztdc_wide_execution_encoding_name(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);


#if ZTD_IS_ON(ZTD_PLATFORM_WINDOWS)

// slight speed optimization for Windows machines
#define ZTD_MB_UTF8 (ztdc_is_execution_encoding_utf8())
#define ZTD_MB_UTF16 0
#define ZTD_MB_UTF32 0

#define ZTD_WCHAR_UTF8 0
#define ZTD_WCHAR_UTF16 1
#define ZTD_WCHAR_UTF32 0

#else

#include <ztd/idk/charN_t.h>
#if ZTD_IS_ON(ZTD_C)
#include <limits.h>
#else
#include <climits>
#endif // C++

// fall back to default implementation
#define ZTD_MB_UTF8 (ztdc_is_execution_encoding_utf8())
#define ZTD_MB_UTF16 ((CHAR_BIT >= 16) && ztdc_is_execution_encoding_utf16())
#define ZTD_MB_UTF32 ((CHAR_BIT >= 32) && ztdc_is_execution_encoding_utf32())

#define ZTD_WCHAR_UTF8 (ztdc_is_wide_execution_encoding_utf8())
#define ZTD_WCHAR_UTF16 (((sizeof(ztd_wchar_t) * CHAR_BIT) >= 16) && ztdc_is_wide_execution_encoding_utf16())
#define ZTD_WCHAR_UTF32 (((sizeof(ztd_wchar_t) * CHAR_BIT) >= 32) && ztdc_is_wide_execution_encoding_utf32())

#endif

#endif
