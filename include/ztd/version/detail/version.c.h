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

#ifndef ZTD_VERSION_DETAIL_VERSION_C_H
#define ZTD_VERSION_DETAIL_VERSION_C_H

#include <ztd/version/detail/is.h>
#include <ztd/version/detail/vc++.codepage_to_name.h>

// clang-format off

#if ZTD_IS_ON(ZTD_CXX)
	#include <cstddef>
	#include <cstdint>
	#include <climits>
	#if ZTD_HAS_INCLUDE_I_(<version>)
		// Can check __has_include and we have the C++20 <version> header
		#include <version>
	#endif
#else
	#include <stddef.h>
	#include <stdint.h>
	#include <limits.h>
#endif

#if defined(__clang__)
	#define ZTD_COMPILER_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_CLANG_I_ ZTD_OFF
#endif

#if ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#if defined(__apple_build_version__)
		// Clang compiler built for Apple
		#define ZTD_COMPILER_APPLE_CLANG_I_ ZTD_ON
	#else
		#define ZTD_COMPILER_APPLE_CLANG_I_ ZTD_OFF
	#endif
#else
	#define ZTD_COMPILER_APPLE_CLANG_I_ ZTD_OFF
#endif

#if defined(__clang__)
	#define ZTD_COMPILER_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_CLANG_I_ ZTD_OFF
#endif

#if defined(__TINYC__)
	#define ZTD_COMPILER_TINYCC_I_ ZTD_ON
#else
	#define ZTD_COMPILER_TINYCC_I_ ZTD_OFF
#endif

#if defined(__GNUC__) && ZTD_IS_OFF(ZTD_COMPILER_CLANG)
	#define ZTD_COMPILER_GCC_I_ ZTD_ON
#else
	#define ZTD_COMPILER_GCC_I_ ZTD_OFF
#endif

#if defined(__GNUC__)
	#define ZTD_COMPILER_ANY_GCC_I_ ZTD_ON
#else
	#define ZTD_COMPILER_ANY_GCC_I_ ZTD_OFF
#endif

#if defined (_MSC_VER)
	#define ZTD_COMPILER_VCXX_I_ ZTD_ON
#else
	#define ZTD_COMPILER_VCXX_I_ ZTD_OFF
#endif

#if defined(ZTD_COMPILER_VCXX_CLANG)
	#if (ZTD_COMPILER_VCXX_CLANG) != 0
		#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_ON
	#else
		#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX) && ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_OFF
#endif

#if defined(ZTD_COMPILER_MINGW)
	#if (ZTD_COMPILER_MINGW) != 0
		#define ZTD_COMPILER_MINGW_I_ ZTD_ON
	#else
		#define ZTD_COMPILER_MINGW_I_ ZTD_OFF
	#endif
#elif defined(__MINGW32__)
	#define ZTD_COMPILER_MINGW_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_COMPILER_MINGW_I_ ZTD_DEFAULT_OFF
#endif

#if defined (ZTD_CXX_VERSION)
	#define ZTD_CXX_VERSION_I_ ZTD_CXX_VERSION
#elif ZTD_IS_ON(ZTD_CXX)
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX) && defined(_MSVC_LANG)
		#define ZTD_CXX_VERSION_I_ _MSVC_LANG
	#else
		#define ZTD_CXX_VERSION_I_ __cplusplus
	#endif
#else
	#define ZTD_CXX_VERSION_I_ 0
#endif

#if defined (ZTD_C_VERSION)
	#define ZTD_C_VERSION_I_ ZTD_C_VERSION
#elif ZTD_IS_ON(ZTD_C)
	#define ZTD_C_VERSION_I_ __STDC_VERSION__
#else
	#define ZTD_C_VERSION_I_ 0
#endif

#if defined(__GLIBCXX__)
	#define ZTD_CXX_STDLIB_STDCXX_I_ ZTD_ON
#else
	#define ZTD_CXX_STDLIB_STDCXX_I_ ZTD_OFF
#endif

#if defined(_LIBCPP_VERSION)
	#define ZTD_CXX_STDLIB_CXX_I_ ZTD_ON
#else
	#define ZTD_CXX_STDLIB_CXX_I_ ZTD_OFF
#endif

#if defined(ZTD_CXX_STDLIB_VCXX)
	#if (ZTD_CXX_STDLIB_VCXX) != 0
		#define ZTD_CXX_STDLIB_VCXX_I_ ZTD_ON
	#else
		#define ZTD_CXX_STDLIB_VCXX_I_ ZTD_OFF
	#endif
#elif defined (_YVALS_CORE_H_)
// Volatile definition;
// would be nice if VC++ exposed some documented macros...
	#define ZTD_CXX_STDLIB_VCXX_I_ ZTD_ON
#else
	#define ZTD_CXX_STDLIB_VCXX_I_ ZTD_OFF
#endif

#if defined(ZTD_C_STDLIB_VCXX)
	#if (ZTD_C_STDLIB_VCXX) != 0
		#define ZTD_C_STDLIB_VCXX_I_ ZTD_ON
	#else
		#define ZTD_C_STDLIB_VCXX_I_ ZTD_OFF
	#endif
#elif defined (_YVALS_CORE_H_)
// Volatile definition;
// would be nice if VC++ exposed some documented macros...
	#define ZTD_C_STDLIB_VCXX_I_ ZTD_ON
#else
	#define ZTD_C_STDLIB_VCXX_I_ ZTD_OFF
#endif

#if defined(ZTD_C_STDLIB_GLIBC)
	#if (ZTD_C_STDLIB_GLIBC) != 0
		#define ZTD_C_STDLIB_GLIBC_I_ ZTD_ON
	#else
		#define ZTD_C_STDLIB_GLIBC_I_ ZTD_OFF
	#endif
#elif defined (__GLIBC__)
// Volatile definition;
// would be nice if VC++ exposed some documented macros...
	#define ZTD_C_STDLIB_GLIBC_I_ ZTD_ON
#else
	#define ZTD_C_STDLIB_GLIBC_I_ ZTD_OFF
#endif

#if defined(ZTD_C_STDLIB_BSD)
	#if (ZTD_C_STDLIB_BSD) != 0
		#define ZTD_C_STDLIB_BSD_I_ ZTD_ON
	#else
		#define ZTD_C_STDLIB_BSD_I_ ZTD_OFF
	#endif
#elif defined (__BSD_VISIBLE)
// Volatile definition;
// would be nice if VC++ exposed some documented macros...
	#define ZTD_C_STDLIB_BSD_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_C_STDLIB_BSD_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_C_STDLIB_MUSL)
	#if (ZTD_C_STDLIB_MUSL) != 0
		#define ZTD_C_STDLIB_MUSL_I_ ZTD_ON
	#else
		#define ZTD_C_STDLIB_MUSL_I_ ZTD_OFF
	#endif
