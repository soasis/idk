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

#ifndef ZTD_ASSERT_HPP
#define ZTD_ASSERT_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/assert.h>

// clang-format off
#if defined(ZTD_CONSTEXPR_ASSERT_USER)
	#define ZTD_CONSTEXPR_ASSERT_I_(...) ZTD_CONSTEXPR_ASSERT_USER(__VA_ARGS__)
#else
	#if ZTD_IS_ON(ZTD_CONSTEXPR_ASSERT_CHECKS)
		#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
			#if ZTD_IS_ON(ZTD_EXCEPTIONS)
				#include <exception>
				#include <iostream>
				#include <cstdlib>
				#include <type_traits>

				#define ZTD_CONSTEXPR_ASSERT_I_(...)                                                                              \
					do {                                                                                                         \
						if (!(__VA_ARGS__)) {                                                                                   \
							if (::std::is_constant_evaluated()) {                                                              \
								throw "Assertion " #__VA_ARGS__ "failed in " __FILE__ " line "  ZTD_TOKEN_TO_STRING(__LINE__);\
							}                                                                                                  \
							else {                                                                                             \
								::std::cerr << "Assertion `" #__VA_ARGS__ "` failed in `" __FILE__ "` line " <<               \
								__LINE__ << ::std::endl;                                                                      \
								::std::terminate();                                                                           \
							}                                                                                                  \
						}                                                                                                       \
					} while (false)
			#else
				#include <exception>
				#include <iostream>
				#include <cstdlib>
				#include <type_traits>

				#define ZTD_CONSTEXPR_ASSERT_I_(...)                                                                    \
					do {                                                                                               \
						if (!(__VA_ARGS__)) {                                                                         \
							if (::std::is_constant_evaluated()) {                                                    \
								/* ?????*/;                                                                         \
							}                                                                                        \
							else {                                                                                   \
								::std::cerr << "Assertion `" #__VA_ARGS__ "` failed in `" __FILE__ "` line " <<     \
								__LINE__ << ::std::endl;                                                            \
								::std::terminate();                                                                 \
							}                                                                                        \
						}                                                                                             \
					} while (false)
			#endif
		#else
			#if ZTD_IS_ON(ZTD_EXCEPTIONS)
				#include <cstdlib>

				#define ZTD_CONSTEXPR_ASSERT_I_(...)                                                                              \
					do {                                                                                                         \
						if (!(__VA_ARGS__)) {                                                                                   \
							throw "Assertion `" #__VA_ARGS__ "` failed in `" __FILE__ "` line "  ZTD_TOKEN_TO_STRING(__LINE__);\
							                                                                                                   \
						}                                                                                                       \
					} while (false)
			#else
				#include <cstdlib>

				#define ZTD_CONSTEXPR_ASSERT_I_(...) \
					do {                            \
						if (!(__VA_ARGS__)) {      \
							/* ????? */;          \
						}                          \
					} while (false)
			#endif
		#endif
	#else
		#define ZTD_CONSTEXPR_ASSERT_I_(...)          \
			do {                                     \
				if (false) {                        \
					(void)(__VA_ARGS__);           \
				}                                   \
			} while (false)
	#endif
#endif

#if defined(ZTD_CONSTEXPR_ASSERT_MESSAGE_USER)
	#define ZTD_CONSTEXPR_ASSERT_MESSAGE_I_(...) ZTD_CONSTEXPR_ASSERT_MESSAGE_USER(__VA_ARGS__)
