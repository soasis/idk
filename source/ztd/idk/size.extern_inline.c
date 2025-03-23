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

#include <ztd/idk/charN_t.h>

#if ZTD_IS_ON(ZTD_CXX)
#include <climits>
#include <cstddef>
#include <ztd/idk/type_traits.hpp>
#else
#include <limits.h>
#include <stddef.h>
#endif

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX) size_t ztdc_c_string_ptr_size_c(const char* __ptr) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_uc(const unsigned char* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX) size_t ztdc_c_string_ptr_size_sc(const signed char* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX) size_t ztdc_c_string_ptr_size_wc(const ztd_wchar_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX) size_t ztdc_c_string_ptr_size_c8(const ztd_char8_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_c16(const ztd_char16_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_c32(const ztd_char32_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX) size_t ztdc_c_string_ptr_size_limit_c(size_t __limit, const char* __ptr) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_limit_uc(size_t __limit, const unsigned char* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_limit_sc(size_t __limit, const signed char* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_limit_wc(size_t __limit, const ztd_wchar_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_limit_c8(size_t __limit, const ztd_char8_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_limit_c16(size_t __limit, const ztd_char16_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_CONSTEXPR_IF_CXX)
size_t ztdc_c_string_ptr_size_limit_c32(size_t __limit, const ztd_char32_t* __ptr) ZTD_USE(ZTD_NOEXCEPT_IF_CXX) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr && __limit-- > 0; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}