#elif ZTD_IS_OFF(ZTD_C_STDLIB_GLIBC) && ZTD_IS_OFF(ZTD_C_STDLIB_BSD) && defined (_REDIR)
// Volatile definition;
// would be nice if VC++ exposed some documented macros...
	#define ZTD_C_STDLIB_MUSL_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_C_STDLIB_MUSL_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_C_STDLIB_UCRT)
	#if (ZTD_C_STDLIB_UCRT) != 0
		#define ZTD_C_STDLIB_UCRT_I_ ZTD_ON
	#else
		#define ZTD_C_STDLIB_UCRT_I_ ZTD_OFF
	#endif
#elif (ZTD_IS_ON(ZTD_COMPILER_MINGW) && defined(_UCRT))
	#define ZTD_C_STDLIB_UCRT_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_C_STDLIB_UCRT_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_WINDOWS)
	#if (ZTD_PLATFORM_WINDOWS != 0)
		#define ZTD_PLATFORM_WINDOWS_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_WINDOWS_I_ ZTD_ON
	#endif
#elif defined(_WIN32)
	#define ZTD_PLATFORM_WINDOWS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_WINDOWS_I_ ZTD_DEFAULT_OFF
#endif // Windows

#if defined(__CYGWIN__)
	#define ZTD_PLATFORM_CYGWIN_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_CYGWIN_I_ ZTD_OFF
#endif // Cygwin shenanigans

#if defined(ZTD_PLATFORM_ZEDOS)
	#if (ZTD_PLATFORM_ZEDOS != 0)
		#define ZTD_PLATFORM_ZEDOS_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_ZEDOS_I_ ZTD_OFF
	#endif
#elif defined(__MVS__)
	#define ZTD_PLATFORM_ZEDOS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_ZEDOS_I_ ZTD_DEFAULT_OFF
#endif // IBM's Z/OS

#if defined(ZTD_PLATFORM_FREESTANDING)
	#if (ZTD_PLATFORM_FREESTANDING != 0)
		#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_OFF
	#endif
#elif !defined(__STDC_HOSTED__)
	#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_AIX)
	#if (ZTD_PLATFORM_AIX != 0)
		#define ZTD_PLATFORM_AIX_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_AIX_I_ ZTD_OFF
	#endif
#elif defined(_AIX)
	// We are on the AIX platform
	#define ZTD_PLATFORM_AIX_I_ ZTD_DEFAULT_ON
#else
	// We are not on the AIX platform
	#define ZTD_PLATFORM_AIX_I_ ZTD_DEFAULT_OFF
#endif // IBM's AIX

#if defined(ZTD_PLATFORM_SOLARIS)
	#if (ZTD_PLATFORM_SOLARIS != 0)
		#define ZTD_PLATFORM_SOLARIS_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_SOLARIS_I_ ZTD_OFF
	#endif
#elif (defined(sun) || defined(__sun)) && (defined(__SVR4) || defined(__svr4__))
	#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_OFF
#endif // Solaris

#if defined(ZTD_PLATFORM_SUNOS)
	#if (ZTD_PLATFORM_SUNOS_I_ != 0)
		#define ZTD_PLATFORM_SUNOS_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_SUNOS_I_ ZTD_OFF
	#endif
#elif (defined(sun) || defined(__sun)) && (!defined(__SVR4) && !defined(__svr4__))
	#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_OFF
#endif // SunOS

#if defined(ZTD_PLATFORM_ANDROID)
	#if (ZTD_PLATFORM_ANDROID_I_ != 0)
		#define ZTD_PLATFORM_ANDROID_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_ANDROID_I_ ZTD_OFF
	#endif
#elif defined(__ANDROID_API__) && (__ANDROID_API__ > 0)
	#define ZTD_PLATFORM_ANDROID_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_ANDROID_I_ ZTD_DEFAULT_OFF
#endif // Android (NDK)

#if defined(ZTD_PLATFORM_ANDROID_VERSION)
	#define ZTD_PLATFORM_ANDROID_I_ ZTD_PLATFORM_ANDROID_VERSION
#elif ZTD_IS_ON(ZTD_PLATFORM_ANDROID)
	#define ZTD_PLATFORM_ANDROID_VERSION_I_ __ANDROID_API__ 
#else
	#define ZTD_PLATFORM_ANDROID_VERSION_I_ 0
#endif

#if defined(ZTD_PLATFORM_UNIX)
	#if (ZTD_PLATFORM_UNIX != 0)
		#define ZTD_PLATFORM_UNIX_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_UNIX_I_ ZTD_OFF
	#endif
#elif defined(__unix) || defined(__unix__)
	#define ZTD_PLATFORM_UNIX_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_UNIX_I_ ZTD_DEFAULT_OFF
#endif // UNIX platforms


#if defined(ZTD_HEADER_SYS_THR_H)
	#if (ZTD_HEADER_SYS_THR_H != 0)
		#define ZTD_HEADER_SYS_THR_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_SYS_THR_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<sys/thr.h>)
	#define ZTD_HEADER_SYS_THR_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_SYS_THR_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_SYS_LWP_H)
	#if (ZTD_HEADER_SYS_LWP_H != 0)
		#define ZTD_HEADER_SYS_LWP_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_SYS_LWP_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<sys/lwp.h>)
	#define ZTD_HEADER_SYS_LWP_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_SYS_LWP_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_UNISTD_H)
	#if (ZTD_HEADER_UNISTD_H != 0)
		#define ZTD_HEADER_UNISTD_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_UNISTD_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<unistd.h>)
	#define ZTD_HEADER_UNISTD_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_UNISTD_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_SYS_SYSCALL_H)
	#if (ZTD_HEADER_SYS_SYSCALL_H != 0)
		#define ZTD_HEADER_SYS_SYSCALL_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_SYS_SYSCALL_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<sys/syscall.h>)
	#define ZTD_HEADER_SYS_SYSCALL_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_SYS_SYSCALL_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_SYS_UIO_H)
	#if (ZTD_HEADER_SYS_UIO_H != 0)
		#define ZTD_HEADER_SYS_UIO_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_SYS_UIO_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<sys/uio.h>)
	#define ZTD_HEADER_SYS_UIO_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_SYS_UIO_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_SYS_TYPES_H)
	#if (ZTD_HEADER_SYS_TYPES_H != 0)
		#define ZTD_HEADER_SYS_TYPES_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_SYS_TYPES_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<sys/types.h>)
	#define ZTD_HEADER_SYS_TYPES_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_SYS_TYPES_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_POSIX)
	#if (ZTD_PLATFORM_POSIX != 0)
		#define ZTD_PLATFORM_POSIX_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_POSIX_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_HEADER_UNISTD_H) && ZTD_IS_ON(ZTD_HEADER_SYS_TYPES_H)
	#define ZTD_PLATFORM_POSIX_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_POSIX_I_ ZTD_DEFAULT_OFF
