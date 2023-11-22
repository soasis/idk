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

#ifndef ZTD_IDK_GENERIC_H
#define ZTD_IDK_GENERIC_H

#include <ztd/idk/static_assert.hpp>

//////
/// @brief A type which, should it appear in user-facing code, means that some form of generic or metaprogramming has
/// failed miserably. Contact the vendor and provide a detailed compiler error trace from the macro, if applicable, to
/// help debug the issue!
typedef struct ztdc_incorrect_generic_t {
	void* __frowny_face;
} ztdc_incorrect_generic_t;

#if ZTD_IS_ON(ZTD_C)

void ztdc_uneval_void(void);
ztdc_incorrect_generic_t ztdc_uneval_incorrect_generic(void);

#define _ZTDC_WRONG_COUNT_ERR(...) \
	ztdc_static_assert(0, "an odd number of arguments was passed to the ZTDC_CASCADING_GENERIC expression!")

#define ZTDC_TYPE_SELECT_FUNC(...) (*((ztd_typeof(__VA_ARGS__)(*)())0))

#define ZTDC_DEFAULT default

#define _ZTDC_CASCADING_GENERIC_0(_CONTROLLING_EXPRESSION) /* nothing! In the future, maybe provoke an error? */
#define _ZTDC_CASCADING_GENERIC_2(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0) \
	_Generic((_CONTROLLING_EXPRESSION), _TYPE0: _CASE0)
