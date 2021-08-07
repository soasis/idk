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

#include <ztd/idk/version.h>
#include <ztd/idk/assert.h>

#if ZTD_IS_ON(ZTD_CXX_I_)
#include <cstddef>
#include <cstdbool>
#else
#include <stddef.h>
#include <stdbool.h>
#endif

// clang-format off
#if !defined(ZTD_IDK_C_SPAN_TYPE)
	#error "A type must be specified using ZTD_IDK_C_SPAN_TYPE when including the generation header."
#endif

#define ZTD_IDK_C_SPAN_TYPE_I_ ZTD_IDK_C_SPAN_TYPE

#if defined(ZTD_IDK_C_SPAN_SIZE_TYPE)
	#define ZTD_IDK_C_SPAN_SIZE_TYPE_I_ ZTD_IDK_C_SPAN_SIZE_TYPE
#else
	#define ZTD_IDK_C_SPAN_SIZE_TYPE_I_ size_t
#endif

#if defined(ZTD_IDK_C_SPAN_TYPE_NAME)
	#define ZTD_IDK_C_SPAN_NAME_SUFFIX_I_ ZTD_IDK_C_SPAN_TYPE_NAME
#else
	#if !defined(ZTD_IDK_C_SPAN_SIZE_TYPE)
		#define ZTD_IDK_C_SPAN_NAME_SUFFIX_I_ ZTD_IDK_C_SPAN_TYPE_I_
	#else
		#define ZTD_IDK_C_SPAN_NAME_SUFFIX_I_ ZTD_CONCAT_TOKENS_I_(ZTD_IDK_C_SPAN_TYPE_I_, ZTD_IDK_C_SPAN_SIZE_TYPE_I_)
	#endif
#endif

#if defined(ZTD_IDK_C_SPAN_NAME)
	#define ZTD_IDK_C_SPAN_FULL_NAME_I_ ZTD_IDK_C_SPAN_NAME
#else
	#define ZTD_IDK_C_SPAN_FULL_NAME_I_ ZTD_CONCAT_TOKENS_I_(c_span_, ZTD_IDK_C_SPAN_NAME_SUFFIX_I_)
#endif

#define ZTD_IDK_C_SPAN_PREFIX_I_(_PREFIX) ZTD_CONCAT_TOKENS_I_(_PREFIX, ZTD_IDK_C_SPAN_FULL_NAME_I_)
#define ZTD_IDK_C_SPAN_SUFFIX_I_(_SUFFIX) ZTD_CONCAT_TOKENS_I_(ZTD_IDK_C_SPAN_FULL_NAME_I_, _SUFFIX)
// clang-format on