#else
	#if ZTD_IS_ON(ZTD_CONSTEXPR_ASSERT_CHECKS)
		#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
			#if ZTD_IS_ON(ZTD_EXCEPTIONS)
				#include <exception>
				#include <iostream>
				#include <cstdlib>
				#include <type_traits>

				#define ZTD_CONSTEXPR_ASSERT_MESSAGE_I_(_MESSAGE, ...)                                                                               \
					do {                                                                                                                            \
						if (!(__VA_ARGS__)) {                                                                                                      \
							if (::std::is_constant_evaluated()) {                                                                                 \
								throw "Assertion `" #__VA_ARGS__ "1 failed in `" __FILE__ "` line "  ZTD_TOKEN_TO_STRING(__LINE__) ": " _MESSAGE;\
							}                                                                                                                     \
							else {                                                                                                                \
								::std::cerr << "Assertion `" #__VA_ARGS__ "` failed in `" __FILE__ "` line " << __LINE__ << ": "                 \
										<< _MESSAGE << ::std::endl;                                                                            \
								::std::terminate();                                                                                              \
							}                                                                                                                     \
						}                                                                                                                          \
					} while (false)
			#else
				#include <iostream>
				#include <cstdlib>
				#include <type_traits>

				#define ZTD_CONSTEXPR_ASSERT_MESSAGE_I_(_MESSAGE, ...)                                                                   \
					do {                                                                                                                \
						if (!(__VA_ARGS__)) {                                                                                          \
							if (::std::is_constant_evaluated()) {                                                                     \
								/* ????? */                                                                                          \
							}                                                                                                         \
							else {                                                                                                    \
								::std::cerr << "Assertion `" #__VA_ARGS__ "` failed in `" __FILE__ "` line " << __LINE__ << ": "     \
										<< _MESSAGE << ::std::endl;                                                                \
								::std::terminate();                                                                                  \
							}                                                                                                         \
						}                                                                                                              \
					} while (false)
			#endif
		#endif
	#else
		#if ZTD_IS_ON(ZTD_EXCEPTIONS)
			#define ZTD_CONSTEXPR_ASSERT_MESSAGE_I_(_MESSAGE, ...)                                                                          \
				do {                                                                                                                       \
					if (!(__VA_ARGS__)) {                                                                                                 \
						throw "Assertion `" #__VA_ARGS__ "` failed in `" __FILE__ "` line "  ZTD_TOKEN_TO_STRING(__LINE__) ": " _MESSAGE;\
					}                                                                                                                     \
				} while (false)
		#else
			#include <cstdlib>

			#define ZTD_CONSTEXPR_ASSERT_MESSAGE_I_(_MESSAGE, ...) \
				do {                                              \
					if (!(__VA_ARGS__)) {                        \
						/* ???? */                              \
						(void)sizeof(_MESSAGE);                 \
					}                                            \
				} while (false)
		#endif
	#endif
#endif

// clang-format on

//////
/// @brief A macro for asserting over a given (set of) conditions.
///
/// @param[in] ... The conditional expressions to check against.
///
/// @remarks The conditions must result in a value that is convertible to a boolean in a boolean context. This macro
/// does nothing when `ZTD_CONSTEXPR_ASSERT_CHECKS` is not detected. (It will still (void)-cast the used items, to prevent unused
/// warnings.) If the condition is not reached, this function will perform either a user-defined action or
/// terminate/exit (not abort).
#define ZTD_CONSTEXPR_ASSERT(...) ZTD_CONSTEXPR_ASSERT_I_(__VA_ARGS__)

//////
/// @brief A macro for asserting over a given (set of) conditions.
///
/// @param[in] _MESSAGE The message to pass through.
/// @param[in] ... The conditional expressions to check against.
///
/// @remarks The conditions must result in a value that is convertible to a boolean in a boolean context. This macro
/// does nothing when `ZTD_CONSTEXPR_ASSERT_CHECKS` is not detected. (It will still (void)-cast the used items, to prevent unused
/// warnings.) If the condition is not reached, this function will perform either a user-defined action or
/// terminate/exit (not abort).
#define ZTD_CONSTEXPR_ASSERT_MESSAGE(_MESSAGE, ...) ZTD_CONSTEXPR_ASSERT_MESSAGE_I_(_MESSAGE, __VA_ARGS__)

#endif
