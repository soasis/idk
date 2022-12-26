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

#ifndef ZTD_RANGES_RECONSTRUCT_HPP
#define ZTD_RANGES_RECONSTRUCT_HPP

#include <ztd/ranges/version.hpp>

#include <ztd/ranges/subrange.hpp>
#include <ztd/ranges/adl.hpp>
#include <ztd/ranges/range.hpp>

#include <ztd/tag_invoke.hpp>
#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/empty_string.hpp>
#include <ztd/idk/hijack.hpp>
#include <ztd/idk/to_address.hpp>
#include <ztd/idk/span.hpp>

#include <utility>
#include <type_traits>
#include <string_view>

#include <ztd/prologue.hpp>

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __rng_detail {

		template <bool>
		class __reconstruct_fn;

		template <bool _Mutable, typename _It, typename _Sen>
		constexpr bool __is_tagless_iterator_reconstruct_noexcept() noexcept {
			if constexpr (((::std::is_class_v<_It> || ::std::is_enum_v<_It>)
				              || (::std::is_class_v<_Sen> || ::std::is_enum_v<_Sen>))
				&& is_tag_invocable_v<__reconstruct_fn<_Mutable>, _It, _Sen>) {
				return is_nothrow_tag_invocable_v<__reconstruct_fn<_Mutable>, _It, _Sen>;
			}
			else {
				return ::std::is_nothrow_constructible_v<subrange<remove_cvref_t<_It>, remove_cvref_t<_Sen>>, _It,
					_Sen>;
			}
		}

		template <bool _Mutable, typename _InPlace, typename _It, typename _Sen>
		constexpr bool __is_iterator_reconstruct_noexcept() noexcept {
			return is_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlace, _It, _Sen>
				? is_nothrow_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlace, _It, _Sen>
				: __is_tagless_iterator_reconstruct_noexcept<_Mutable, _It, _Sen>();
		}

		template <bool _Mutable, typename _InPlace, typename _Range, typename _It, typename _Sen>
		constexpr bool __is_range_iterator_reconstruct_noexcept() noexcept {
			return is_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlace, _Range, _It, _Sen>
				? is_nothrow_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlace, _Range, _It, _Sen>
				: __is_iterator_reconstruct_noexcept<_Mutable, _InPlace, _It, _Sen>();
		}

		template <bool _Mutable, typename _InPlace, typename _Range>
		constexpr bool __is_range_reconstruct_noexcept() noexcept {
			return __is_range_iterator_reconstruct_noexcept<_Mutable, _InPlace, _Range,
				::std::conditional_t<_Mutable, range_iterator_t<_Range>, range_const_iterator_t<_Range>>,
				::std::conditional_t<_Mutable, range_sentinel_t<_Range>, range_const_sentinel_t<_Range>>>();
		}

		template <bool _Mutable, typename _InPlaceOrIt, typename _RangeOrSen>
		constexpr bool __is_range_reconstruct_or_tagless_iterator_reconstruct_noexcept() noexcept {
			if constexpr (is_specialization_of_v<remove_cvref_t<_InPlaceOrIt>, ::std::in_place_type_t>) {
				return __is_range_reconstruct_noexcept<_Mutable, _InPlaceOrIt, _RangeOrSen>();
			}
			else {
				return __is_tagless_iterator_reconstruct_noexcept<_Mutable, _InPlaceOrIt, _RangeOrSen>();
			}
		}

		template <bool _Mutable>
		class __reconstruct_fn : public ::ztd::hijack::token<__reconstruct_fn<_Mutable>>,
			                    public ::ztd_hijack_global_token<__reconstruct_fn<_Mutable>> {
		public:
			template <typename _InPlaceTag, typename _It, typename _Sen>
			constexpr auto operator()(::std::in_place_type_t<_InPlaceTag> __inplace, _It&& __iterator,
				_Sen&& __sentinel) const noexcept(__is_iterator_reconstruct_noexcept<_Mutable,
				::std::in_place_type_t<_InPlaceTag>, _It, _Sen>()) {
				if constexpr (is_tag_invocable_v<__reconstruct_fn, ::std::in_place_type_t<_InPlaceTag>,
					              ::ztd::remove_cvref_t<_It>, ::ztd::remove_cvref_t<_Sen>>) {
					return ::ztd::tag_invoke(
						*this, __inplace, ::std::forward<_It>(__iterator), ::std::forward<_Sen>(__sentinel));
				}
				else {
					(void)__inplace;
					return (*this)(::std::forward<_It>(__iterator), ::std::forward<_Sen>(__sentinel));
				}
			}

			template <typename _InPlaceTag, typename _Range, typename _It, typename _Sen>
			constexpr decltype(auto) operator()(::std::in_place_type_t<_InPlaceTag> __inplace, _Range&& __range,
				_It&& __it, _Sen&& __sen) const noexcept(__is_range_iterator_reconstruct_noexcept<_Mutable,
				::std::in_place_type_t<_InPlaceTag>, _Range, _It, _Sen>()) {
				if constexpr (is_tag_invocable_v<__reconstruct_fn, ::std::in_place_type_t<_InPlaceTag>, _Range, _It,
					              _Sen>) {
					return ::ztd::tag_invoke(*this, __inplace, ::std::forward<_Range>(__range),
						::std::forward<_It>(__it), ::std::forward<_Sen>(__sen));
				}
				else {
					return (*this)(__inplace, ::std::forward<_It>(__it), ::std::forward<_Sen>(__sen));
				}
			}

			template <typename _InPlaceOrIt, typename _RangeOrSen>
			constexpr decltype(auto) operator()(
				_InPlaceOrIt&& __inplace_or_iterator, _RangeOrSen&& __range_or_sentinel) const
				noexcept(__is_range_reconstruct_or_tagless_iterator_reconstruct_noexcept<_Mutable, _InPlaceOrIt,
				     _RangeOrSen>()) {
				if constexpr (is_specialization_of_v<remove_cvref_t<_InPlaceOrIt>, ::std::in_place_type_t>) {
					if constexpr (is_tag_invocable_v<__reconstruct_fn, _InPlaceOrIt, _RangeOrSen>) {
						return ::ztd::tag_invoke(*this, ::std::forward<_InPlaceOrIt>(__inplace_or_iterator),
							::std::forward<_RangeOrSen>(__range_or_sentinel));
					}
					else {
						if constexpr (_Mutable) {
							return (*this)(::std::forward<_InPlaceOrIt>(__inplace_or_iterator),
								::std::forward<_RangeOrSen>(__range_or_sentinel),
								::ztd::ranges::begin(__range_or_sentinel),
								::ztd::ranges::end(__range_or_sentinel));
						}
						else {
							return (*this)(::std::forward<_InPlaceOrIt>(__inplace_or_iterator),
								::std::forward<_RangeOrSen>(__range_or_sentinel),
								::ztd::ranges::cbegin(__range_or_sentinel),
								::ztd::ranges::cend(__range_or_sentinel));
						}
					}
				}
				else if constexpr (((::std::is_class_v<_InPlaceOrIt> || ::std::is_enum_v<_InPlaceOrIt>)
					                   || (::std::is_class_v<_RangeOrSen> || ::std::is_enum_v<_RangeOrSen>))
					&& is_tag_invocable_v<__reconstruct_fn, _InPlaceOrIt, _RangeOrSen>) {
					return ::ztd::tag_invoke(*this, ::std::forward<_InPlaceOrIt>(__inplace_or_iterator),
						::std::forward<_RangeOrSen>(__range_or_sentinel));
				}
				else {
					// static_assert(ztd::always_false_v<_InPlaceOrIt>, "fuck off");
					return subrange<remove_cvref_t<_InPlaceOrIt>, remove_cvref_t<_RangeOrSen>>(
						::std::forward<_InPlaceOrIt>(__inplace_or_iterator),
						::std::forward<_RangeOrSen>(__range_or_sentinel));
				}
			}
		};

		template <bool _Mutable, typename _InPlaceOrIt, typename _RangeOrSen, typename... _Args>
		static constexpr bool __is_reconstructible() noexcept {
			if constexpr (sizeof...(_Args) == 0) {
				if constexpr (is_specialization_of_v<remove_cvref_t<_InPlaceOrIt>, ::std::in_place_type_t>) {
					if constexpr (is_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlaceOrIt, _RangeOrSen>) {
						return true;
					}
					else {
						if constexpr (_Mutable) {
							return __is_reconstructible<_Mutable, _InPlaceOrIt, _RangeOrSen,
								::ztd::ranges::range_iterator_t<_RangeOrSen>,
								::ztd::ranges::range_sentinel_t<_RangeOrSen>>();
						}
						else {
							return __is_reconstructible<_Mutable, _InPlaceOrIt, _RangeOrSen,
								::ztd::ranges::range_const_iterator_t<_RangeOrSen>,
								::ztd::ranges::range_const_sentinel_t<_RangeOrSen>>();
						}
					}
				}
				else if constexpr (((::std::is_class_v<_InPlaceOrIt> || ::std::is_enum_v<_InPlaceOrIt>)
					                   || (::std::is_class_v<_RangeOrSen> || ::std::is_enum_v<_RangeOrSen>))
					&& is_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlaceOrIt, _RangeOrSen>) {
					return true;
				}
				else {
					return false;
				}
			}
			else if constexpr (sizeof...(_Args) == 1) {
				if constexpr (is_tag_invocable_v<__reconstruct_fn<_Mutable>, ::ztd::remove_cvref_t<_InPlaceOrIt>,
					              ::ztd::remove_cvref_t<_RangeOrSen>, ::ztd::remove_cvref_t<_Args>...>) {
					return true;
				}
				else {
					return __is_reconstructible<_Mutable, _RangeOrSen, _Args...>();
				}
			}
			else if constexpr (sizeof...(_Args) == 2) {
				if constexpr (is_tag_invocable_v<__reconstruct_fn<_Mutable>, _InPlaceOrIt, _RangeOrSen, _Args...>) {
					return true;
				}
				else {
					return __is_reconstructible<_Mutable, _InPlaceOrIt, _Args...>();
				}
			}
			else {
				static_assert(::ztd::always_false_constant_v<bool, _Mutable>,
					"improper arguments to is_cascade_reconstructible");
			}
		}

		template <bool _Mutable, typename _InPlaceOrIt, typename _RangeOrSen, typename... _Args>
		inline constexpr bool __is_reconstructible_noexcept() noexcept {
			if constexpr (sizeof...(_Args) == 0) {
				if constexpr (is_specialization_of_v<remove_cvref_t<_InPlaceOrIt>, ::std::in_place_type_t>) {
					return __is_range_reconstruct_noexcept<_Mutable, _InPlaceOrIt, _RangeOrSen>();
				}
				else {
					return __is_tagless_iterator_reconstruct_noexcept<_Mutable, _InPlaceOrIt, _RangeOrSen>();
				}
			}
			else if constexpr (sizeof...(_Args) == 1) {
				return __is_iterator_reconstruct_noexcept<_Mutable, _InPlaceOrIt, _RangeOrSen, _Args...>();
			}
			else if constexpr (sizeof...(_Args) == 2) {
				return __is_range_iterator_reconstruct_noexcept<_Mutable, _InPlaceOrIt, _RangeOrSen, _Args...>();
			}
			else {
				static_assert(::ztd::always_false_constant_v<bool, _Mutable>,
					"improper arguments to is_cascade_reconstructible_noexcept");
			}
		}

	} // namespace __rng_detail

	inline namespace __fn {
		//////
		/// @brief An implementation of the P1664 (https://wg21.link/p1664 |
		/// https://thephd.dev/_vendor/future_cxx/papers/d1664.html) reconstructible ranges extension point. It is
		/// derives from ztd::hijack::token in order for outside implementations to have a common place to put
		/// reconstruction for things outside of their control, without needing to place it in the global namespace or
		/// the immediate ztd::ranges namespace, where there are too many other types that could force asking more
		/// questions about what is in the list for ADL and drive up compile-times.
		inline constexpr __rng_detail::__reconstruct_fn<true> reconstruct = {};

		//////
		/// @brief Similar to
		inline constexpr __rng_detail::__reconstruct_fn<false> const_reconstruct = {};
	} // namespace __fn

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges

