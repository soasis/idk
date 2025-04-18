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

#ifndef ZTD_RANGES_DETAIL_ALGORITHM_HPP
#define ZTD_RANGES_DETAIL_ALGORITHM_HPP

#include <ztd/ranges/version.hpp>

#include <ztd/ranges/adl.hpp>
#include <ztd/ranges/iterator.hpp>
#include <ztd/ranges/range.hpp>
#include <ztd/ranges/subrange.hpp>
#include <ztd/ranges/unbounded.hpp>
#include <ztd/ranges/unreachable_sentinel.hpp>
#include <ztd/ranges/counted_iterator.hpp>

#include <ztd/idk/to_address.hpp>

#include <algorithm>
#include <cstring>

#include <ztd/prologue.hpp>

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __rng_detail {

		template <typename _InItOrRange, typename _OutItOrRange>
		struct __in_out_result {
			_InItOrRange in;
			_OutItOrRange out;

			template <typename _ArgInIt, typename _ArgOutIt,
				::std::enable_if_t<::std::is_convertible_v<const _InItOrRange&,
				     _ArgInIt>&& ::std::is_convertible_v<const _OutItOrRange&, _ArgOutIt>>* = nullptr>
			constexpr operator __in_out_result<_ArgInIt, _ArgOutIt>() const& {
				return { in, out };
			}

			template <typename _ArgInIt, typename _ArgOutIt,
				::std::enable_if_t<::std::is_convertible_v<const _InItOrRange&,
				     _ArgInIt>&& ::std::is_convertible_v<const _OutItOrRange&, _ArgOutIt>>* = nullptr>
			constexpr operator __in_out_result<_ArgInIt, _ArgOutIt>() & {
				return { in, out };
			}

			template <typename _ArgInIt, typename _ArgOutIt,
				::std::enable_if_t<::std::is_convertible_v<_InItOrRange,
				     _ArgInIt>&& ::std::is_convertible_v<_OutItOrRange, _ArgOutIt>>* = nullptr>
			constexpr operator __in_out_result<_ArgInIt, _ArgOutIt>() && {
				return { ::std::move(in), ::std::move(out) };
			}
		};

		template <typename _InItOrRange, typename _OutItOrRange>
		struct __current_last_result {
			_InItOrRange current;
			_OutItOrRange last;

			template <typename _ArgInIt, typename _ArgOutIt,
				::std::enable_if_t<::std::is_convertible_v<const _InItOrRange&,
				     _ArgInIt>&& ::std::is_convertible_v<const _OutItOrRange&, _ArgOutIt>>* = nullptr>
			constexpr operator __current_last_result<_ArgInIt, _ArgOutIt>() const& {
				return { current, last };
			}

			template <typename _ArgInIt, typename _ArgOutIt,
				::std::enable_if_t<::std::is_convertible_v<const _InItOrRange&,
				     _ArgInIt>&& ::std::is_convertible_v<const _OutItOrRange&, _ArgOutIt>>* = nullptr>
			constexpr operator __current_last_result<_ArgInIt, _ArgOutIt>() & {
				return { current, last };
			}

			template <typename _ArgInIt, typename _ArgOutIt,
				::std::enable_if_t<::std::is_convertible_v<_InItOrRange,
				     _ArgInIt>&& ::std::is_convertible_v<_OutItOrRange, _ArgOutIt>>* = nullptr>
			constexpr operator __current_last_result<_ArgInIt, _ArgOutIt>() && {
				return { ::std::move(current), ::std::move(last) };
			}
		};

	} // namespace __rng_detail
#if ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
	template <typename _InItOrRange, typename _OutItOrRange>
	using in_out_result = ::std::ranges::in_out_result<_InItOrRange, _OutItOrRange>;
#else
	template <typename _InItOrRange, typename _OutItOrRange>
	using in_out_result = __rng_detail::__in_out_result<_InItOrRange, _OutItOrRange>;