#endif // POSIX platforms

#if defined(ZTD_PLATFORM_LINUX)
	#if (ZTD_PLATFORM_LINUX != 0)
		#define ZTD_PLATFORM_LINUX_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_LINUX_I_ ZTD_OFF
	#endif
#elif defined(__linux) || defined(__linux__) || defined(linux)
	#define ZTD_PLATFORM_LINUX_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_LINUX_I_ ZTD_DEFAULT_OFF
#endif // Linux platforms

#if defined(ZTD_PLATFORM_FREE_BSD)
	#if (ZTD_PLATFORM_FREE_BSD != 0)
		#define ZTD_PLATFORM_FREE_BSD_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_FREE_BSD_I_ ZTD_OFF
	#endif
#elif defined(__FreeBSD__)
	#define ZTD_PLATFORM_FREE_BSD_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_FREE_BSD_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_OPEN_BSD)
	#if (ZTD_PLATFORM_OPEN_BSD != 0)
		#define ZTD_PLATFORM_OPEN_BSD_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_OPEN_BSD_I_ ZTD_OFF
	#endif
#elif defined(__OpenBSD__)
	#define ZTD_PLATFORM_OPEN_BSD_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_OPEN_BSD_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_NET_BSD)
	#if (ZTD_PLATFORM_NET_BSD != 0)
		#define ZTD_PLATFORM_NET_BSD_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_NET_BSD_I_ ZTD_OFF
	#endif
#elif defined(__NetBSD__)
	#define ZTD_PLATFORM_NET_BSD_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_NET_BSD_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_DRAGONFLY_BSD)
	#if (ZTD_PLATFORM_DRAGONFLY_BSD != 0)
		#define ZTD_PLATFORM_DRAGONFLY_BSD_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_DRAGONFLY_BSD_I_ ZTD_OFF
	#endif
#elif defined(__DragonFly__)
	#define ZTD_PLATFORM_DRAGONFLY_BSD_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_DRAGONFLY_BSD_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_MAC_OS)
	#if (ZTD_PLATFORM_MAC_OS != 0)
		#define ZTD_PLATFORM_MAC_OS_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_MAC_OS_I_ ZTD_OFF
	#endif
#elif defined(macintosh) || defined(Macintosh) || (__APPLE__)
	#define ZTD_PLATFORM_MAC_OS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_PLATFORM_MAC_OS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_PLATFORM_UNKNOWN_CHECK)
	#if (ZTD_PLATFORM_UNKNOWN_CHECK != 0)
		#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_OFF
	#endif
#else
	#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_SIZE_64_BITS)
	#if (ZTD_SIZE_64_BITS != 0)
		#define ZTD_SIZE_64_BITS_I_ ZTD_ON
	#else
		#define ZTD_SIZE_64_BITS_I_ ZTD_OFF
	#endif
#elif SIZE_MAX <= 0xFFFFFFFF
	#define ZTD_SIZE_64_BITS_I_ ZTD_DEFAULT_OFF
#elif SIZE_MAX >= 0xFFFFFFFFFFFFFFFF
	#define ZTD_SIZE_64_BITS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_SIZE_64_BITS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_SIZE_32_BITS)
	#if (ZTD_SIZE_32_BITS != 0)
		#define ZTD_SIZE_32_BITS_I_ ZTD_ON
	#else
		#define ZTD_SIZE_32_BITS_I_ ZTD_OFF
	#endif
#elif SIZE_MAX <= 0xFFFF
	#define ZTD_SIZE_32_BITS_I_ ZTD_DEFAULT_OFF
#elif SIZE_MAX >= 0xFFFFFFFF
	#define ZTD_SIZE_32_BITS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_SIZE_32_BITS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD___INT128_T)
	#if (ZTD___INT128_T != 0)
		#define ZTD___INT128_T_I_ ZTD_ON
	#else
		#define ZTD___INT128_T_I_ ZTD_OFF
	#endif
#elif defined(__SIZEOF_INT128__)
	#define ZTD___INT128_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD___INT128_T_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_BITINT)
	#if (ZTD_BITINT != 0)
		#define ZTD_BITINT_I_ ZTD_ON
	#else
		#define ZTD_BITINT_I_ ZTD_OFF
	#endif
#elif defined(__BITINT_MAXWIDTH__) && __BITINT_MAXWIDTH__ > 0
	#define ZTD_BITINT_I_ ZTD_DEFAULT_ON
#elif defined(BITINT_MAXWIDTH) && BITINT_MAXWIDTH > 0
	#define ZTD_BITINT_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG) && (__clang_major__ >= 15)
	#define ZTD_BITINT_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BITINT_I_ ZTD_DEFAULT_OFF
#endif


#if defined(ZTD___UINT128_T)
	#if (ZTD___UINT128_T != 0)
		#define ZTD___UINT128_T_I_ ZTD_ON
	#else
		#define ZTD___UINT128_T_I_ ZTD_OFF
	#endif
#elif defined(__SIZEOF_INT128__)
	#define ZTD___UINT128_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD___UINT128_T_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD___INT256_T)
	#if (ZTD___INT256_T != 0)
		#define ZTD___INT256_T_I_ ZTD_ON
	#else
		#define ZTD___INT256_T_I_ ZTD_OFF
	#endif
#elif defined(__SIZEOF_INT256__)
	#define ZTD___INT256_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD___INT256_T_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD___UINT256_T)
	#if (ZTD___UINT256_T != 0)
		#define ZTD___UINT256_T_I_ ZTD_ON
	#else
		#define ZTD___UINT256_T_I_ ZTD_OFF
	#endif
#elif defined(__SIZEOF_INT256__)
	#define ZTD___UINT256_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD___UINT256_T_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STATEMENT_EXPRESSIONS)
	#if (ZTD_STATEMENT_EXPRESSIONS != 0)
		#define ZTD_STATEMENT_EXPRESSIONS_I_ ZTD_ON
	#else
		#define ZTD_STATEMENT_EXPRESSIONS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_TINYCC)
	#define ZTD_STATEMENT_EXPRESSIONS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STATEMENT_EXPRESSIONS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_AUTO_TYPE)
	#if (ZTD_AUTO_TYPE != 0)
		#define ZTD_AUTO_TYPE_I_ ZTD_ON
	#else
		#define ZTD_AUTO_TYPE_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_TINYCC)
	#define ZTD_AUTO_TYPE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_AUTO_TYPE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_DEBUG)
	#if (ZTD_DEBUG != 0)
		#define ZTD_DEBUG_I_ ZTD_ON
	#else
		#define ZTD_DEBUG_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX) && defined(_DEBUG)
	#define ZTD_DEBUG_I_ ZTD_DEFAULT_ON