typedef struct ZTD_IDK_C_SPAN_FULL_NAME_I_ {
	ZTD_IDK_C_SPAN_TYPE_I_* data;
	ZTD_IDK_C_SPAN_SIZE_TYPE_I_ size;
} ZTD_IDK_C_SPAN_FULL_NAME_I_;

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_FULL_NAME_I_ ZTD_IDK_C_SPAN_PREFIX_I_(make_)(
     ZTD_IDK_C_SPAN_TYPE_I_* __first, ZTD_IDK_C_SPAN_TYPE_I_* __last) {
	ZTD_IDK_C_SPAN_FULL_NAME_I_ __result;
	__result.data = __first;
	__result.size = __last - __first;
	return __result;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_FULL_NAME_I_ ZTD_IDK_C_SPAN_PREFIX_I_(make_sized_)(
     ZTD_IDK_C_SPAN_TYPE_I_* __first, ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __size) {
	ZTD_IDK_C_SPAN_FULL_NAME_I_ __result;
	__result.data = __first;
	__result.size = __size;
	return __result;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_* ZTD_IDK_C_SPAN_SUFFIX_I_(_data)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	return __span.data;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_SIZE_TYPE_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_size)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	return __span.size;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline bool ZTD_IDK_C_SPAN_SUFFIX_I_(_empty)(ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	return __span.size == 0;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_front)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	ZTD_ASSERT_MESSAGE_I_("c_span's size must be greater than zero", __span.size > 0);
	return *__span.data;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_back)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	ZTD_ASSERT_MESSAGE_I_("c_span's size must be greater than zero", __span.size > 0);
	return *(__span.data + __span.size - 1);
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_at)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span, ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __index) {
	ZTD_ASSERT_MESSAGE_I_("c_span's size must be greater than zero", __span.size > __index);
	return __span.data[__index];
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_* ZTD_IDK_C_SPAN_SUFFIX_I_(_ptr_at)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span, ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __index) {
	ZTD_ASSERT_MESSAGE_I_("index must be within c_span's boundaries", __index < __span.size);
	return __span.data + __index;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_* ZTD_IDK_C_SPAN_SUFFIX_I_(_maybe_ptr_at)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span, ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __index) {
	if (__index < __span.size)
		return __span.data + __index;
	return NULL;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_SIZE_TYPE_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_byte_size)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	return __span.size * sizeof(char);
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_* ZTD_IDK_C_SPAN_SUFFIX_I_(_begin)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	return __span.data;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_TYPE_I_* ZTD_IDK_C_SPAN_SUFFIX_I_(_end)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span) {
	return __span.data + __span.size;
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_FULL_NAME_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_subspan_at)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span, ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __offset_index,
     ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __size) {
	ZTD_ASSERT_MESSAGE_I_("c_span's size must be greater than or equal to the offset and size",
	     __span.size >= (__offset_index + __size));
	return ZTD_IDK_C_SPAN_PREFIX_I_(make_sized_)(__span.data + __offset_index, __size);
}

ZTD_C_FUNCTION_LINKAGE_I_ inline ZTD_IDK_C_SPAN_FULL_NAME_I_ ZTD_IDK_C_SPAN_SUFFIX_I_(_subspan)(
     ZTD_IDK_C_SPAN_FULL_NAME_I_ __span, ZTD_IDK_C_SPAN_SIZE_TYPE_I_ __offset_index) {
	ZTD_ASSERT_MESSAGE_I_(
	     "c_span's size must be greater than or equal to the offset and size", __span.size >= (__offset_index));
	return ZTD_IDK_C_SPAN_SUFFIX_I_(_subspan_at)(__span, __offset_index, __span.size - __offset_index);
}

//////
/// @file c_span.g.h
///
/// @brief The generation header for the C-style span type.
//////

//////
/// @addtogroup ztd_idk_c_c_span ztd.idk c_span functions
///
/// @{
//////

//////
/// @struct c_span_T
///
/// @brief A structured pointer which keeps its size type, which represents a NON-OWNING view into a buffer.
//////

//////
/// @var c_span_T::size
///
/// @brief A pointer to the region of data.
//////

//////
/// @var c_span_T::size
///
/// @brief The size of the region of data (in number of elements).
//////

//////
/// @fn c_span_T make_c_span_T(T* __first, T* __last)
///
/// @brief Create a c_span from two pointers which denote a region of memory.
///
/// @param[in] __first The start of the region of memory, inclusive.
/// @param[in] __last The end of the region of memory, non-inclusive.
///
/// @remarks Precondition:
/// - `__first` <  `__last` (`__first` is reachable from `__last`).
/// - `__first` and `__last` are part of the same storage and form a valid range.
//////

//////
/// @fn c_span_T make_sized_c_span_T(T* __first, size_t __size)
///
/// @brief Create a c_span from two pointers which denote a region of memory.
///
/// @param[in] __first The start of the region of memory, inclusive.
/// @param[in] __size The number of elements of the region of memory.
///
/// @remarks Precondition:
/// - `__first` and `__first + __size` are part of the same storage and form a valid range.
//////

//////
/// @fn T* c_span_T_data(c_span_T __span)
///
/// @brief Retrieves a pointer to the start of this span of memory.
///
/// @param[in] __span The "self" object.
//////

//////
/// @fn size_t c_span_T_size(c_span_T __span)
///
/// @brief Retrieves the size of this span of memory, in number of elements.
///
/// @param[in] __span The "self" object.
//////

//////
/// @fn bool c_span_T_empty(c_span_T __span)
///
/// @brief Returns whether or not this span is empty.
///
/// @param[in] __span The "self" object.
//////

