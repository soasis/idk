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

#ifndef ZTD_IDK_DETAIL_WINDOWS_HPP
#define ZTD_IDK_DETAIL_WINDOWS_HPP

#include <ztd/idk/version.h>
#if ZTD_IS_ON(ZTD_CXX)
#include <ztd/idk/version.hpp>
#endif



#if ZTD_IS_ON(ZTD_CXX)
#include <cstdint>
#else
#include <stdint.h>
#endif

#if ZTD_IS_ON(ZTD_CXX)
namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_
	namespace __idk_detail { namespace __windows {

		inline constexpr int32_t __code_page_active        = 0;
		inline constexpr int32_t __code_page_oem           = 1;
		inline constexpr int32_t __code_page_mac           = 2;
		inline constexpr int32_t __code_page_active_thread = 3;
	}} // namespace __idk_detail::__windows
	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd
#endif

#if ZTD_IS_ON(ZTD_PLATFORM_WINDOWS)

#if ZTD_IS_ON(ZTD_COMPILER_VCXX) || ZTD_IS_ON(ZTD_COMPILER_GCC)
#pragma push_macro("NOMINMAX")
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#pragma push_macro("VC_EXTRALEAN")
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN
#undef VC_EXTRALEAN
#endif

#define NOMINMAX 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1

#if ZTD_IS_ON(ZTD_COMPILER_VCXX)
#if ZTD_IS_ON(ZTD_CXX)
#include <cstddef>
#include <cwchar>
#include <locale>
#else
#include <stddef.h>
#include <wchar.h>
#endif
#endif

ZTD_USE(ZTD_EXTERN_C_OPEN)
#include <Windows.h>
ZTD_USE(ZTD_EXTERN_C_CLOSE)
#include <winapifamily.h>

#include <ztd/prologue.hpp>

#if !defined(_KERNELX) && !defined(_ONECORE)
#if defined(WINAPI_FAMILY) || defined(WINAPI_FAMILY_APP)
#define ZTD_FILEAPISAREANSI_I_ ZTD_OFF
#else
#define ZTD_FILEAPISAREANSI_I_ ZTD_ON
#endif
#else
#define ZTD_FILEAPISAREANSI_I_ ZTD_OFF
#endif

#if ZTD_IS_ON(ZTD_CXX)
namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_
	namespace __idk_detail { namespace __windows {

		inline int __determine_active_code_page() noexcept {
#if defined(_STL_LANG) || defined(_YVALS_CORE_H) || defined(_STDEXT)
			// Removed in later versions of VC++
			if (___lc_codepage_func() == CP_UTF8) {
				return CP_UTF8;
			}
#endif // VC++ stuff

#if ZTD_IS_ON(ZTD_FILEAPISAREANSI)
			if (!::AreFileApisANSI()) {
				return CP_OEMCP;
			}
#endif // !defined(_KERNELX) && !defined(_ONECORE)

			return CP_ACP;
		}

		inline bool __is_unicode_code_page(int __codepage_id) {
			switch (__codepage_id) {
			case CP_UTF7:
			case CP_UTF8:
			case 1200:  // UTF-16, Little Endian ("utf-16")
			case 1201:  // UTF-16, Big Endian ("unicodeFFFE")
			case 12000: // UTF-16, Little Endian ("utf-32")
			case 12001: // UTF-16, Big Endian ("utf-32BE")
			case 54936: // GB18030, 4 bytes long
				return true;
			default:
				return false;
			}
		}

		struct __mbtowc_default_used {
			int __flags;
			const char* __p_default_char;
			BOOL* __p_default_char_used;
		};

		inline __mbtowc_default_used __widechar_to_multibyte_used_char(
			uint32_t __codepage_id, const char* __p_default_char, BOOL* __p_default_char_used) {
			__mbtowc_default_used __used = { 0, __p_default_char, __p_default_char_used };
			switch (__codepage_id) {
			case 50220:
			case 50221:
			case 50222:
			case 50225:
			case 50227:
			case 50229:
			case 57002:
			case 57003:
			case 57004:
			case 57005:
			case 57006:
			case 57007:
			case 57008:
			case 57009:
			case 57010:
			case 57011:
			case 65000: //(UTF-7)
			case 42:    // (Symbol)
				// flags are not allowed for these
				__used.__flags = 0;
				// UNDOCUMENTED: these parameters are not allowed to be pass as anything but "nullptr" for these
				// conversions. Microsoft, of course, refuses to mention this.
				__used.__p_default_char      = nullptr;
				__used.__p_default_char_used = nullptr;
				break;
			case 54936:
			case 65001: // UTF-8
				__used.__flags |= WC_ERR_INVALID_CHARS;
				break;
			case 0:
			case 1:
			case 2:
			case 3:
				// unsure for these...?
				__used.__flags |= WC_ERR_INVALID_CHARS;
				break;
			default:
				break;
			}
			switch (__codepage_id) {
			case 65000: //(UTF-7)
			case 65001: //(UTF-8)
				// not allowed to use default character pointers
				__used.__p_default_char      = nullptr;
				__used.__p_default_char_used = nullptr;
			default:
				break;
			}
			return __used;
		}

		inline uint32_t __multibyte_to_widechar_flags(uint32_t __codepage_id) {
			switch (__codepage_id) {
			case 50220:
			case 50221:
			case 50222:
			case 50225:
			case 50227:
			case 50229:
			case 57002:
			case 57003:
			case 57004:
			case 57005:
			case 57006:
			case 57007:
			case 57008:
			case 57009:
			case 57010:
			case 57011:
			case 65000: //(UTF-7)
			case 42:    // (Symbol)
				// flags are not allowed for these
				return 0;
			default:
				break;
			}
			return MB_ERR_INVALID_CHARS;
		}

		ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
		ZTD_USE(ZTD_IDK_API_LINKAGE)
		bool __get_codepage_descirptor(uint32_t __codepage_id, CPINFOEXW** __pp_codepage_info)
			ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

		// double-check if we were screwed over by the conversion: given
		// Win32's undocumented fuckups around this, the only way to know if
		// we actually failed is by checking if the single character we output
		// is equal to a replacement character, and if the replacement
		// character is NOT present in the original stream. The proper way to
		// do this is to call GetCPInfoExW and then using a comparison to the
		// MultiByte stream. But there's so many different things wrong with
		// it, and it's hard to know.

		ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
		ZTD_USE(ZTD_IDK_API_LINKAGE)
		bool __widechar_to_multibyte_conversion_failed(const WCHAR* __input, size_t __output_size,
			const CHAR* __output, CPINFOEXW* __p_codepage_info) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

		ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
		ZTD_USE(ZTD_IDK_API_LINKAGE)
		bool __multibyte_to_widechar_conversion_failed(size_t __input_size, const CHAR* __input,
			const WCHAR* __output, CPINFOEXW* __p_codepage_info) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

	}} // namespace __idk_detail::__windows
	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#endif

#if ZTD_IS_ON(ZTD_COMPILER_VCXX)
#pragma pop_macro("VC_EXTRALEAN")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#pragma pop_macro("NOMINMAX")
#endif

#endif // Windows nightmare

#include <ztd/epilogue.hpp>

#endif
