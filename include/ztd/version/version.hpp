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

#ifndef ZTD_VERSION_VERSION_HPP
#define ZTD_VERSION_VERSION_HPP

#include <cstddef>
#include <cstdint>
#include <climits>
#include <type_traits>

#define ZTD_VERSION_MAJOR 0
#define ZTD_VERSION_MINOR 0
#define ZTD_VERSION_PATCH 0
#define ZTD_VERSION_STRING "0.0.0"
#define ZTD_VERSION_VERSION ((ZTD_VERSION_MAJOR * 100'000) + (ZTD_VERSION_MINOR * 100) + (ZTD_VERSION_PATCH))

#define ZTD_IS_ON(OP_SYMBOL) ((3 OP_SYMBOL 3) != 0)
#define ZTD_IS_OFF(OP_SYMBOL) ((3 OP_SYMBOL 3) == 0)
#define ZTD_IS_DEFAULT_ON(OP_SYMBOL) ((3 OP_SYMBOL 3) > 3)
#define ZTD_IS_DEFAULT_OFF(OP_SYMBOL) ((3 OP_SYMBOL 3 OP_SYMBOL 3) < 0)

#define ZTD_ON |
#define ZTD_OFF ^
#define ZTD_DEFAULT_ON +
#define ZTD_DEFAULT_OFF -

// clang-format off

#if defined(ZTD_HAS_INCLUDE)
	#define ZTD_HAS_INCLUDE_I_(...) ZTD_HAS_INCLUDE(__VA_ARGS__)
#elif defined(__has_include)
	#define ZTD_HAS_INCLUDE_I_(...) __has_include(__VA_ARGS__)
#else
	#define ZTD_HAS_INCLUDE_I_(...) 0
#endif

#define ZTD_TOKEN_TO_STRING_POST_EXPANSION_I_(__TOK) #__TOK
#define ZTD_TOKEN_TO_STRING_I_(__TOK) ZTD_TOKEN_TO_STRING_POST_EXPANSION_I_(__TOK)

#if ZTD_HAS_INCLUDE_I_(<version>)
	// Can check __has_include and we have the C++20 <version> header
	#include <version>
#endif

#if defined(__clang__)
	#define ZTD_COMPILER_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_CLANG_I_ ZTD_OFF
#endif

#if defined(__GNUC__)
	#define ZTD_COMPILER_GCC_I_ ZTD_ON
#else
	#define ZTD_COMPILER_GCC_I_ ZTD_OFF
#endif

#if defined (_MSC_VER)
	#define ZTD_COMPILER_VCXX_I_ ZTD_ON
#else
	#define ZTD_COMPILER_VCXX_I_ ZTD_OFF
#endif

#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) && ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_OFF
#endif

#if defined(__MINGW32__)
	#define ZTD_COMPILER_MINGW_I_ ZTD_ON
#else
	#define ZTD_COMPILER_MINGW_I_ ZTD_OFF
#endif

#if defined(__GLIBCXX__)
	#define ZTD_LIBSTDCXX_I_ ZTD_ON
#else
	#define ZTD_LIBSTDCXX_I_ ZTD_OFF
#endif

#if defined(_LIBCPP_VERSION)
	#define ZTD_LIBCXX_I_ ZTD_ON
#else
	#define ZTD_LIBCXX_I_ ZTD_OFF
#endif

#if defined (_YVALS_CORE_H_) // Volatile definition; would be nice if VC++ exposed some documented macros...
	#define ZTD_LIBVCXX_I_ ZTD_ON
#else
	#define ZTD_LIBVCXX_I_ ZTD_OFF
#endif

#if defined(_WIN32)
	#define ZTD_PLATFORM_WINDOWS_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_WINDOWS_I_ ZTD_OFF
#endif // Windows

#if defined(__CYGWIN__)
	#define ZTD_PLATFORM_CYGWIN_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_CYGWIN_I_ ZTD_OFF
#endif // Cygwin shenanigans

#if defined(__MVS__)
	#define ZTD_PLATFORM_ZEDOS_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_ZEDOS_I_ ZTD_OFF
#endif // IBM's Z/OS

#if defined(__STDC_HOSTED__)
	#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_OFF
#else
	#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_ON
#endif

#if defined(_AIX)
	// We are on the AIX platform
	#define ZTD_PLATFORM_AIX_I_ ZTD_ON
#else
	// We are not on the AIX platform
	#define ZTD_PLATFORM_AIX_I_ ZTD_OFF
#endif // IBM's AIX