//////
/// @fn T c_span_T_front(c_span_T __span)
///
/// @brief Retrieves the first element of this span of elements.
///
/// @param[in] __span The "self" object.
///
/// @remarks Preconditions:
/// - `c_span_T_size(__span) > 0`.
//////

//////
/// @fn T c_span_T_back(c_span_T __span)
///
/// @brief Retrieves the last element of this span of elements.
///
/// @remarks Preconditions:
/// - `c_span_T_size(__span) > 0`.
//////

//////
/// @fn T c_span_T_at(c_span_T __span, size_t __index)
///
/// @brief Retrieves the the element at the provided index.
///
/// @param[in] __span The "self" object.
/// @param[in] __index The offset into the span of elements to access.
///
/// @remarks Preconditions:
/// - The size is greater than the @c __index value.
//////

//////
/// @fn T* c_span_T_ptr_at(c_span_T __span, size_t __index)
///
/// @brief Retrieves the the element at the provided index.
///
/// @param[in] __span The "self" object.
/// @param[in] __index The offset into the span of elements to access.
///
/// @remarks Preconditions:
/// - The size is greater than the @c __index value.
//////

//////
/// @fn T* c_span_T_maybe_ptr_at(c_span_T __span, size_t __index)
///
/// @brief Retrieves the the element at the provided index.
///
/// @param[in] __span The "self" object.
/// @param[in] __index The offset into the span of elements to access.
///
/// @remarks This function checks size so there are no preconditions.
//////

//////
/// @fn size_t c_span_T_byte_size(c_span_T __span)
///
/// @brief Retrieves the size of this span of memory, in number of `unsigned char`s.
///
/// @param[in] __span The "self" object.
//////

//////
/// @fn c_span_T_begin(c_span_T __span)
///
/// @brief An iterator to the beginning of the span of elements.
///
/// @param[in] __span The "self" object.
//////

//////
/// @fn T* c_span_T_end(c_span_T __span)
///
/// @brief An iterator to the end of the span of elements.
///
/// @param[in] __span The "self" object.
//////

//////
/// @fn c_span_T c_span_T_subspan_at(c_span_T __span, size_t __offset_index, size_t __size)
///
/// @brief Creates a smaller span from this span, using the given offset into the span and the desired size.
///
/// @param[in] __span The "self" object.
/// @param[in] __offset_index The offset into the span.
/// @param[in] __size The size of the resulting span.
///
/// @remarks Precondition:
/// - `__span.size >= (__offset_index + __size)`.
//////

//////
/// @fn c_span_T c_span_T_subspan(c_span_T __span, size_t __offset_index)
///
/// @brief Creates a smaller span from this span, from the given offset. The resulting size is the offset minus the
/// `__span`'s current size.
///
/// @param[in] __span The "self" object.
/// @param[in] __offset_index The offset into the span.
///
/// @remarks Precondition:
/// - `__span.size >= __offset_index`.
//////

//////
/// @}
//////

// clang-format off
#undef ZTD_IDK_C_SPAN_TYPE
#undef ZTD_IDK_C_SPAN_TYPE_I_
#if defined(ZTD_IDK_C_SPAN_TYPE_NAME)
	#undef ZTD_IDK_C_SPAN_TYPE_NAME
#endif
#undef ZTD_IDK_C_SPAN_NAME_SUFFIX_I_

#if defined(ZTD_IDK_C_SPAN_SIZE_TYPE)
	#undef ZTD_IDK_C_SPAN_SIZE_TYPE
#endif
#undef ZTD_IDK_C_SPAN_SIZE_TYPE_I_

#if defined(ZTD_IDK_C_SPAN_NAME)
	#undef ZTD_IDK_C_SPAN_NAME
#endif

#undef ZTD_IDK_C_SPAN_CRIME_I_
#undef ZTD_IDK_C_SPAN_FULL_NAME_I_
#undef ZTD_IDK_C_SPAN_PREFIX_I_
#undef ZTD_IDK_C_SPAN_SUFFIX_I_
// clang-format on