namespace ztd { namespace hijack {

	namespace __hj_detail {
		template <typename _Ty, typename _It, typename _Sen>
		constexpr bool __is_span_reconstructible() noexcept {
			using _ItElementTy = ::std::remove_reference_t<::ztd::ranges::iterator_reference_t<_It>>;
			constexpr const bool __initial_check
				= ::ztd::is_non_derived_compatible_pointer_v<_ItElementTy, _Ty> // cf
				&& ::ztd::ranges::is_iterator_contiguous_iterator_v<_It>        // cf
				&& ((::std::is_const_v<_ItElementTy>) ? std::is_const_v<_Ty> : true);
			if constexpr (__initial_check) {
				if constexpr (::ztd::ranges::is_sized_sentinel_for_v<_It, _Sen>) {
					return true;
				}
				else {
					return ::std::is_convertible_v<_Sen, ::std::size_t>;
				}
			}
			else {
				return false;
			}
		}

		template <typename _Ty, typename _It, typename _Sen>
		constexpr bool __is_string_view_reconstructible() noexcept {
			if constexpr (!::ztd::ranges::is_iterator_contiguous_iterator_v<_It>) {
				return false;
			}
			else {
				if constexpr (::ztd::ranges::is_sized_sentinel_for_v<_It, _Sen>) {
					return true;
				}
				else {
					return ::std::is_convertible_v<_Sen, ::std::size_t>;
				}
			}
		}
	} // namespace __hj_detail