#elif (ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_GCC)) && (defined(__OPTIMIZE__) && __OPTIMIZE__ != 0)
	#define ZTD_DEBUG_I_ ZTD_DEFAULT_ON
#elif (ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_GCC)) && (!defined(__OPTIMIZE__) || __OPTIMIZE__ == 0)
	#define ZTD_DEBUG_I_ ZTD_DEFAULT_ON
#elif defined(NDEBUG)
	#define ZTD_DEBUG_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_DEBUG_I_ ZTD_DEFAULT_OFF
#endif // We are in a debug mode of some sort

#if defined(ZTD_ASSERT_CHECKS)
	#if (ZTD_ASSERT_CHECKS != 0)
		#define ZTD_ASSERT_CHECKS_I_ ZTD_ON
	#else
		#define ZTD_ASSERT_CHECKS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_DEBUG)
	#define ZTD_ASSERT_CHECKS_I_ ZTD_ON
#else
	#define ZTD_ASSERT_CHECKS_I_ ZTD_OFF
#endif

#if defined(ZTD_CONSTEXPR_ASSERT_CHECKS)
	#if (ZTD_CONSTEXPR_ASSERT_CHECKS != 0)
		#define ZTD_CONSTEXPR_ASSERT_CHECKS_I_ ZTD_ON
	#else
		#define ZTD_CONSTEXPR_ASSERT_CHECKS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_DEBUG) || ZTD_IS_ON(ZTD_ASSERT_CHECKS)
	// C++17 and lower is worthless for constexpr code; don't bother
	#if defined(__cplusplus)  && (__cplusplus >= 202000L)
		#define ZTD_CONSTEXPR_ASSERT_CHECKS_I_ ZTD_ON
	#else
		#define ZTD_CONSTEXPR_ASSERT_CHECKS_I_ ZTD_OFF
	#endif
#else
	#define ZTD_CONSTEXPR_ASSERT_CHECKS_I_ ZTD_OFF
#endif

#if defined(ZTD_HEADER_NL_LANGINFO_H)
	#if (ZTD_HEADER_NL_LANGINFO_H != 0)
		#define ZTD_HEADER_NL_LANGINFO_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_NL_LANGINFO_H_I_ ZTD_OFF
	#endif
#else
	#if ZTD_HAS_INCLUDE_I_(<nl_langinfo.h>)
		#if ZTD_IS_ON(ZTD_PLATFORM_ANDROID)
			#if ZTD_USE(ZTD_PLATFORM_ANDROID_VERSION) >= 26
				#define ZTD_HEADER_NL_LANGINFO_H_I_ ZTD_DEFAULT_ON
			#else
				#define ZTD_HEADER_NL_LANGINFO_H_I_ ZTD_DEFAULT_OFF
			#endif
		#else
			#define ZTD_HEADER_NL_LANGINFO_H_I_ ZTD_DEFAULT_ON
		#endif
	#else
		#define ZTD_HEADER_NL_LANGINFO_H_I_ ZTD_DEFAULT_OFF
	#endif
#endif // nl_langinfo POSIX

#if defined(ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION)
	#if (ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION != 0)
		#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_ON
	#else
		#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_HEADER_NL_LANGINFO_H) && (ZTD_IS_ON(ZTD_PLATFORM_ZEDOS) || ZTD_IS_ON(ZTD_PLATFORM_AIX))
	#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_ON
#else
	#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_DEFAULT_OFF
#endif // Locale-dependent wchar_t detection

#if defined(ZTD_WCHAR_T_UTF16_COMPATIBLE)
	#if (ZTD_WCHAR_T_UTF16_COMPATIBLE != 0)
		#define ZTD_WCHAR_T_UTF16_COMPATIBLE_I_ ZTD_ON
	#else
		#define ZTD_WCHAR_T_UTF16_COMPATIBLE_I_ ZTD_OFF
	#endif
#elif (WCHAR_MAX >= 0xFFFF) && ZTD_IS_ON(ZTD_PLATFORM_WINDOWS)
	#define ZTD_WCHAR_T_UTF16_COMPATIBLE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_WCHAR_T_UTF16_COMPATIBLE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_WCHAR_T_UTF32_COMPATIBLE)
	#if (ZTD_WCHAR_T_UTF32_COMPATIBLE != 0)
		#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_ON
	#else
		#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_OFF
	#endif
#elif defined(__STDC_ISO_10646__) && (__STDC_ISO_10646__ != 0)
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0x0010FFFF) && ZTD_IS_OFF(ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION) && ZTD_IS_OFF(ZTD_WCHAR_T_UTF16_COMPATIBLE)
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_OFF
#endif

#if ZTD_IS_ON(ZTD_WCHAR_T_UTF32_COMPATIBLE) && ZTD_IS_ON(ZTD_WCHAR_T_UTF16_COMPATIBLE)
	#error Both ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ and ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ are on, meaning that the wchar_t encoding is both UTF-32 and UTF-16 compatible. This cannot be right: please check your build macros for WCHAR_T-related ZTD defines, or file a bug report!
#endif

#if defined(ZTD_NATIVE_CHAR8_T)
	#if (ZTD_NATIVE_CHAR8_T)
		#define ZTD_NATIVE_CHAR8_T_I_ ZTD_ON
	#else
		#define ZTD_NATIVE_CHAR8_T_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_CXX) && defined(__cpp_char8_t)
	#define ZTD_NATIVE_CHAR8_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_NATIVE_CHAR8_T_I_ ZTD_DEFAULT_OFF
#endif // char8_t exists natively (C++) - C proposal in WG14 still in progress

#if defined(ZTD_WCHAR_T_IS_UNSIGNED)
	#if (ZTD_WCHAR_T_IS_UNSIGNED != 0)
		#define ZTD_WCHAR_T_IS_UNSIGNED_I_ ZTD_ON
	#else
		#define ZTD_WCHAR_T_IS_UNSIGNED_I_ ZTD_OFF
	#endif
#elif defined(WCHAR_MIN)
	#if (WCHAR_MIN < 0)
		#define ZTD_WCHAR_T_IS_UNSIGNED_I_ ZTD_DEFAULT_OFF
	#elif (WCHAR_MIN >= 0)
		#define ZTD_WCHAR_T_IS_UNSIGNED_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_WCHAR_T_IS_UNSIGNED_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_WCHAR_T_IS_UNSIGNED_I_ ZTD_OFF
#endif

#if defined(ZTD_CHAR8_T)
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_ON
	#define ZTD_CHAR8_T_I_ ZTD_CHAR8_T
#elif ZTD_IS_ON(ZTD_NATIVE_CHAR8_T)
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_DEFAULT_OFF
	#define ZTD_CHAR8_T_I_ char8_t