#define _ZTDC_CASCADING_GENERIC_4(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                        \
	     _TYPE0: _CASE0,                                                       \
	     default: _ZTDC_CASCADING_GENERIC_2(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_6(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                        \
	     _TYPE0: _CASE0,                                                       \
	     default: _ZTDC_CASCADING_GENERIC_4(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_8(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                        \
	     _TYPE0: _CASE0,                                                       \
	     default: _ZTDC_CASCADING_GENERIC_6(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_10(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                         \
	     _TYPE0: _CASE0,                                                        \
	     default: _ZTDC_CASCADING_GENERIC_8(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_12(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                         \
	     _TYPE0: _CASE0,                                                        \
	     default: _ZTDC_CASCADING_GENERIC_10(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_14(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                         \
	     _TYPE0: _CASE0,                                                        \
	     default: _ZTDC_CASCADING_GENERIC_12(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_16(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                         \
	     _TYPE0: _CASE0,                                                        \
	     default: _ZTDC_CASCADING_GENERIC_14(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_18(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                         \
	     _TYPE0: _CASE0,                                                        \
	     default: _ZTDC_CASCADING_GENERIC_16(_CONTROLLING_EXPRESSION, __VA_ARGS__))
#define _ZTDC_CASCADING_GENERIC_20(_CONTROLLING_EXPRESSION, _TYPE0, _CASE0, ...) \
	_Generic((_CONTROLLING_EXPRESSION),                                         \
	     _TYPE0: _CASE0,                                                        \
	     default: _ZTDC_CASCADING_GENERIC_18(_CONTROLLING_EXPRESSION, __VA_ARGS__))

#define _ZTDC_CASCADING_GENERIC_SELECT(_FUN20, _ERR19, _FUN18, _ERR17, _FUN16, _ERR15, _FUN14, _ERR13, _FUN12, _ERR11, \
     _FUN10, _ERR9, _FUN8, _ERR7, _FUN6, _ERR5, _FUN4, _ERR3, _FUN2, _ERR1, _FUN_TARGET, ...)                          \
	_FUN_TARGET

#define ZTDC_CASCADING_GENERIC(_CONTROLLING_EXPRESSION, ...)                                                    \
	_ZTDC_CASCADING_GENERIC_SELECT(__VA_ARGS__, _ZTDC_CASCADING_GENERIC_20, _ZTDC_WRONG_COUNT_ERR,             \
	     _ZTDC_CASCADING_GENERIC_18, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_16, _ZTDC_WRONG_COUNT_ERR, \
	     _ZTDC_CASCADING_GENERIC_14, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_12, _ZTDC_WRONG_COUNT_ERR, \
	     _ZTDC_CASCADING_GENERIC_10, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_8, _ZTDC_WRONG_COUNT_ERR,  \
	     _ZTDC_CASCADING_GENERIC_6, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_4, _ZTDC_WRONG_COUNT_ERR,   \
	     _ZTDC_CASCADING_GENERIC_2, _ZTDC_WRONG_COUNT_ERR)                                                     \
	(_CONTROLLING_EXPRESSION, __VA_ARGS__)

#else

#include <ztd/idk/size.h>

#include <type_traits>

#define _ZTDC_WRONG_COUNT_ERR(...) \
	ztdc_static_assert(0, "an odd number of arguments was passed to the ZTDC_CASCADING_GENERIC expression!")

struct __ztdc_idk_detail_default_t {
	__ztdc_idk_detail_default_t()                                   = delete;
	__ztdc_idk_detail_default_t(const __ztdc_idk_detail_default_t&) = delete;
	__ztdc_idk_detail_default_t(__ztdc_idk_detail_default_t&&)      = delete;
};

#define ZTDC_DEFAULT __ztdc_idk_detail_default_t

#define _ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0)            \
	else if constexpr (::std::is_same_v<_TYPE0, _ZTDC_CONTROL_TYPE>) { \
		return _CASE0;                                                \
	}

#define _ZTDC_CASCADING_GENERIC_0() ztdc_static_assert(1, "")
#define _ZTDC_CASCADING_GENERIC_2(_TYPE0, _CASE0)                                \
	else {                                                                      \
		if constexpr (::std::is_same_v<_TYPE0, __ztdc_idk_detail_default_t>) { \
			return _CASE0;                                                    \
		}                                                                      \
		_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0)                   \
	}                                                                           \
	_ZTDC_CASCADING_GENERIC_0()
#define _ZTDC_CASCADING_GENERIC_4(_TYPE0, _CASE0, ...)    \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_2(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_6(_TYPE0, _CASE0, ...)    \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_4(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_8(_TYPE0, _CASE0, ...)    \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_6(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_10(_TYPE0, _CASE0, ...)   \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_8(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_12(_TYPE0, _CASE0, ...)   \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_10(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_14(_TYPE0, _CASE0, ...)   \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_12(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_16(_TYPE0, _CASE0, ...)   \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_14(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_18(_TYPE0, _CASE0, ...)   \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_16(__VA_ARGS__)
#define _ZTDC_CASCADING_GENERIC_20(_TYPE0, _CASE0, ...)   \
	_ZTDC_CASCADING_GENERIC_TYPICAL_CASE(_TYPE0, _CASE0) \
	_ZTDC_CASCADING_GENERIC_18(__VA_ARGS__)

#define _ZTDC_CASCADING_GENERIC_SELECT(_FUN20, _ERR19, _FUN18, _ERR17, _FUN16, _ERR15, _FUN14, _ERR13, _FUN12, _ERR11, \
     _FUN10, _ERR9, _FUN8, _ERR7, _FUN6, _ERR5, _FUN4, _ERR3, _FUN2, _ERR1, _FUN_TARGET, ...)                          \
	_FUN_TARGET

#define ZTDC_CASCADING_GENERIC(_CONTROLLING_EXPRESSION, ...)                                                           \
	([&]() {                                                                                                          \
		using _ZTDC_RAW_UNQUAL_CONTROL_TYPE = ::ztd::remove_cvref_t<decltype(_CONTROLLING_EXPRESSION)>;              \
		using _ZTDC_CONTROL_TYPE            = ::std::conditional_t<::std::is_array_v<_ZTDC_RAW_UNQUAL_CONTROL_TYPE>, \
               ::std::remove_extent_t<_ZTDC_RAW_UNQUAL_CONTROL_TYPE>*, _ZTDC_RAW_UNQUAL_CONTROL_TYPE>;      \
		if constexpr (false) { }                                                                                     \
		_ZTDC_CASCADING_GENERIC_SELECT(__VA_ARGS__, _ZTDC_CASCADING_GENERIC_20, _ZTDC_WRONG_COUNT_ERR,               \
		     _ZTDC_CASCADING_GENERIC_18, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_16, _ZTDC_WRONG_COUNT_ERR,   \
		     _ZTDC_CASCADING_GENERIC_14, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_12, _ZTDC_WRONG_COUNT_ERR,   \
		     _ZTDC_CASCADING_GENERIC_10, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_8, _ZTDC_WRONG_COUNT_ERR,    \
		     _ZTDC_CASCADING_GENERIC_6, _ZTDC_WRONG_COUNT_ERR, _ZTDC_CASCADING_GENERIC_4, _ZTDC_WRONG_COUNT_ERR,     \
		     _ZTDC_CASCADING_GENERIC_2, _ZTDC_WRONG_COUNT_ERR)                                                       \
		(__VA_ARGS__);                                                                                               \
	}())
#endif

#endif