#if defined(ZTD_PLATFORM_UNKNOWN_CHECK)
	#if (ZTD_PLATFORM_UNKNOWN_CHECK != 0)
		#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_OFF
	#endif
#else
	#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_OFF
#endif

#if defined(sun) || defined(__sun)
	#if defined(__SVR4) || defined(__svr4__)
		// Solaris
		#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_OFF
		#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_ON
	#else
		// SunOS
		#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_ON
		#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_OFF
	#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_OFF
#endif // SunOS and Solaris

#if defined(__unix) || defined(__unix__)
	#define ZTD_PLATFORM_UNIX_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_UNIX_I_ ZTD_DEFAULT_OFF
#endif // UNIX platforms

#if defined(__linux) || defined(__linux__) || defined(linux)
	#define ZTD_PLATFORM_LINUX_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_LINUX_I_ ZTD_DEFAULT_OFF
#endif // Linux platforms

#if defined(macintosh) || defined(Macintosh) || (__APPLE__)
	#define ZTD_PLATFORM_MAC_OS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_MAC_OS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_DEBUG)
	#if (ZTD_DEBUG != 0)
		#define ZTD_DEBUG_I_ ZTD_ON
	#else
		#define ZTD_DEBUG_I_ ZTD_OFF
	#endif
#elif !defined(NDEBUG)
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) && defined(_DEBUG)
		#define ZTD_DEBUG_I_ ZTD_DEFAULT_ON
	#elif (ZTD_IS_ON(ZTD_COMPILER_CLANG_I_) || ZTD_IS_ON(ZTD_COMPILER_GCC_I_)) && !defined(__OPTIMIZE__)
		#define ZTD_DEBUG_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_DEBUG_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_DEBUG_I_ ZTD_DEFAULT_OFF
#endif // We are in a debug mode of some sort

#if defined(ZTD_WCHAR_T_UTF32_COMPATIBLE)
	#if (ZTD_WCHAR_T_UTF32_COMPATIBLE != 0)
		#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_ON
	#else
		#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_OFF
	#endif
#elif defined(__STDC_ISO_10646__) && (__STDC_ISO_10646__ != 0)
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0x001FFFFF) && ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_CHAR8_T)
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_ON
	#define ZTD_CHAR8_T_I_ ZTD_CHAR8_T
#elif defined(__cpp_char8_t)
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_DEFAULT_OFF
	#define ZTD_CHAR8_T_I_ char8_t
#else
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_DEFAULT_OFF
	#define ZTD_CHAR8_T_I_ unsigned char
#endif // char8_t defined by the user

#if defined(__cpp_char8_t)
	#define ZTD_NATIVE_CHAR8_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_NATIVE_CHAR8_T_I_ ZTD_DEFAULT_OFF
#endif // char8_t exists natively (C++) - C proposal in WG14 still in progress

#if defined(ZTD_BUILD)
	#if (ZTD_BUILD != 0)
		#define ZTD_BUILD_I_ ZTD_ON
	#else
		#define ZTD_BUILD_I_ ZTD_OFF
	#endif
#else
	#define ZTD_BUILD_I_ ZTD_DEFAULT_OFF
#endif // Building or not

#if defined(ZTD_DLL) && (ZTD_DLL != 0)
	#define ZTD_DLL_I_ ZTD_ON
#else
	#define ZTD_DLL_I_ ZTD_OFF
#endif // Building or not

#if defined(ZTD_HEADER_ONLY)
	#if (ZTD_HEADER_ONLY != 0)
		#define ZTD_HEADER_ONLY_I_ ZTD_ON
	#else
		#define ZTD_HEADER_ONLY_I_ ZTD_OFF
	#endif
#else
	#define ZTD_HEADER_ONLY_I_ ZTD_DEFAULT_OFF
#endif // Header only library

#if defined(ZTD_INLINE_BUILD)
	#if (ZTD_INLINE_BUILD != 0)
		#define ZTD_INLINE_BUILD_I_ ZTD_ON
	#else
		#define ZTD_INLINE_BUILD_I_ ZTD_OFF
	#endif
#else
	#define ZTD_INLINE_BUILD_I_ ZTD_DEFAULT_OFF
#endif // Header only library

#if !defined(ZTD_FUNCTION_LINKAGE)
	#if defined(__cplusplus)
		// C++
		#define ZTD_FUNCTION_LINKAGE_I_ extern "C"
	#else
		// normal
		#define ZTD_FUNCTION_LINKAGE_I_
	#endif // C++ or not
#else
	#define ZTD_FUNCTION_LINKAGE_I_ ZTD_FUNCTION_LINKAGE