#else
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_DEFAULT_OFF
	#define ZTD_CHAR8_T_I_ unsigned char
#endif // char8_t defined by the user

#if defined(ZTD_HEADER_UCHAR_H)
	#if (ZTD_HEADER_UCHAR_H != 0)
		#define ZTD_HEADER_UCHAR_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_UCHAR_H_I_ ZTD_OFF
	#endif
#elif ZTD_IS_OFF(ZTD_PLATFORM_MAC_OS)
	#define ZTD_HEADER_UCHAR_H_I_ ZTD_DEFAULT_ON
#elif ZTD_HAS_INCLUDE_I_(<uchar.h>)
	#define ZTD_HEADER_UCHAR_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_UCHAR_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_CUCHAR)
	#if (ZTD_HEADER_CUCHAR != 0)
		#define ZTD_HEADER_CUCHAR_I_ ZTD_ON
	#else
		#define ZTD_HEADER_CUCHAR_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_HAS_INCLUDE_I_(<cuchar>)
	#define ZTD_HEADER_CUCHAR_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_OFF(ZTD_CXX_STDLIB_CXX)
	#define ZTD_HEADER_CUCHAR_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_CUCHAR_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_WCHAR_H)
	#if (ZTD_HEADER_WCHAR_H != 0)
		#define ZTD_HEADER_WCHAR_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_WCHAR_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<wchar.h>)
	#define ZTD_HEADER_WCHAR_H_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_OFF(ZTD_CXX_STDLIB_CXX)
	#define ZTD_HEADER_WCHAR_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_WCHAR_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_CWCHAR)
	#if (ZTD_HEADER_CWCHAR != 0)
		#define ZTD_HEADER_CWCHAR_I_ ZTD_ON
	#else
		#define ZTD_HEADER_CWCHAR_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_HAS_INCLUDE_I_(<cwchar>)
	#define ZTD_HEADER_CWCHAR_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_OFF(ZTD_PLATFORM_MAC_OS)
	#define ZTD_HEADER_CWCHAR_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_CWCHAR_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_DLFCN_H)
	#if (ZTD_HEADER_DLFCN_H != 0)
		#define ZTD_HEADER_DLFCN_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_DLFCN_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<dlfcn.h>)
	#define ZTD_HEADER_DLFCN_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_DLFCN_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_PTHREAD_H)
	#if (ZTD_HEADER_PTHREAD_H != 0)
		#define ZTD_HEADER_PTHREAD_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_PTHREAD_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<pthread.h>)
	#define ZTD_HEADER_PTHREAD_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_PTHREAD_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_PTHREAD_NP_H)
	#if (ZTD_HEADER_PTHREAD_NP_H != 0)
		#define ZTD_HEADER_PTHREAD_NP_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_PTHREAD_NP_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<pthread_np.h>)
	#define ZTD_HEADER_PTHREAD_NP_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_PTHREAD_NP_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_SCHED_H)
	#if (ZTD_HEADER_SCHED_H != 0)
		#define ZTD_HEADER_SCHED_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_SCHED_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<sched.h>)
	#define ZTD_HEADER_SCHED_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_SCHED_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_THREADS_H)
	#if (ZTD_THREASD_H != 0)
		#define ZTD_HEADER_THREADS_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_THREADS_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<threads.h>)
	#define ZTD_HEADER_THREADS_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_THREADS_H_I_ ZTD_DEFAULT_OFF
#endif


#if defined(ZTD_HEADER_CTHREADS)
	#if (ZTD_THREASD_H != 0)
		#define ZTD_HEADER_CTHREADS_I_ ZTD_ON
	#else
		#define ZTD_HEADER_CTHREADS_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<cthreads>)
	#define ZTD_HEADER_CTHREADS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_CTHREADS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_STDATOMIC_H)
	#if (ZTD_THREASD_H != 0)
		#define ZTD_HEADER_STDATOMIC_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_STDATOMIC_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<stdatomic.h>)
	#define ZTD_HEADER_STDATOMIC_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_STDATOMIC_H_I_ ZTD_DEFAULT_OFF
#endif


#if defined(ZTD_HEADER_CSTDATOMIC)
	#if (ZTD_THREASD_H != 0)
		#define ZTD_HEADER_CSTDATOMIC_I_ ZTD_ON
	#else
		#define ZTD_HEADER_CSTDATOMIC_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<cstdatomic>)
	#define ZTD_HEADER_CSTDATOMIC_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_CSTDATOMIC_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_HEADER_XTHREADS_H)
	#if (ZTD_THREASD_H != 0)
		#define ZTD_HEADER_XTHREADS_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_XTHREADS_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<xthreads.h>)
	#define ZTD_HEADER_XTHREADS_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_XTHREADS_H_I_ ZTD_DEFAULT_OFF
#endif


#if defined(ZTD_HEADER_STDBIT_H)
	#if (ZTD_HEADER_STDBIT_H != 0)
		#define ZTD_HEADER_STDBIT_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_STDBIT_H_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_INCLUDE_I_(<stdbit.h>)
	#define ZTD_HEADER_STDBIT_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_STDBIT_H_I_ ZTD_DEFAULT_OFF
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#if ZTD_IS_ON(ZTD_HEADER_CUCHAR)
		#define ZTD_UCHAR_SCOPE_I_ ::std::
	#else
		#define ZTD_UCHAR_SCOPE_I_ ::
	#endif
#else
	#define ZTD_UCHAR_SCOPE_I_
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#if ZTD_IS_ON(ZTD_HEADER_CWCHAR)
		#define ZTD_WCHAR_SCOPE_I_ ::std::
	#else
		#define ZTD_WCHAR_SCOPE_I_ ::
	#endif
#else
	#define ZTD_WCHAR_SCOPE_I_
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#if ZTD_IS_ON(ZTD_HEADER_CWCHAR) || ZTD_IS_ON(ZTD_HEADER_CUCHAR)
		#define ZTD_MBSTATE_SCOPE_I_ ::std::
	#else
		#define ZTD_MBSTATE_SCOPE_I_ ::
	#endif
#else
	#define ZTD_MBSTATE_SCOPE_I_
#endif

#if defined(ZTD_HEADER_LANG_INFO_H)
	#if (ZTD_HEADER_LANG_INFO_H != 0)
		#define ZTD_HEADER_LANG_INFO_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_LANG_INFO_H_I_ ZTD_OFF
	#endif
