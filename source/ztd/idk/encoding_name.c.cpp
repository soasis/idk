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

#include <ztd/idk/encoding_name.h>
#include <ztd/idk/encoding_name.hpp>

#include <ztd/idk/size.hpp>

ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_encoding_name_equal(
     const char* __left_encoding_name, const char* __right_encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_encoding_name_equal(__left_encoding_name, __right_encoding_name);
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_encoding_name_equal_n(size_t __left_encoding_name_size,
     const char* __left_encoding_name, size_t __right_encoding_name_size,
     const char* __right_encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_encoding_name_equal(
	     { __left_encoding_name, __left_encoding_name_size }, { __right_encoding_name, __right_encoding_name_size });
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_encoding_name_equal_c8(
     const ztd_char8_t* __left_encoding_name, const ztd_char8_t* __right_encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_encoding_name_equal(__left_encoding_name, __right_encoding_name);
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_encoding_name_equal_c8n(size_t __left_encoding_name_size,
     const ztd_char8_t* __left_encoding_name, size_t __right_encoding_name_size,
     const ztd_char8_t* __right_encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_encoding_name_equal(
	     { __left_encoding_name, __left_encoding_name_size }, { __right_encoding_name, __right_encoding_name_size });
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_encoding_name_equal_c8n_c8(
     size_t __left_encoding_name_size, const ztd_char8_t* __left_encoding_name,
     const ztd_char8_t* __right_encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_encoding_name_equal({ __left_encoding_name, __left_encoding_name_size },
	     { __right_encoding_name, ztdc_c_string_ptr_size_c8(__right_encoding_name) });
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_unicode_encoding_name(
     const char* __encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_unicode_encoding_name(__encoding_name);
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_unicode_encoding_name_c8(
     const ztd_char8_t* __encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_unicode_encoding_name(__encoding_name);
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_unicode_encoding_name_n(
     size_t __encoding_name_size, const char* __encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_unicode_encoding_name({ __encoding_name, __encoding_name_size });
}
ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_IDK_API_LINKAGE_I_ bool ztdc_is_unicode_encoding_name_c8n(
     size_t __encoding_name_size, const ztd_char8_t* __encoding_name) ZTD_NOEXCEPT_IF_CXX_I_ {
	return ::ztd::is_unicode_encoding_name({ __encoding_name, __encoding_name_size });
}