#endif // Linkage specification

#if defined(ZTD_API_LINKAGE)
	#define ZTD_API_LINKAGE_I_ ZTD_API_LINKAGE
#else
	#if ZTD_IS_ON(ZTD_DLL_I_)
		#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) || ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_) || ZTD_IS_ON(ZTD_PLATFORM_CYGWIN_I_)
			// MSVC Compiler; or, Windows, or Cygwin platforms
			#if ZTD_IS_ON(ZTD_BUILD_I_)
				// Building the library
				#if ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
					// Using GCC
					#define ZTD_API_LINKAGE_I_ __attribute__((dllexport))
				#else
					// Using Clang, MSVC, etc...
					#define ZTD_API_LINKAGE_I_ __declspec(dllexport)
				#endif
			#else
				#if ZTD_IS_ON(ZTD_PLATFORM_GCC_I_)
					#define ZTD_API_LINKAGE_I_ __attribute__((dllimport))
				#else
					#define ZTD_API_LINKAGE_I_ __declspec(dllimport)
				#endif
			#endif
		#else
			// extern if building normally on non-MSVC
			#define ZTD_API_LINKAGE_I_ extern
		#endif
	#elif ZTD_IS_ON(ZTD_INLINE_BUILD_I_)
		// Built-in library, like how stb typical works
		#if ZTD_IS_ON(ZTD_HEADER_ONLY_I_)
			// Header only, so functions are defined "inline"
			#define ZTD_API_LINKAGE_I_ inline
		#else
			// Not header only, so seperately compiled files
			#define ZTD_API_LINKAGE_I_ extern
		#endif
	#else
		// Normal static library
		#if defined(__cplusplus)
			#define ZTD_API_LINKAGE_I_
		#else
			#define ZTD_API_LINKAGE_I_ extern
		#endif
	#endif // DLL or not
#endif // Build definitions

#if defined (ZTD_ALIGNED_OPERATOR_NEW)
	#if (ZTD_ALIGNED_OPERATOR_NEW != 0)
		#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_ON
	#else
		#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_OFF
	#endif
#elif defined(__cpp_aligned_new)
	#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_ON
#elif defined(__cplusplus) && __cplusplus > 201603L
	#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_OFF
#endif // C++ operator new, with alignment parameter

#if defined(ZTD_CONCEPTS)
	#if (ZTD_CONCEPTS != 0)
		#define ZTD_CONCEPTS_I_ ZTD_ON
	#else
		#define ZTD_CONCEPTS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	// clang is busted right now!
	// taking bets: Clang 14 is when it'll get fixed!
	#if (__clang_major__ > 14)
		#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_OFF
	#endif
#elif defined(__cpp_concepts) && (__cpp_concepts >= 201907LL)
	#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_UCHAR)
	#if (ZTD_UCHAR != 0)
		#define ZTD_UCHAR_I_ ZTD_ON
	#else
		#define ZTD_UCHAR_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<uchar.h>)
	#define ZTD_UCHAR_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_UCHAR_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_CUCHAR)
	#if (ZTD_CUCHAR != 0)
		#define ZTD_CUCHAR_I_ ZTD_ON
	#else
		#define ZTD_CUCHAR_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<cuchar>)
	#define ZTD_CUCHAR_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_CUCHAR_I_ ZTD_DEFAULT_OFF
#endif

#if ZTD_IS_ON(ZTD_CUCHAR_I_)
	#define ZTD_UCHAR_ACCESSOR_I_ ::std::
#else
	#define ZTD_UCHAR_ACCESSOR_I_ ::
#endif

#if defined(ZTD_LANGINFO)
	#if (ZTD_LANGINFO != 0)
		#define ZTD_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_LANGINFO_I_ ZTD_OFF
	#endif
#else
	#if ZTD_HAS_INCLUDE_I_(<langinfo.h>)
		#define ZTD_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_LANGINFO_I_ ZTD_DEFAULT_OFF
	#endif
#endif // langinfo POSIX

#if defined(ZTD_NL_LANGINFO)
	#if (ZTD_NL_LANGINFO != 0)
		#define ZTD_NL_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_NL_LANGINFO_I_ ZTD_OFF
	#endif
#else
	#if ZTD_HAS_INCLUDE_I_(<nl_langinfo.h>)
		#define ZTD_NL_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_NL_LANGINFO_I_ ZTD_DEFAULT_OFF
	#endif
#endif // nl_langinfo POSIX