#else
	#if ZTD_HAS_INCLUDE_I_(<langinfo.h>)
		#if ZTD_IS_ON(ZTD_PLATFORM_ANDROID)
			#if ZTD_USE(ZTD_PLATFORM_ANDROID_VERSION) >= 26
				#define ZTD_HEADER_LANG_INFO_H_I_ ZTD_DEFAULT_ON
			#else
				#define ZTD_HEADER_LANG_INFO_H_I_ ZTD_DEFAULT_OFF
			#endif
		#else
			#define ZTD_HEADER_LANG_INFO_H_I_ ZTD_DEFAULT_ON
		#endif
	#else
		#define ZTD_HEADER_LANG_INFO_H_I_ ZTD_DEFAULT_OFF
	#endif
#endif // langinfo POSIX

#if defined(ZTD_NL_LANGINFO)
	#if (ZTD_NL_LANGINFO != 0)
		#define ZTD_NL_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_NL_LANGINFO_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_HEADER_NL_LANGINFO_H) || ZTD_IS_ON(ZTD_HEADER_LANG_INFO_H)
	#define ZTD_NL_LANGINFO_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_NL_LANGINFO_I_ ZTD_DEFAULT_OFF
#endif

#if (ZTD_HAS_ATTRIBUTE_I_(nodiscard) != 0L)
	#if ZTD_IS_ON(ZTD_CXX)
		#if ZTD_HAS_ATTRIBUTE_I_(nodiscard) >= 201907L
			#define ZTD_ATTR_NODISCARD_MESSAGE_I_(__message) [[nodiscard(__message)]]
			#define ZTD_ATTR_NODISCARD_I_ [[nodiscard]]
		#else
			#define ZTD_ATTR_NODISCARD_MESSAGE_I_(__message) [[nodiscard]]
			#define ZTD_ATTR_NODISCARD_I_ [[nodiscard]]
		#endif
	#else
		#define ZTD_ATTR_NODISCARD_MESSAGE_I_(__message) [[nodiscard(__message)]]
		#define ZTD_ATTR_NODISCARD_I_ [[nodiscard]]
	#endif
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX) && defined(_Check_return_)
		#define ZTD_ATTR_NODISCARD_MESSAGE_I_(__message) _Check_return_
		#define ZTD_ATTR_NODISCARD_I_ _Check_return_
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_GCC)
		#define ZTD_ATTR_NODISCARD_MESSAGE_I_(__message) __attribute__((warn_unused_result))
		#define ZTD_ATTR_NODISCARD_I_ __attribute__((warn_unused_result))
	#else
		// :c
		#define ZTD_NODSICARD_I_(__message)
		#define ZTD_ATTR_NODISCARD_I_
	#endif
#endif

#if (ZTD_HAS_ATTRIBUTE_I_(no_unique_address) != 0L)
	#define ZTD_NO_UNIQUE_ADDRESS_I_ [[no_unique_address]]
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_ON(ZTD_COMPILER_VCXX) && _MSC_VER >= 1929L && ZTD_USE(ZTD_CXX_VERSION) >= 202000L 
	#define ZTD_NO_UNIQUE_ADDRESS_I_ [[msvc::no_unique_address]]
#else
	#define ZTD_NO_UNIQUE_ADDRESS_I_
#endif

#if (ZTD_HAS_ATTRIBUTE_I_(no_unique_address) != 0L)
	#define ZTD_NO_UNIQUE_ADDRESS_I_ [[no_unique_address]]
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_ON(ZTD_COMPILER_VCXX) && _MSC_VER >= 1929L && ZTD_USE(ZTD_CXX_VERSION) >= 202000L 
	#define ZTD_NO_UNIQUE_ADDRESS_I_ [[msvc::no_unique_address]]
#else
	#define ZTD_NO_UNIQUE_ADDRESS_I_
#endif

#if ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_ATTR_WEAK_FUNC_I_ __attribute__((weak))
#elif (ZTD_HAS_ATTRIBUTE_I_(weak) != 0L)
	#define ZTD_ATTR_WEAK_FUNC_I_ [[weak]]
#elif (ZTD_HAS_ATTRIBUTE_I_(gcc::weak) != 0L)
	#define ZTD_ATTR_WEAK_FUNC_I_ [[gcc::weak]]
#elif (ZTD_HAS_ATTRIBUTE_I_(clang::weak) != 0L)
	#define ZTD_ATTR_WEAK_FUNC_I_ [[clang::weak]]
#else
	#define ZTD_ATTR_WEAK_FUNC_I_
#endif

#if ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_ATTR_FLATTEN_I_ __attribute__((flatten))
#elif (ZTD_HAS_ATTRIBUTE_I_(flatten) != 0L)
	#define ZTD_ATTR_FLATTEN_I_ [[flatten]]
#elif (ZTD_HAS_ATTRIBUTE_I_(gcc::flatten) != 0L)
	#define ZTD_ATTR_FLATTEN_I_ [[gcc::flatten]]
#elif (ZTD_HAS_ATTRIBUTE_I_(clang::flatten) != 0L)
	#define ZTD_ATTR_FLATTEN_I_ [[clang::flatten]]
#elif (ZTD_HAS_ATTRIBUTE_I_(msvc::flatten) != 0L)
	#define ZTD_ATTR_FLATTEN_I_ [[msvc::flatten]]
#else
	#define ZTD_ATTR_FLATTEN_I_
#endif

#if ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_ATTR_ALWAYS_INLINE_I_ __attribute__((always_inline))
#elif (ZTD_HAS_ATTRIBUTE_I_(always_inline) != 0L)
	#define ZTD_ATTR_ALWAYS_INLINE_I_ [[always_inline]]
#elif (ZTD_HAS_ATTRIBUTE_I_(gcc::always_inline) != 0L)
	#define ZTD_ATTR_ALWAYS_INLINE_I_ [[gcc::always_inline]]
#elif (ZTD_HAS_ATTRIBUTE_I_(clang::always_inline) != 0L)
	#define ZTD_ATTR_ALWAYS_INLINE_I_ [[clang::always_inline]]
#elif (ZTD_HAS_ATTRIBUTE_I_(forceinline) != 0L)
	#define ZTD_ATTR_ALWAYS_INLINE_I_ [[forceinline]]
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
	#define ZTD_ATTR_ALWAYS_INLINE_I_ __forceinline
#else
	#define ZTD_ATTR_ALWAYS_INLINE_I_
#endif

#if ZTD_IS_ON(ZTD_COMPILER_VCXX) && ZTD_IS_OFF(ZTD_COMPILER_VCXX_CLANG)
	#define ZTD_INLINE_IF_NOT_MSVC_I_ 
#else
	#define ZTD_INLINE_IF_NOT_MSVC_I_ inline
#endif

#if (ZTD_HAS_ATTRIBUTE_I_(deprecated) != 0L)
	#define ZTD_ATTR_DEPRECATED_I_(__message) [[deprecated(__message)]]
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX)
		#define ZTD_ATTR_DEPRECATED_I_(__message) declspec(deprecated)
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_GCC)
		#define ZTD_ATTR_DEPRECATED_I_(__message) __attribute__((deprecated))
	#else
		// :c
		#define ZTD_ATTR_DEPRECATED_I_(__message)
	#endif
