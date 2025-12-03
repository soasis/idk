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

#ifndef ZTD_VERSION_DETAIL_VERSION_CXX_HPP
#define ZTD_VERSION_DETAIL_VERSION_CXX_HPP

#include <ztd/version/detail/is.h>
#include <ztd/version/detail/version.c.h>

// clang-format off
#if defined(ZTD_EXCEPTIONS)
	#if (ZTD_EXCEPTIONS != 0)
		#define ZTD_EXCEPTIONS_I_ ZTD_ON
	#else
		#define ZTD_EXCEPTIONS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_exceptions) && (__cpp_exceptions != 0)
	#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC)
	#if defined(__EXCEPTIONS) && (__EXCEPTIONS != 0)
		#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#if ZTD_HAS_FEATURE_I_(cxx_exceptions)
		#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
	#if defined(_CPPUNWIND) && (_CPPUNWIND != 0)
		#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_EXCEPTIONS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_RTTI)
	#if (ZTD_RTTI != 0)
		#define ZTD_RTTI_I_ ZTD_ON
	#else
		#define ZTD_RTTI_I_ ZTD_OFF
	#endif
#elif defined(__cpp_rtti) && (__cpp_rtti != 0)
	#define ZTD_RTTI_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_GCC)
	#if defined(__GXX_RTTI) && (__GXX_RTTI != 0)
		#define ZTD_RTTI_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_RTTI_I_ ZTD_DEFAULT_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#if ZTD_HAS_FEATURE_I_(cxx_rtti)
		#define ZTD_RTTI_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_RTTI_I_ ZTD_DEFAULT_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_VCXX)
	#if defined(_CPPRTTI) && (_CPPRTTI != 0)
		#define ZTD_RTTI_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_RTTI_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_RTTI_I_ ZTD_DEFAULT_OFF
#endif

#if defined (ZTD_STD_ALIGNED_OPERATOR_NEW)
	#if (ZTD_STD_ALIGNED_OPERATOR_NEW != 0)
		#define ZTD_STD_ALIGNED_OPERATOR_NEW_I_ ZTD_ON
	#else
		#define ZTD_STD_ALIGNED_OPERATOR_NEW_I_ ZTD_OFF
	#endif
#elif defined(__cpp_aligned_new)
	#define ZTD_STD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_CXX) && __cplusplus > 201603L
	#define ZTD_STD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_OFF
#endif // C++ operator new, with alignment parameter

#if defined(ZTD_STD_CONCEPTS)
	#if (ZTD_STD_CONCEPTS != 0)
		#define ZTD_STD_CONCEPTS_I_ ZTD_ON
	#else
		#define ZTD_STD_CONCEPTS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG)
	// clang is busted right now! need to check specific versions
	#if ZTD_IS_ON(ZTD_COMPILER_APPLE_CLANG)
		// Apple Clang has different versioning from regular clang, because OF COURSE THEY DO
		#if (__clang_major__ >= 15) && defined(__cpp_concepts) && (__cpp_concepts >= 201907LL)
			#define ZTD_STD_CONCEPTS_I_ ZTD_DEFAULT_ON
		#else
			#define ZTD_STD_CONCEPTS_I_ ZTD_DEFAULT_OFF
		#endif
	#else
		// taking bets: Clang 17 is when it'll get fixed!
		#if (__clang_major__ >= 17) && defined(__cpp_concepts) && (__cpp_concepts >= 201907LL)
			#define ZTD_STD_CONCEPTS_I_ ZTD_DEFAULT_ON
		#else
			#define ZTD_STD_CONCEPTS_I_ ZTD_DEFAULT_OFF
		#endif
	#endif
#elif defined(__cpp_concepts) && (__cpp_concepts >= 201907LL)
	#define ZTD_STD_CONCEPTS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_CONCEPTS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_DESIGNATED_INITIALIZERS)
	#if (ZTD_STD_DESIGNATED_INITIALIZERS != 0)
		#define ZTD_STD_DESIGNATED_INITIALIZERS_I_ ZTD_ON
	#else
		#define ZTD_STD_DESIGNATED_INITIALIZERS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_designated_initializers) && (__cpp_designated_initializers != 0)
	#define ZTD_STD_DESIGNATED_INITIALIZERS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_DESIGNATED_INITIALIZERS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_EXPLICIT)
	#if (ZTD_STD_EXPLICIT != 0)
		#define ZTD_STD_EXPLICIT_I_ ZTD_ON
	#else
		#define ZTD_STD_EXPLICIT_I_ ZTD_OFF
	#endif