#if defined(ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION)
	#if (ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION != 0)
		#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_ON
	#else
		#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_NL_LANGINFO_I_) && (ZTD_IS_ON(ZTD_PLATFORM_ZEDOS_I_) || ZTD_IS_ON(ZTD_PLATFORM_AIX_I_))
	#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_ON
#else
	#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_DEFAULT_OFF
#endif // Locale-dependent wchar_t detection

#if defined (__has_cpp_attribute) && (__has_cpp_attribute(nodiscard) != 0L)
	#if __has_cpp_attribute(nodiscard) >= 201907L
		#define ZTD_NODISCARD_MESSAGE_I_(__message) [[nodiscard(__message)]]
		#define ZTD_NODISCARD_I_ [[nodiscard]]
	#else
		#define ZTD_NODISCARD_MESSAGE_I_(__message) [[nodiscard]]
		#define ZTD_NODISCARD_I_ [[nodiscard]]
	#endif
#elif defined (__has_c_attribute) && (__has_c_attribute(nodiscard) != 0L)
	#define ZTD_NODISCARD_MESSAGE_I_(__message) [[nodiscard(__message)]]
	#define ZTD_NODISCARD_I_ [[nodiscard]]
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) && defined(_Check_return_)
		#define ZTD_NODISCARD_MESSAGE_I_(__message) _Check_return_
		#define ZTD_NODISCARD_I_ _Check_return_
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_) || ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
		#define ZTD_NODISCARD_MESSAGE_I_(__message) __attribute__((warn_unused_result))
		#define ZTD_NODISCARD_I_ __attribute__((warn_unused_result))
	#else
		// :c
		#define ZTD_NODSICARD_I_(__message)
		#define ZTD_NODISCARD_I_
	#endif
#endif

#if defined(ZTD_STD_TEXT_ENCODING_ID)
	#if (ZTD_STD_TEXT_ENCODING_ID != 0)
		#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_ON
	#else
		#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_text_encoding_id)
	#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_IS_NOTHROW_CONVERTIBLE)
	#if (ZTD_STD_LIBRARY_IS_NOTHROW_CONVERTIBLE != 0)
		#define ZTD_STD_LIBRARY_IS_NOTHROW_CONVERTIBLE_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_IS_NOTHROW_CONVERTIBLE_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_is_nothrow_convertible)
	#define ZTD_STD_LIBRARY_IS_NOTHROW_CONVERTIBLE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_IS_NOTHROW_CONVERTIBLE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_TEXT_ENCODING_ID)
	#if (ZTD_STD_LIBRARY_TEXT_ENCODING_ID != 0)
		#define ZTD_STD_LIBRARY_TEXT_ENCODING_ID_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_TEXT_ENCODING_ID_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_text_encoding_id)
	#define ZTD_STD_LIBRARY_TEXT_ENCODING_ID_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_TEXT_ENCODING_ID_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS)
	#if (ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS != 0)
		#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_constexpr_algorithms)
	#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_RANGES)
	#if (ZTD_STD_LIBRARY_RANGES != 0)
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	#if 0
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_ON
	#else
		// clang's concepts implementation, which powers ranges, is busted!
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_OFF
	#endif
#elif defined(__cpp_lib_ranges)
	#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_ENDIAN)
	#if (ZTD_STD_LIBRARY_ENDIAN != 0)
		#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_endian)
	#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_CONCEPTS)
	#if (ZTD_STD_LIBRARY_CONCEPTS_I_ != 0)
		#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_concepts)
	#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_DEFAULT_OFF
#endif

#if defined (__has_cpp_attribute) && (__has_cpp_attribute(deprecated) != 0L)
	#define ZTD_DEPRECATED_I_(__message) [[deprecated(__message)]]
#elif defined (__has_c_attribute) && (__has_c_attribute(deprecated) != 0L)
	#define ZTD_DEPRECATED_I_(__message) [[deprecated(__message)]]
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_)
		#define ZTD_DEPRECATED_I_(__message) declspec(deprecated)
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_) || ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
		#define ZTD_DEPRECATED_I_(__message) __attribute__((warn_unused_result))
	#else
		// :c
		#define ZTD_DEPRECATED_I_(__message)
	#endif
#endif

#if defined(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
	#if (ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED != 0)
		#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_is_constant_evaluated)
	#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_TO_ADDRESS)
	#if (ZTD_STD_LIBRARY_TO_ADDRESS != 0)
		#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_to_address)
	#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_CONSTEXPR_UTILITIES)
	#if (ZTD_STD_LIBRARY_CONSTEXPR_UTILITIES != 0)
		#define ZTD_STD_LIBRARY_CONSTEXPR_UTILITIES_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONSTEXPR_UTILITIES_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_constexpr_utility)
	#define ZTD_STD_LIBRARY_CONSTEXPR_UTILITIES_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONSTEXPR_UTILITIES_I_ ZTD_DEFAULT_OFF