#endif

#if (ZTD_HAS_ATTRIBUTE_I_(no_return) != 0L)
	#define ZTD_ATTR_NO_RETURN_I_ [[noreturn]]
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX)
		#define ZTD_ATTR_NO_RETURN_I_ declspec(noreturn)
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_GCC)
		#define ZTD_ATTR_NO_RETURN_I_ __attribute__((noreturn))
	#else
		// :c
		#define ZTD_ATTR_NO_RETURN_I_
	#endif
#endif

#if (ZTD_HAS_ATTRIBUTE_I_(fallthrough) != 0L)
	#define ZTD_ATTR_FALLTHROUGH_I_ [[fallthrough]]
#else
	#define ZTD_ATTR_FALLTHROUGH_I_
#endif

#if defined(ZTD_ATTR_TYPE_ALIGN)
	#define ZTD_ATTR_TYPE_ALIGN_I_(...) ZTD_ATTR_TYPE_ALIGN(__VA__ARGS__)
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
	#define ZTD_ATTR_TYPE_ALIGN_I_(...) __declspec(align(__VA_ARGS__))
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG) || ZTD_IS_ON(ZTD_COMPILER_GCC)
	#define ZTD_ATTR_TYPE_ALIGN_I_(...) __attribute__((aligned(__VA_ARGS__)))
#else
	#define ZTD_ATTR_TYPE_ALIGN_I_(...)
#endif

#if defined(ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE)
	#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX)
		// "The reserve value specifies the total stack allocation in virtual memory. 
		// For ARM, x86 and x64 machines, the default stack size is 1 MB."
		// ...
		// "For ARM, x86 and x64 machines, the default commit value is 4 KB"
		// https://docs.microsoft.com/en-us/cpp/build/reference/stack-stack-allocations?view=vs-2019
		// Uses: (1024 * 64)
		#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ (65536)
	#elif ZTD_IS_ON(ZTD_PLATFORM_MAC_OS)
		// "  -stack_size size
		//     Specifies the maximum stack size for the main thread in a program.  Without this option a
		//     program has a 8MB stack.  The argument size is a hexadecimal number with an optional lead-
		//     ing 0x. The size should be a multiple of the architecture's page size (4KB or 16KB).
		// ld(1) manpage on Mac OS
		// Uses: ((1024 * 64) * 8)
		#define ZTD_INTERMEDIATE_BUFFER_SUGGESTED_BYTE_SIZE_I_ (524288)
	#elif ZTD_IS_ON(ZTD_PLATFORM_LINUX) || ZTD_IS_ON(ZTD_PLATFORM_UNIX)
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

#if defined(ZTD_STD_C_THREADS)
	#if (ZTD_STD_C_THREADS != 0)
		#define ZTD_STD_C_THREADS_I_ ZTD_ON
	#else
		#define ZTD_STD_C_THREADS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_HEADER_THREADS_H) && !(defined(__STDC_NO_THREADS__) && (__STDC_NO_THREADS__ != 0))
	#define ZTD_STD_C_THREADS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_C_THREADS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS)
	#if (ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS != 0)
		#define ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS_I_ ZTD_ON
	#else
		#define ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS_I_ ZTD_OFF
	#endif
#else
	#define ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_NONPORTABLE_MSVC_INTRINSICS)
	#if (ZTD_NONPORTABLE_MSVC_INTRINSICS != 0)
		#define ZTD_NONPORTABLE_MSVC_INTRINSICS_I_ ZTD_ON
	#else
		#define ZTD_NONPORTABLE_MSVC_INTRINSICS_I_ ZTD_OFF
	#endif
#else
	#define ZTD_NONPORTABLE_MSVC_INTRINSICS_I_ ZTD_DEFAULT_OFF
#endif


// Cache line size: number of bytes
#if defined(ZTD_L1_CACHE_LINE_SIZE)
	#define ZTD_L1_CACHE_LINE_SIZE_USER_DEFINED_I_ ZTD_ON
	#define ZTD_L1_CACHE_LINE_SIZE_I_ ZTD_L1_CACHE_LINE_SIZE
#else
	#define ZTD_L1_CACHE_LINE_SIZE_USER_DEFINED_I_ ZTD_OFF
	#define ZTD_L1_CACHE_LINE_SIZE_I_ 64
#endif

#if defined(ZTD_COMPILE_TIME_ENCODING_NAME)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         ZTD_COMPILE_TIME_ENCODING_NAME
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "set by the user with ZTD_COMPILE_TIME_ENCODING_NAME as (" ZTD_TOKEN_TO_STRING(ZTD_COMPILE_TIME_ENCODING_NAME) ")"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(_MSVC_EXECUTION_CHARACTER_SET)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         ZTD_VCXX_MSC_CODEPAGE_ID_TO_NAME_I_(_MSVC_EXECUTION_CHARACTER_SET)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "MSVC CodePage ID: " ZTD_TOKEN_TO_STRING(_MSVC_EXECUTION_CHARACTER_SET) " (" ZTD_VCXX_MSC_CODEPAGE_ID_TO_NAME_I_(_MSVC_EXECUTION_CHARACTER_SET) ")"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(__GNUC_EXECUTION_CHARSET_NAME)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         __GNUC_EXECUTION_CHARSET_NAME
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() __GNUC_EXECUTION_CHARSET_NAME
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(__clang_literal_encoding__)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         __clang_literal_encoding__
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() __clang_literal_encoding__
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#else
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         "UTF-8"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "UTF-8, Defaulted"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_COMPILE_TIME_WIDE_ENCODING_NAME)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         ZTD_COMPILE_TIME_WIDE_ENCODING_NAME
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "set by the user with ZTD_COMPILE_TIME_ENCODING_NAME as (" ZTD_TOKEN_TO_STRING(ZTD_COMPILE_TIME_WIDE_ENCODING_NAME) ")"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_ON
#elif defined(__GNUC_WIDE_EXECUTION_CHARSET_NAME)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         __GNUC_WIDE_EXECUTION_CHARSET_NAME
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(__clang_wide_literal_encoding__)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         __clang_wide_literal_encoding__
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_PLATFORM_WINDOWS)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0x001FFFFF) && ZTD_IS_ON(ZTD_WCHAR_T_UTF32_COMPATIBLE)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0x0000FFFF)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0x000000FF)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-8"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-8"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#else
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-32, Defaulted"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_OFF
#endif

#if ZTD_IS_ON(ZTD_CXX) || ZTD_IS_ON(ZTD_COMPILER_VCXX)
	#define ZTD_STATIC_PTR_EXTENT_I_(...)
