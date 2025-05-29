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

#include <ztd/idk/version.h>
#include <ztd/idk/version.hpp>

#include <ztd/idk/thread_local.h>
#include <ztd/idk/detail/windows.hpp>

#include <map>
#include <memory>

#if ZTD_IS_ON(ZTD_PLATFORM_WINDOWS)

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_
	namespace __idk_detail { namespace __windows {

		ztd_thread_local ::std::map<uint32_t, ::std::unique_ptr<CPINFOEXW>> __codepage_descriptors;

		ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
		ZTD_USE(ZTD_IDK_API_LINKAGE)
		bool __get_codepage_descirptor(uint32_t __codepage_id, CPINFOEXW** __pp_codepage_info)
			ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
			if (__pp_codepage_info == nullptr) {
				return false;
			}
			if (__codepage_id == CP_ACP || __codepage_id == CP_THREAD_ACP) {
				__codepage_id = static_cast<uint32_t>(GetACP());
			}
			else if (__codepage_id == CP_OEMCP) {
				__codepage_id = static_cast<uint32_t>(GetOEMCP());
			}
			auto __it = __codepage_descriptors.find(__codepage_id);
			if (__it == __codepage_descriptors.cend()) {
				CPINFOEXW __info = {};
				if (GetCPInfoExW(static_cast<UINT>(__codepage_id), 0, &__info) == 0) {
					// somehow failed: we can't use this
					*__pp_codepage_info = nullptr;
					return false;
				}
				__it = __codepage_descriptors.insert(::std::move(__it),
					::std::pair<uint32_t, ::std::unique_ptr<CPINFOEXW>>(
					     __codepage_id, ::std::make_unique<CPINFOEXW>(__info)));
			}
			*__pp_codepage_info = __it->second.get();
			return true;
		}

		ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
		ZTD_USE(ZTD_IDK_API_LINKAGE)
		bool __widechar_to_multibyte_conversion_failed(const WCHAR* __input, size_t __output_size,
			const CHAR* __output, CPINFOEXW* __p_codepage_info) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
			if (!__p_codepage_info) {
				return false;
			}
			if (__output[0] != __p_codepage_info->DefaultChar[0]) {
				return false;
			}
			if (__p_codepage_info->DefaultChar[1] == '\0') {
				// There is only a single byte worth of default characters
				if (__input[0] == __p_codepage_info->UnicodeDefaultChar) {
					// if the input IS equal to the UTF-16 default character, then it wasn't change and instead
					// just a default transfer of what was expected.
					// NOTE: this can be a false positive, but like. What the hell else are we supposed to do?
					return false;
				}
				else {
					// Otherwise, if there isn't a second char then we're done here: the wide character was NOT
					// already the default and it changed therein.
					return true;
				}
			}
			if (__output_size < 2u || __p_codepage_info->DefaultChar[1] != __output[1]) {
				return false;
			}
			if (__input[0] != __p_codepage_info->UnicodeDefaultChar) {
				return false;
			}
			// if all things are equal, then there was, in fact, a failure
			return true;
		}

		ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
		ZTD_USE(ZTD_IDK_API_LINKAGE)
		bool __multibyte_to_widechar_conversion_failed(size_t __input_size, const CHAR* __input,
			const WCHAR* __output, CPINFOEXW* __p_codepage_info) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
			if (!__p_codepage_info) {
				return false;
			}
			if (__output[0] != __p_codepage_info->UnicodeDefaultChar || __output[0] != '?') {
				// The output does not have the replacement character!
				return false;
			}
			// Okay: the output has a replaced character. It's time to check if the input already had the (original)
			// replacement character.
			if (__input[0] == __p_codepage_info->DefaultChar[0]) {
				// if the input is equal to the default character, then we can't be sure.
				if (__p_codepage_info->DefaultChar[1] == '\0') {
					// This is the maximum length so it definitely can't be sure.
					return false;
				}
				if (__input_size > 1u && __p_codepage_info->DefaultChar[1] == __input[1]) {
					// okay, so we have 2 characters and they're both equal: we cannot be sure.
					return false;
				}
			}
			// the input does not contain the same characters, and the output IS the default character:
			// that seems like a replacement! Which means the conversion DID fail.
			return true;
		}

	}} // namespace __idk_detail::__windows
	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#endif