#endif

#if defined (ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED)
	#if (ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED != 0)
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ constexpr
	#else
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ 
	#endif
#elif ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_)
	#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ constexpr
#else
	#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ 
#endif

#if defined(ZTD_STD_LIBRARY_SPACESHIP_COMPARE)
	#if (ZTD_STD_LIBRARY_SPACESHIP_COMPARE != 0)
		#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_three_way_comparison)
	#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_ON
#else
	#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_STARTS_ENDS_WITH)
	#if (ZTD_STD_LIBRARY_STARTS_ENDS_WITH != 0)
		#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_ON
	#endif
#elif defined(__cpp_lib_starts_ends_with)
	#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_STRING_CONTAINS)
	#if (ZTD_STD_LIBRARY_STRING_CONTAINS != 0)
		#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_ON
	#endif
#elif defined(__cpp_lib_string_contains)
	#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_SPAN)
	#if (ZTD_STD_LIBRARY_SPAN != 0)
		#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_ON
	#endif
#elif defined(__cpp_lib_span)
	#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG)
	#if (ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG != 0)
		#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_LIBVCXX_I_) && ZTD_IS_ON(ZTD_STD_LIBRARY_CONCEPTS_I_)
	#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_STD_LIBRARY_CONCEPTS_I_) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES_I_)
	#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_DEBUG_ITERATORS)
	#if (ZTD_STD_LIBRARY_DEBUG_ITERATORS != 0)
		#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_LIBVCXX_I_) && (defined(_ITERATOR_DEBUG_LEVEL) && (_ITERATOR_DEBUG_LEVEL > 0))
	#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST)
	#if (ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST != 0)
		#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_LIBVCXX_I_) && defined(_ITERATOR_DEBUG_LEVEL) && (_ITERATOR_DEBUG_LEVEL > 0)
	#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE)
	#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_)
		// "The reserve value specifies the total stack allocation in virtual memory. 
		// For ARM, x86 and x64 machines, the default stack size is 1 MB."
		// ...
		// "For ARM, x86 and x64 machines, the default commit value is 4 KB"
		// https://docs.microsoft.com/en-us/cpp/build/reference/stack-stack-allocations?view=vs-2019
		// Uses: (1024 * 64)
		#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ (65536)
	#elif ZTD_IS_ON(ZTD_PLATFORM_APPLE_I_)
		// "  -stack_size size
		//     Specifies the maximum stack size for the main thread in a program.  Without this option a
		//     program has a 8MB stack.  The argument size is a hexadecimal number with an optional lead-
		//     ing 0x. The size should be a multiple of the architecture's page size (4KB or 16KB).
		// ld(1) manpage on Mac OS
		// Uses: ((1024 * 64) * 8)
		#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ (524288)
	#elif ZTD_IS_ON(ZTD_PLATFORM_LINUX_I_) || ZTD_IS_ON(ZTD_PLATFORM_UNIX_I_)
		// "Here is the vale for a few architectures:"
		//
		//    │Architecture │ Default stack size │
		//    ├─────────────┼────────────────────┤
		//    │i386         │               2 MB │
		//    ├─────────────┼────────────────────┤
		//    │IA-64        │              32 MB │
		//    ├─────────────┼────────────────────┤
		//    │PowerPC      │               4 MB │
		//    ├─────────────┼────────────────────┤
		//    │S/390        │               2 MB │
		//    ├─────────────┼────────────────────┤
		//    │Sparc-32     │               2 MB │
		//    ├─────────────┼────────────────────┤
		//    │Sparc-64     │               4 MB │
		//    ├─────────────┼────────────────────┤
		//    │x86_64       │               2 MB │
		//    └─────────────┴────────────────────┘
		// http://man7.org/linux/man-pages/man3/pthread_create.3.html
		// Uses: (1024 * 128)
		#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ (131072)
	#else
		// Tiny embbeded compiler shenanigans??
		// Uses: (1024 * 2)
		#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ (2048)
	#endif // MSVC vs. others
#endif // Intermediate buffer sizing

#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_SIZE_I_(...) (ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ / sizeof(__VA_ARGS__))

#include <ztd/version/detail/build_version.hpp>

#include <ztd/prologue.hpp>
#include <ztd/epilogue.hpp>

#endif // ZTD_VERSION_VERSION_HPP