#else
	#define ZTD_STATIC_PTR_EXTENT_I_(...) static (__VA_ARGS__)
#endif

#if defined(ZTD_HEADER_VCXX_INTRIN_H)
	#if (ZTD_HEADER_VCXX_INTRIN_H != 0)
		#define ZTD_HEADER_VCXX_INTRIN_H_I_ ZTD_ON
	#else
		#define ZTD_HEADER_VCXX_INTRIN_H_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX) && ZTD_HAS_INCLUDE_I_(<intrin.h>)
	#define ZTD_HEADER_VCXX_INTRIN_H_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_HEADER_VCXX_INTRIN_H_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS)
	#if (ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS != 0)
		#define ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS_I_ ZTD_ON
	#else
		#define ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS_I_ ZTD_OFF
	#endif
#else
	#define ZTD_VCXX_CONSTEXPR_BIT_INTRINSICS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_DOXYGEN_PREPROCESSING)
	#if (ZTD_DOXYGEN_PREPROCESSING != 0)
		#define ZTD_DOXYGEN_PREPROCESSING_I_ ZTD_ON
	#else
		#define ZTD_DOXYGEN_PREPROCESSING_I_ ZTD_OFF
	#endif
#else
	#define ZTD_DOXYGEN_PREPROCESSING_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_CONST_IF_NOT_BROKEN_CXX)
	#define ZTD_CONST_IF_NOT_BROKEN_CXX_I_ ZTD_CONST_IF_NOT_BROKEN_CXX
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_ON(ZTD_COMPILER_VCXX)
	#define ZTD_CONST_IF_NOT_BROKEN_CXX_I_
#else
	#define ZTD_CONST_IF_NOT_BROKEN_CXX_I_ const
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#define ZTD_CONSTEXPR_IF_CXX_I_ constexpr
#else
	#define ZTD_CONSTEXPR_IF_CXX_I_
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#define ZTD_INLINE_IF_CXX_I_ inline
#else
	#define ZTD_INLINE_IF_CXX_I_
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#define ZTD_NOEXCEPT_IF_CXX_I_ noexcept
#else
	#define ZTD_NOEXCEPT_IF_CXX_I_
#endif

#if defined(ZTD_BUILTIN_POPCOUNT)
	#if (ZTD_BUILTIN_POPCOUNT != 0)
		#define ZTD_BUILTIN_POPCOUNT_I_ ZTD_ON
	#else
		#define ZTD_BUILTIN_POPCOUNT_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_BUILTIN_I_(__builtin_popcount)
	#define ZTD_BUILTIN_POPCOUNT_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_BUILTIN_POPCOUNT_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BUILTIN_POPCOUNT_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_BUILTIN_RETURN_ADDRESS)
	#if (ZTD_BUILTIN_RETURN_ADDRESS != 0)
		#define ZTD_BUILTIN_RETURN_ADDRESS_I_ ZTD_ON
	#else
		#define ZTD_BUILTIN_RETURN_ADDRESS_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_BUILTIN_I_(__builtin_return_address)
	#define ZTD_BUILTIN_RETURN_ADDRESS_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_BUILTIN_RETURN_ADDRESS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BUILTIN_RETURN_ADDRESS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_BUILTIN_FRAME_ADDRESS)
	#if (ZTD_BUILTIN_FRAME_ADDRESS != 0)
		#define ZTD_BUILTIN_FRAME_ADDRESS_I_ ZTD_ON
	#else
		#define ZTD_BUILTIN_FRAME_ADDRESS_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_BUILTIN_I_(__builtin_frame_address)
	#define ZTD_BUILTIN_FRAME_ADDRESS_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_BUILTIN_FRAME_ADDRESS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BUILTIN_FRAME_ADDRESS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_BUILTIN_CTZ)
	#if (ZTD_BUILTIN_CTZ != 0)
		#define ZTD_BUILTIN_CTZ_I_ ZTD_ON
	#else
		#define ZTD_BUILTIN_CTZ_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_BUILTIN_I_(__builtin_ctz)
	#define ZTD_BUILTIN_CTZ_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_BUILTIN_CTZ_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BUILTIN_CTZ_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_BUILTIN_CLZ)
	#if (ZTD_BUILTIN_CLZ != 0)
		#define ZTD_BUILTIN_CLZ_I_ ZTD_ON
	#else
		#define ZTD_BUILTIN_CLZ_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_BUILTIN_I_(__builtin_clz)
	#define ZTD_BUILTIN_CLZ_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_BUILTIN_CLZ_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BUILTIN_CLZ_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_BUILTIN_FFS)
	#if (ZTD_BUILTIN_FFS != 0)
		#define ZTD_BUILTIN_FFS_I_ ZTD_ON
	#else
		#define ZTD_BUILTIN_FFS_I_ ZTD_OFF
	#endif
#elif ZTD_HAS_BUILTIN_I_(__builtin_ffs)
	#define ZTD_BUILTIN_FFS_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC) || ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#define ZTD_BUILTIN_FFS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_BUILTIN_FFS_I_ ZTD_DEFAULT_OFF
#endif

#define ZTD_INLINE_CONSTEXPR_IF_CXX_I_ ZTD_INLINE_IF_CXX_I_ ZTD_CONSTEXPR_IF_CXX_I_

#if ZTD_IS_ON(ZTD_CXX)
	#define ZTD_EXTERN_C_OPEN_I_ extern "C" {
	#define ZTD_EXTERN_C_CLOSE_I_ }
#else
	#define ZTD_EXTERN_C_OPEN_I_
	#define ZTD_EXTERN_C_CLOSE_I_
#endif

#if ZTD_IS_ON(ZTD_CXX)
	#define ZTD_CXX_NOEXCEPT_I_ noexcept
	#define ZTD_CXX_NOEXCEPT_IF_I_(...) noexcept(__VA_ARGS__)
#else
	#define ZTD_CXX_NOEXCEPT_I_
	#define ZTD_CXX_NOEXCEPT_IF_I_(...)
#endif

#if defined(ZTD_C_LANGUAGE_LINKAGE)
	#define ZTD_C_LANGUAGE_LINKAGE_I_ ZTD_C_LANGUAGE_LINKAGE
#else
	#if ZTD_IS_ON(ZTD_CXX)
		#define ZTD_C_LANGUAGE_LINKAGE_I_ extern "C"
	#else
		#define ZTD_C_LANGUAGE_LINKAGE_I_ extern
	#endif
#endif // C language linkage

#if defined(ZTD_CXX_LANGUAGE_LINKAGE)
	#define ZTD_CXX_LANGUAGE_LINKAGE_I_ ZTD_CXX_LANGUAGE_LINKAGE
#else
	#define ZTD_CXX_LANGUAGE_LINKAGE_I_ extern
#endif // C++ language linkage


// clang-format on

#endif