#elif defined(__cpp_conditional_explicit) && (__cpp_conditional_explicit != 0)
	#define ZTD_STD_EXPLICIT_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_EXPLICIT_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_SPACESHIP_COMPARE)
	#if (ZTD_STD_SPACESHIP_COMPARE != 0)
		#define ZTD_STD_SPACESHIP_COMPARE_I_ ZTD_ON
	#else
		#define ZTD_STD_SPACESHIP_COMPARE_I_ ZTD_OFF
	#endif
#elif defined(__cpp_impl_three_way_comparison) && (__cpp_impl_three_way_comparison != 0)
	#define ZTD_STD_SPACESHIP_COMPARE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_SPACESHIP_COMPARE_I_ ZTD_DEFAULT_OFF
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

#if defined(ZTD_STD_LIBRARY_ASSUME_ALIGNED)
	#if (ZTD_STD_LIBRARY_ASSUME_ALIGNED != 0)
		#define ZTD_STD_LIBRARY_ASSUME_ALIGNED_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_ASSUME_ALIGNED_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_assume_aligned)
	#define ZTD_STD_LIBRARY_ASSUME_ALIGNED_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_ASSUME_ALIGNED_I_ ZTD_DEFAULT_OFF
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

#if defined(ZTD_STD_LIBRARY_CONSTRUCT_AT)
	#if (ZTD_STD_LIBRARY_CONSTRUCT_AT != 0)
		#define ZTD_STD_LIBRARY_CONSTRUCT_AT_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONSTRUCT_AT_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_constexpr_dynamic_alloc)
	#define ZTD_STD_LIBRARY_CONSTRUCT_AT_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONSTRUCT_AT_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_DESTROY_AT)
	#if (ZTD_STD_LIBRARY_DESTROY_AT != 0)
		#define ZTD_STD_LIBRARY_DESTROY_AT_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_DESTROY_AT_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_constexpr_dynamic_alloc)
	#define ZTD_STD_LIBRARY_DESTROY_AT_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_DESTROY_AT_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_RANGES)
	#if (ZTD_STD_LIBRARY_RANGES != 0)
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG)
	#if ZTD_IS_ON(ZTD_STD_CONCEPTS)
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

#if defined(ZTD_STD_LIBRARY_RANGES_BASIC_CONST_ITERATOR)
	#if (ZTD_STD_LIBRARY_RANGES_BASIC_CONST_ITERATOR != 0)
		#define ZTD_STD_LIBRARY_RANGES_BASIC_CONST_ITERATOR_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_RANGES_BASIC_CONST_ITERATOR_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_ranges_as_const) && __cpp_lib_ranges_as_const >= 202207L
	#define ZTD_STD_LIBRARY_RANGES_BASIC_CONST_ITERATOR_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_RANGES_BASIC_CONST_ITERATOR_I_ ZTD_DEFAULT_OFF
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


#if defined(ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS)
	#if (ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS != 0)
		#define ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_ranges)
	#if ZTD_IS_ON(ZTD_COMPILER_CLANG) && ZTD_IS_ON(ZTD_PLATFORM_MAC_OS) && __cpp_lib_ranges <= 202600L
		#define ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS_I_ ZTD_DEFAULT_OFF
	#elif __cpp_lib_ranges >= 202300L
		#define ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_STD_LIBRARY_RANGES_REVERSE_CPOS_I_ ZTD_DEFAULT_OFF
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

#if defined(ZTD_STD_LIBRARY_ATOMIC_REF)
	#if (ZTD_STD_LIBRARY_ATOMIC_REF != 0)
		#define ZTD_STD_LIBRARY_ATOMIC_REF_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_ATOMIC_REF_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_atomic_ref)
	#define ZTD_STD_LIBRARY_ATOMIC_REF_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_ATOMIC_REF_I_ ZTD_DEFAULT_OFF