#endif

	template <typename _InItOrRange, typename _OutItOrRange>
	using current_last_result = __rng_detail::__current_last_result<_InItOrRange, _OutItOrRange>;

	namespace __rng_detail {

		template <typename _Iterator0, typename _Iterator1>
		constexpr _Iterator0 __reverse(_Iterator0 __first, _Iterator1 __last) noexcept {
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
			return ::std::ranges::reverse(::std::move(__first), ::std::move(__last));
#else
			if (__first == __last) {
				return __first;
			}
			--__last;
			if (__first == __last) {
				return __first;
			}

			// we have to start bringing them closer
			for (;;) {
				// we know these are different, so
				// do a swap
				::ztd::ranges::iter_swap(__first, __last);
				--__last;
				if (__first == __last) {
					break;
				}
				++__first;
				if (__first == __last) {
					break;
				}
				// otherwise, keep going
			}
			return __first;
#endif
		}

		template <typename _First, typename, typename _OutFirst>
		constexpr bool __copy_unsafe_noexcept() noexcept {
			return ::std::is_nothrow_assignable_v<iterator_reference_t<_OutFirst>, iterator_reference_t<_First>>;
		}

		template <typename _First, typename _Last, typename _OutFirst, typename _OutLast>
		constexpr bool __copy_noexcept() noexcept {
			if constexpr (is_sized_sentinel_for_v<_OutFirst, _OutLast>) {
				return __copy_unsafe_noexcept<_First, _Last, _OutFirst>()
					&& ::std::is_nothrow_assignable_v<iterator_reference_t<_OutFirst>,
					     iterator_reference_t<_First>>;
			}
			else {
				return ::std::is_nothrow_assignable_v<iterator_reference_t<_OutFirst>,
					iterator_reference_t<_First>>;
			}
		}

		template <typename _First, typename _FirstCount, typename _OutFirst>
		constexpr auto __copy_n_unsafe(_First __first, _FirstCount __size, _OutFirst __out_first) noexcept(
			__copy_unsafe_noexcept<_First, _FirstCount, _OutFirst>()) {
			using _ResultInIt = counted_iterator<_First>;
			using _InRange    = subrange<_ResultInIt, default_sentinel_t>;
			using _OutRange   = unbounded_view<_OutFirst>;
			using _Result     = in_out_result<_InRange, _OutRange>;
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
			if (!::std::is_constant_evaluated())
#else
			if (false)
#endif
			{
				using _ValueType    = iterator_value_type_t<_First>;
				using _OutValueType = iterator_value_type_t<_OutFirst>;
				if constexpr (is_iterator_contiguous_iterator_v<_First>
					&& is_iterator_contiguous_iterator_v<_OutFirst>
					&& ::std::has_unique_object_representations_v<_ValueType>
					&& ::std::has_unique_object_representations_v<_OutValueType>) {
					auto __first_ptr              = ::ztd::to_address(__first);
					auto __distance               = __size;
					::std::size_t __byte_distance = sizeof(_ValueType) * __distance;
					::std::size_t __out_distance  = __byte_distance / sizeof(_OutValueType);
					::std::memcpy(::ztd::to_address(__out_first), __first_ptr, __byte_distance);
					return _Result { _InRange(_ResultInIt(::std::move(__first) + __distance, 0), default_sentinel),
						_OutRange(::std::move(__out_first) + __out_distance) };
				}
			}
			_FirstCount __current_size = 0;
			for (; __current_size < __size; ++__first, (void)++__out_first, (void)++__current_size) {
				*__out_first = *__first;
			}
			return _Result { _InRange(_ResultInIt(::std::move(__first), 0), default_sentinel),
				_OutRange(::std::move(__out_first)) };
		}

		template <typename _First, typename _Last, typename _OutFirst>
		constexpr auto __copy_unsafe(_First __first, _Last __last, _OutFirst __out_first) noexcept(
			__copy_unsafe_noexcept<_First, _Last, _OutFirst>()) {
			using _InRange  = subrange<_First, _Last>;
			using _OutRange = unbounded_view<_OutFirst>;
			using _Result   = in_out_result<_InRange, _OutRange>;
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
			if (!::std::is_constant_evaluated())
#else
			if (false)
#endif
			{
				using _ValueType    = iterator_value_type_t<_First>;
				using _OutValueType = iterator_value_type_t<_OutFirst>;
				if constexpr (is_iterator_contiguous_iterator_v<_First>
					&& is_iterator_contiguous_iterator_v<_OutFirst>
					&& ::std::has_unique_object_representations_v<_ValueType>
					&& ::std::has_unique_object_representations_v<_OutValueType>) {
					auto __first_ptr              = ::ztd::to_address(__first);
					auto __distance               = __last - __first;
					::std::size_t __byte_distance = sizeof(_ValueType) * __distance;
					::std::size_t __out_distance  = __byte_distance / sizeof(_OutValueType);
					::std::memcpy(::ztd::to_address(__out_first), __first_ptr, __byte_distance);
					return _Result { _InRange(::std::move(__first) + __distance, ::std::move(__last)),
						_OutRange(::std::move(__out_first) + __out_distance) };
				}
			}

			for (; __first != __last; ++__first, (void)++__out_first) {
				*__out_first = *__first;
			}
			return _Result { _InRange(::std::move(__first), ::std::move(__last)),
				_OutRange(::std::move(__out_first)) };
		}

		template <typename _First, typename _FirstCount, typename _OutFirst, typename _OutFirstCount>
		constexpr auto __copy_n(_First __first, _FirstCount __size, _OutFirst __out_first,
			_OutFirstCount __out_size) noexcept(__copy_noexcept<_First, _FirstCount, _OutFirst, _OutFirstCount>()) {
			using _InRange  = subrange<counted_iterator<_First>, default_sentinel_t>;
			using _OutRange = subrange<counted_iterator<_OutFirst>, default_sentinel_t>;
			using _Result   = in_out_result<_InRange, _OutRange>;
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
			if (!::std::is_constant_evaluated())
#else
			if (false)
#endif
			{
				if constexpr (is_iterator_concept_or_better_v<::std::random_access_iterator_tag, _OutFirst>) {
					if (__size <= __out_size) {
						auto __result = __copy_n_unsafe(::std::move(__first), __size, ::std::move(__out_first));
						return _Result { ::std::move(__result.in),
							_OutRange(__result.out.begin(), __result.out.begin() + __size) };
					}
					else {
						auto __result
							= __copy_n_unsafe(::std::move(__first), __out_size, ::std::move(__out_first));
						iterator_difference_type_t<_OutFirst> __out_size_left
							= static_cast<iterator_difference_type_t<_OutFirst>>(__size - __out_size);
						return _Result { ::std::move(__result.in),
							_OutRange(
								{ ::std::move(__result.out).begin(), __out_size_left }, default_sentinel) };
					}
				}
			}

			decltype(__size) __current_count         = 0;
			decltype(__out_size) __current_out_count = 0;
			for (; __current_count < __size && __current_out_count != __out_size;
				++__first, (void)++__out_first, (void)++__current_count, (void)++__current_out_count) {
				*__out_first = *__first;
			}
			iterator_difference_type_t<_First> __size_left
				= static_cast<iterator_difference_type_t<_First>>(__size - __current_count);
			iterator_difference_type_t<_OutFirst> __out_size_left
				= static_cast<iterator_difference_type_t<_OutFirst>>(__out_size - __current_out_count);
			return _Result { _InRange({ ::std::move(__first), __size_left }, default_sentinel),
				_OutRange({ ::std::move(__out_first), __out_size_left }, default_sentinel) };
		}

		template <typename _First, typename _Last, typename _OutFirst, typename _OutLast>
		constexpr auto __copy(_First __first, _Last __last, _OutFirst __out_first, _OutLast __out_last) noexcept(
			__copy_noexcept<_First, _Last, _OutFirst, _OutLast>()) {
			using _InRange  = subrange<_First, _Last>;
			using _OutRange = subrange<_OutFirst, _OutLast>;
			using _Result   = in_out_result<_InRange, _OutRange>;
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
			if (!::std::is_constant_evaluated())
#else
			if (false)
#endif
			{
				if constexpr (is_sized_sentinel_for_v<_OutFirst, _OutLast>) {
					auto __out_size = __out_last - __out_first;
					auto __size     = __last - __first;
					if (__size <= __out_size) {
						auto __result
							= __copy_unsafe(::std::move(__first), ::std::move(__last), ::std::move(__out_first));
						return _Result { ::std::move(__result.in),
							_OutRange(::std::move(__result.out).begin(), ::std::move(__out_last)) };
					}
					else {
						auto __short_last = __first + __out_size;
						auto __result     = __copy_unsafe(
                                   ::std::move(__first), ::std::move(__short_last), ::std::move(__out_first));
						return _Result { ::std::move(__result.in),
							_OutRange(::std::move(__result.out).begin(), ::std::move(__out_last)) };
					}
				}
			}

			for (; __first != __last && __out_first != __out_last; ++__first, (void)++__out_first) {
				*__out_first = *__first;
			}
			return _Result { _InRange(::std::move(__first), ::std::move(__last)),
				_OutRange(::std::move(__out_first), ::std::move(__out_last)) };
		}

		template <typename _Input, typename _Output>
		constexpr auto __copy(_Input&& __input, _Output&& __output) noexcept(
			__copy_noexcept<ztd::ranges::range_const_iterator_t<_Input>, ztd::ranges::range_const_sentinel_t<_Input>,
			     ztd::ranges::range_iterator_t<_Output>, ztd::ranges::range_sentinel_t<_Output>>()) {
			return ::ztd::ranges::__rng_detail::__copy(::ztd::ranges::cbegin(std::forward<_Input>(__input)),
				::ztd::ranges::cend(__input), ::ztd::ranges::begin(std::forward<_Output>(__output)),
				::ztd::ranges::end(__output));
		}

		template <typename _First0, typename _Last0, typename _First1, typename _Last1>
		constexpr int __lexicographical_compare_three_way_basic(
			_First0 __first0, _Last0 __last0, _First1 __first1, _Last1 __last1) {
			for (; (__first0 != __last0) && (__first1 != __last1); ++__first0, (void)++__first1) {
				if (*__first0 < *__first1)
					return -1;
				if (*__first1 < *__first0)
					return 1;
			}
			bool __firstlast0_exhausted = (__first0 == __last0);
			bool __firstlast1_exhausted = (__first1 == __last1);
			if (__firstlast0_exhausted && __firstlast1_exhausted) {
				return 0;
			}
			else if (__firstlast0_exhausted) {
				return -1;
			}
			else {
				return 1;
			}
		}

		template <typename _First0, typename _Last0, typename _First1, typename _Last1>
		constexpr bool __lexicographical_compare(
			_First0 __first0, _Last0 __last0, _First1 __first1, _Last1 __last1) noexcept {
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
			return ::std::ranges::lexicographical_compare(
				::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
#else
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS)
			if constexpr (::std::is_same_v<_First0, _Last0> && ::std::is_same_v<_First1, _Last1>) {
				return ::std::lexicographical_compare(
					::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
			}
			else
#endif
			{
				for (; (__first0 != __last0) && (__first1 != __last1); ++__first0, (void)++__first1) {
					if (*__first0 < *__first1)
						return true;
					if (*__first1 < *__first0)
						return false;
				}
				return (__first0 == __last0) && (__first1 != __last1);
			}
#endif
		}

	} // namespace __rng_detail

	template <typename _It, typename _Last>
	constexpr auto distance(_It&& __it, _Last&& __last) noexcept {
		if constexpr (::ztd::ranges::is_iterator_concept_or_better_v<::std::random_access_iterator_tag, _It>) {
			return __last - __it;
		}
		else {
			::ztd::ranges::iterator_difference_type_t<_It> __diff = 0;
			for (; __it != __last; ++__it) {
				++__diff;
			}
			return __diff;
		}
	}

	template <typename _It, typename _Last, typename _Pred>
	constexpr current_last_result<_It, _Last> find_if(_It __first, _Last __last, _Pred __predicate) noexcept {
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
		if (!::std::is_constant_evaluated())
#else
		if (false)
#endif
		{
			// TODO: constexpr-unfriendly implementation when possible
		}
		for (; __first != __last; ++__first) {
			if (__predicate(*__first)) {
				return { ::std::move(__first), ::std::move(__last) };
			}
		}
		return { ::std::move(__first), ::std::move(__last) };
	}

	template <typename _It, typename _Last, typename _Ty, typename _Compare>
	constexpr current_last_result<_It, _Last> lower_bound(
		_It __first, _Last __last, _Ty&& __target_val, _Compare __compare) noexcept {
		using _Diff = ::ztd::ranges::iterator_difference_type_t<_It>;
#if ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
		if (!::std::is_constant_evaluated())
#else
		if (false)
#endif
		{
			if constexpr (::std::is_same_v<_It, _Last>) {
				auto __it = ::std::lower_bound(__first, __last, __target_val, __compare);
				return { ::std::move(__it), ::std::move(__last) };
			}
		}
		_It __it      = {};
		_Diff __count = ::ztd::ranges::distance(__first, __last);
		_Diff __step  = 0;
		while (__count > 0) {
			__it   = __first;
			__step = __count / 2;
			::ztd::ranges::iter_advance(__it, __step);
			if (__compare(*__it, __target_val)) {
				__first = ++__it;
				__count -= __step + 1;
			}
			else {
				__count = __step;
			}
		}
		return { ::std::move(__first), ::std::move(__last) };
	}

	template <typename _ItLast, typename _Ty, typename _Compare>
	constexpr auto lower_bound(_ItLast&& __it_last, _Ty&& __target_val, _Compare __compare) noexcept {
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
		return ::std::ranges::lower_bound(::ztd::ranges::cbegin(::std::forward<_ItLast>(__it_last)),
			::ztd::ranges::cend(__it_last), ::std::forward<_Ty>(__target_val), ::std::forward<_Compare>(__compare));
#else
		return ::ztd::ranges::lower_bound(::ztd::ranges::cbegin(::std::forward<_ItLast>(__it_last)),
			::ztd::ranges::cend(__it_last), ::std::forward<_Ty>(__target_val), ::std::forward<_Compare>(__compare));
#endif
	}

	template <typename _Iterator0, typename _Sentinel0, typename _Iterator1, typename _Sentinel1>
	constexpr bool equal(_Iterator0 __first0, _Sentinel0 __last0, _Iterator1 __first1, _Sentinel1 __last1) {
		// std lib does not take differing sentinels, which is kind of shitty tbh
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
		return ::std::ranges::equal(
			::std::move(__first0), ::std::move(__last0), ::std::move(__first1), ::std::move(__last1));
#else
		if (__first0 == __last0) {
			if (__first1 == __last1) {
				return true;
			}
			return false;
		}
		for (; __first0 != __last0; (void)++__first0, ++__first1) {
			if (__first1 == __last1) {
				return false;
			}
			if (*__first0 != *__first1) {
				return false;
			}
		}

		return __first1 == __last1;
#endif
	}

	template <typename _Iterator0, typename _Sentinel0, typename _Iterator1, typename _Sentinel1, typename _Predicate>
	constexpr bool equal(
		_Iterator0 __first0, _Sentinel0 __last0, _Iterator1 __first1, _Sentinel1 __last1, _Predicate&& __predicate) {
		// std lib does not take differing sentinels, which is kind of shitty tbh
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
		return ::std::ranges::equal(::std::move(__first0), ::std::move(__last0), ::std::move(__first1),
			::std::move(__last1), ::std::forward<_Predicate>(__predicate));
#else
		if (__first0 == __last0) {
			if (__first1 == __last1) {
				return true;
			}
			return false;
		}
		for (; __first0 != __last0; (void)++__first0, ++__first1) {
			if (__first1 == __last1) {
				return false;
			}
			if (!::std::forward<_Predicate>(__predicate)(*__first0, *__first1)) {
				return false;
			}
		}

		return __first1 == __last1;
#endif
	}

	template <typename _FirstLast0, typename _FirstLast1>
	constexpr bool equal(_FirstLast0&& __first_last0, _FirstLast1&& __first_last1) {
		// std lib does not take differing sentinels, which is kind of shitty tbh
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
		return ::std::ranges::equal(
			::std::forward<_FirstLast0>(__first_last0), ::std::forward<_FirstLast1>(__first_last1));
#else
		return ::ztd::ranges::equal(::ztd::ranges::cbegin(::std::forward<_FirstLast0>(__first_last0)),
			::ztd::ranges::cend(__first_last0), ::ztd::ranges::cbegin(::std::forward<_FirstLast1>(__first_last1)),
			::ztd::ranges::cend(__first_last1));
#endif
	}

	template <typename _FirstLast0, typename _FirstLast1, typename _Predicate>
	constexpr bool equal(_FirstLast0&& __first_last0, _FirstLast1&& __first_last1, _Predicate&& __predicate) {
		// std lib does not take differing sentinels, which is kind of shitty tbh
#if ZTD_IS_ON(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS) && ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
		return ::std::ranges::equal(::std::forward<_FirstLast0>(__first_last0),
			::std::forward<_FirstLast1>(__first_last1), ::std::forward<_Predicate>(__predicate));
#else
		return ::ztd::ranges::equal(::ztd::ranges::cbegin(::std::forward<_FirstLast0>(__first_last0)),
			::ztd::ranges::cend(__first_last0), ::ztd::ranges::cbegin(::std::forward<_FirstLast1>(__first_last1)),
			::ztd::ranges::cend(__first_last1), ::std::forward<_Predicate>(__predicate));
#endif
	}

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges

#include <ztd/epilogue.hpp>

#endif