	template <typename _Ty, decltype(::ztd::dynamic_extent) _Extent, typename _It, typename _Sen,
		::std::enable_if_t<__hj_detail::__is_span_reconstructible<_Ty, _It, _Sen>()>* = nullptr>
	constexpr ::ztd::span<_Ty> tag_invoke(ztd::tag_t<::ztd::ranges::reconstruct>,
		::std::in_place_type_t<::ztd::span<_Ty, _Extent>>, _It __iterator, _Sen __sentinel) noexcept {
		if constexpr (::ztd::ranges::is_sized_sentinel_for_v<_It, _Sen>) {
			if constexpr (::ztd::ranges::is_iterator_contiguous_iterator_v<_Sen>) {
				auto __iterator_address = ::ztd::to_address(__iterator);
				auto __sentinel_address = ::ztd::to_address(__sentinel);
				return ::ztd::span<_Ty>(
					__iterator_address, static_cast<::std::size_t>(__sentinel_address - __iterator_address));
			}
			else {
				auto __iterator_address = ::ztd::to_address(__iterator);
				return ::ztd::span<_Ty>(__iterator_address, static_cast<::std::size_t>(__sentinel - __iterator));
			}
		}
		else {
			auto __iterator_address = ::ztd::to_address(__iterator);
			return ::ztd::span<_Ty>(__iterator_address, __sentinel);
		}
	}