#endif

#if defined (ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED)
	#if (ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED != 0)
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ constexpr
	#else
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ 
	#endif
#elif ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
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

#if defined(__cpp_lib_bitops)
	#if __cpp_lib_bitops != 0
		#define ZTD_STD_LIBRARY_BIT_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_BIT_I_ ZTD_OFF
	#endif
#else
	#define ZTD_STD_LIBRARY_BIT_I_ ZTD_DEFAULT_OFF
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
#elif ZTD_IS_ON(ZTD_CXX_STDLIB_VCXX) && ZTD_IS_ON(ZTD_STD_LIBRARY_CONCEPTS)
	#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_STD_LIBRARY_CONCEPTS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
	#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONTIGUOUS_ITERATOR_TAG_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_BORROWED_RANGE)
	#if (ZTD_STD_LIBRARY_BORROWED_RANGE != 0)
		#define ZTD_STD_LIBRARY_BORROWED_RANGE_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_BORROWED_RANGE_I_ ZTD_OFF
	#endif
#elif (ZTD_IS_ON(ZTD_CXX_STDLIB_STDCXX) && ZTD_IS_ON(ZTD_STD_LIBRARY_CONCEPTS)) \
     || (ZTD_IS_ON(ZTD_CXX_STDLIB_VCXX) && ZTD_IS_ON(ZTD_STD_LIBRARY_CONCEPTS)) || ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
	#define ZTD_STD_LIBRARY_BORROWED_RANGE_I_ ZTD_ON
#else
	#define ZTD_STD_LIBRARY_BORROWED_RANGE_I_ ZTD_OFF
#endif

#if defined(ZTD_STD_LIBRARY_FROM_RANGE_T)
	#if (ZTD_STD_LIBRARY_FROM_RANGE_T != 0)
		#define ZTD_STD_LIBRARY_FROM_RANGE_T_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_FROM_RANGE_T_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_ranges_to_container) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
#define ZTD_STD_LIBRARY_FROM_RANGE_T_I_ ZTD_DEFAULT_ON
#else
#define ZTD_STD_LIBRARY_FROM_RANGE_T_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_DEBUG_ITERATORS)
	#if (ZTD_STD_LIBRARY_DEBUG_ITERATORS != 0)
		#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_CXX_STDLIB_VCXX) && (defined(_ITERATOR_DEBUG_LEVEL) && (_ITERATOR_DEBUG_LEVEL > 0))
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
#elif ZTD_IS_ON(ZTD_CXX_STDLIB_VCXX) && defined(_ITERATOR_DEBUG_LEVEL) && (_ITERATOR_DEBUG_LEVEL > 0)
	#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_DEBUG_ITERATORS_EXIST_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_CXX_COMPILE_TIME_ENCODING_NAME)
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_GET_I_()         ZTD_CXX_COMPILE_TIME_ENCODING_NAME
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "set by the user with ZTD_CXX_COMPILE_TIME_ENCODING_NAME as (" ZTD_TOKEN_TO_STRING(ZTD_COMPILE_TIME_ENCODING_NAME) ")"
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_ON(ZTD_STD_LIBRARY_TEXT_ENCODING_ID)
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_GET_I_()         ::std::text_encoding::literal().name()
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "from std::text_encoding::literal().name()"
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME                  ZTD_DEFAULT_ON
#else
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_GET_I_()         ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_()
	#define ZTD_CXX_COMPILE_TIME_ENCODING_NAME_I_               ZTD_COMPILE_TIME_ENCODING_NAME_I_
#endif

#if defined(ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME)
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "set by the user with ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME as (" ZTD_TOKEN_TO_STRING(ZTD_COMPILE_TIME_WIDE_ENCODING_NAME) ")"
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_ON
#elif ZTD_IS_ON(ZTD_CXX) && ZTD_IS_ON(ZTD_STD_LIBRARY_TEXT_ENCODING_ID)
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         ::std::text_encoding::wide_literal().name()
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "from ::std::text_encoding::wide_literal().name()"
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#else
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_()
	#define ZTD_CXX_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_
#endif

// clang-format on

#endif