	template <typename _Ty, typename _Traits, typename _It, typename _Sen,
		::std::enable_if_t<__hj_detail::__is_string_view_reconstructible<_Ty, _It, _Sen>()>* = nullptr>
	constexpr ::std::basic_string_view<_Ty, _Traits> tag_invoke(ztd::tag_t<::ztd::ranges::reconstruct>,
		::std::in_place_type_t<::std::basic_string_view<_Ty, _Traits>>, _It __iterator, _Sen __sentinel) noexcept {
		using _SizeType = typename ::std::basic_string_view<_Ty, _Traits>::size_type;
		if constexpr (::ztd::ranges::is_sized_sentinel_for_v<_It, _Sen>) {
			_SizeType __ptr_size = static_cast<_SizeType>(__sentinel - __iterator);
#if ZTD_IS_ON(ZTD_STD_LIBRARY_DEBUG_ITERATORS)
			if (__ptr_size == static_cast<_SizeType>(0)) {
				const auto& __empty_str = empty_string<_Ty>();
				return ::std::basic_string_view<_Ty, _Traits>(__empty_str + 0, 0);
			}
#endif
			return ::std::basic_string_view<_Ty, _Traits>(::ztd::to_address(__iterator), __ptr_size);
		}
		else {
#if ZTD_IS_ON(ZTD_STD_LIBRARY_DEBUG_ITERATORS)
			if (static_cast<_SizeType>(__sentinel) == static_cast<_SizeType>(0)) {
				const auto& __empty_str = empty_string<_Ty>();
				return ::std::basic_string_view<_Ty, _Traits>(__empty_str + 0, 0);
			}
#endif
			return ::std::basic_string_view<_Ty, _Traits>(
				::ztd::to_address(__iterator), static_cast<_SizeType>(__sentinel));
		}
	}

}} // namespace ztd::hijack

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	template <typename _It, typename _Sen>
	inline constexpr bool is_tagless_iterator_reconstructible_v
		= ((::std::is_class_v<_It> || ::std::is_enum_v<_It>)           // cf
		       || (::std::is_class_v<_Sen> || ::std::is_enum_v<_Sen>)) // cf
		&& is_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _It, _Sen>;

	template <typename _Tag, typename _It, typename _Sen>
	inline constexpr bool is_iterator_reconstructible_v
		= is_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _Tag, _It, _Sen>;

	template <typename _Tag, typename _Range, typename _It, typename _Sen>
	inline constexpr bool is_range_iterator_reconstructible_v
		= is_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _Tag, _Range, _It, _Sen>;

	template <typename _Tag, typename _Range>
	inline constexpr bool is_range_reconstructible_v
		= is_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _Tag, _Range>;

	template <typename... _Args>
	inline constexpr bool is_reconstructible_v = __rng_detail::__is_reconstructible<true, _Args...>();

	template <typename _It, typename _Sen>
	inline constexpr bool is_nothrow_tagless_iterator_reconstructible_v
		= ((::std::is_class_v<_It> || ::std::is_enum_v<_It>)           // cf
		       || (::std::is_class_v<_Sen> || ::std::is_enum_v<_Sen>)) // cf
		&& is_nothrow_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _It, _Sen>;

	template <typename _Tag, typename _It, typename _Sen>
	inline constexpr bool is_nothrow_iterator_reconstructible_v
		= is_nothrow_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _Tag, _It, _Sen>;

	template <typename _Tag, typename _Range, typename _It, typename _Sen>
	inline constexpr bool is_nothrow_range_iterator_reconstructible_v
		= is_nothrow_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _Tag, _Range, _It, _Sen>;

	template <typename _It, typename _Sen>
	inline constexpr bool is_nothrow_range_reconstructible_v
		= is_nothrow_tag_invocable_v<__rng_detail::__reconstruct_fn<true>, _It, _Sen>;

	template <typename... _Args>
	inline constexpr bool is_nothrow_reconstructible_v = __rng_detail::__is_reconstructible_noexcept<true, _Args...>();

	template <typename _Range, typename _It = ranges::range_iterator_t<unwrap_remove_reference_t<_Range>>,
		typename _Sen = ranges::range_sentinel_t<unwrap_remove_reference_t<_Range>>>
	using reconstruct_t = decltype(ranges::reconstruct(
		::std::in_place_type<unwrap_remove_cvref_t<_Range>>, ::std::declval<_It>(), ::std::declval<_Sen>()));

	template <typename _Range>
	using range_reconstruct_t = decltype(ranges::reconstruct(
		::std::in_place_type<unwrap_remove_cvref_t<_Range>>, ::std::declval<_Range>()));

	template <typename _Tag, typename _Range = _Tag>
	using tag_range_reconstruct_t
		= decltype(ranges::reconstruct(::std::in_place_type<unwrap_remove_cvref_t<_Tag>>, ::std::declval<_Range>()));

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges

#include <ztd/epilogue.hpp>

#endif
