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

#ifndef ZTD_IDK_DETAIL_SPAN_IMPLEMENTATION_HPP
#define ZTD_IDK_DETAIL_SPAN_IMPLEMENTATION_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/to_address.hpp>
#include <ztd/idk/is_array.hpp>
#include <ztd/idk/explicit.hpp>
#include <ztd/idk/contiguous_iterator_tag.hpp>
#include <ztd/idk/assert.hpp>
#include <ztd/ranges/adl.hpp>
#include <ztd/ranges/range.hpp>
#include <ztd/ranges/iterator.hpp>

#include <array>
#include <iterator>
#include <utility>
#include <initializer_list>
#include <cstdlib>
#include <cstddef>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __span_detail {
		inline constexpr ::std::size_t __dynamic_extent = static_cast<::std::size_t>(-1LL);

		class __rng_key_t {
		} constexpr __rng_key = {};

		template <typename _Ty, ::std::size_t _Extent>
		class span;

		template <typename _Ty>
		class __is_span : public ::std::false_type { };

		template <typename _Ty, ::std::size_t _N>
		class __is_span<::ztd::__span_detail::span<_Ty, _N>> : public ::std::true_type { };

		template <typename _Ty>
		inline constexpr bool __is_span_v = ::ztd::__span_detail::__is_span<_Ty>::value;

		template <::std::size_t _Extent>
		class __span_size {
		public:
			constexpr __span_size() noexcept = default;
			constexpr __span_size(::std::size_t __size) noexcept {
				ZTD_CONSTEXPR_ASSERT(__size <= _Extent);
			}

			constexpr ::std::size_t size() const noexcept {
				return _Extent;
			}
		};

		template <>
		class __span_size<__dynamic_extent> {
		public:
			constexpr __span_size() noexcept : _M_size(0) {
			}
			constexpr __span_size(::std::size_t __size) noexcept : _M_size(__size) {
			}

			constexpr ::std::size_t size() const noexcept {
				return this->_M_size;
			}

			std::size_t _M_size;
		};

		template <typename _Ty, ::std::size_t _Extent = ::ztd::__span_detail::__dynamic_extent>
		class span : public __span_size<_Extent> {
		private:
			using __base_span_size = __span_size<_Extent>;

		public:
			using pointer                            = _Ty*;
			using element_type                       = _Ty;
			using value_type                         = ::std::remove_const_t<element_type>;
			using iterator                           = _Ty*;
			using reference                          = ::std::add_lvalue_reference_t<_Ty>;
			using const_reference                    = reference;
			using const_iterator                     = iterator;
			using reverse_iterator                   = ::std::reverse_iterator<iterator>;
			using const_reverse_iterator             = ::std::reverse_iterator<const_iterator>;
			using difference_type                    = ::std::ptrdiff_t;
			using size_type                          = ::std::size_t;
			using iterator_tag                       = ::ztd::contiguous_iterator_tag;
			using iterator_concept                   = ::ztd::contiguous_iterator_tag;
			inline static constexpr size_type extent = _Extent;

			template <::std::size_t _Ex0                                                              = extent,
			     ::std::enable_if_t<(_Ex0 == 0) || (_Ex0 == ::ztd::__span_detail::__dynamic_extent)>* = nullptr>
			constexpr span() noexcept : __base_span_size(), _M_data() {
			}
			constexpr span(const span&) noexcept = default;
			constexpr span(span&&) noexcept      = default;

			template <::std::size_t _N,
			     ::std::enable_if_t<(extent == _N) || (extent == ::ztd::__span_detail::__dynamic_extent)>* = nullptr>
			constexpr span(::ztd::type_identity_t<element_type> (&__arr)[_N]) noexcept
			: __base_span_size(_N), _M_data(__arr) {
			}

			template <typename _Elem, ::std::size_t _N,
			     ::std::enable_if_t<::ztd::is_non_derived_compatible_pointer_v<_Elem, element_type>
			          && ((extent == _N) || (extent == ::ztd::__span_detail::__dynamic_extent))>* = nullptr>
			constexpr span(::std::array<_Elem, _N>& __arr) noexcept : __base_span_size(_N), _M_data(__arr.data()) {
			}

			template <typename _Elem, ::std::size_t _N,
			     ::std::enable_if_t<::ztd::is_non_derived_compatible_pointer_v<_Elem, element_type>
			          && ((extent == _N) || (extent == ::ztd::__span_detail::__dynamic_extent))>* = nullptr>
			constexpr span(const ::std::array<_Elem, _N>& __arr) noexcept
			: __base_span_size(_N), _M_data(__arr.data()) {
			}

			template <typename _Elem,
			     ::std::enable_if_t<::ztd::is_non_derived_compatible_pointer_v<_Elem, element_type>>* = nullptr>
			constexpr span(::std::initializer_list<_Elem> __il) noexcept
			: __base_span_size(__il.size()), _M_data(__il.begin()) {
			}

			template <typename _Ty0, std::size_t _Ex0,
			     ::std::enable_if_t<(extent == ::ztd::__span_detail::__dynamic_extent
			                             || _Ex0 == ::ztd::__span_detail::__dynamic_extent || _Ex0 == extent) // cf
			          && ::ztd::is_non_derived_compatible_pointer_v<_Ty0, element_type>                       // cf
			          && !::std::is_same_v<span, ::ztd::__span_detail::span<_Ty0, _Ex0>>                      // cf
			          >* = nullptr>
			constexpr span(const ::ztd::__span_detail::span<_Ty0, _Ex0>& __source) noexcept
			: __base_span_size(__source.size()), _M_data(__source.data()) {
			}

			template <typename _Range,
			     ::std::enable_if_t<!::ztd::is_std_or_c_array_v<::ztd::remove_cvref_t<_Range>> // cf
			          && !::ztd::is_initializer_list_v<::ztd::remove_cvref_t<_Range>>          // cf
			          && !::ztd::__span_detail::__is_span_v<::ztd::remove_cvref_t<_Range>>     // cf
			          >* = nullptr>
			ZTD_EXPLICIT(extent != ::ztd::__span_detail::__dynamic_extent)
			constexpr span(_Range&& __range) noexcept : span(__rng_key, __rng_key, ::std::forward<_Range>(__range)) {
			}

			template <typename _ItFirst, typename _ItLast,
			     ::std::enable_if_t<                                                          // cf
			          ::ztd::ranges::is_sized_sentinel_for_v<_ItFirst, _ItLast>               // cf
			               && ::ztd::ranges::is_iterator_random_access_iterator_v<_ItLast>    // cf
			                    && ::ztd::ranges::is_iterator_contiguous_iterator_v<_ItFirst> // cf
			          && !::std::is_convertible_v<_ItLast, size_type>                         // cf
			          >* = nullptr>
			ZTD_EXPLICIT(extent != ::ztd::__span_detail::__dynamic_extent)
			constexpr span(_ItFirst __first, _ItLast __last) noexcept
			: __base_span_size(static_cast<size_type>(::std::distance(__first, __last)))
			, _M_data(::ztd::to_address(__first)) {
			}

			constexpr span(::std::nullptr_t, size_type __count) noexcept
			: __base_span_size(__count), _M_data(nullptr) {
			}

			template <typename _It,
			     ::std::enable_if_t<::ztd::ranges::is_iterator_contiguous_iterator_v<_It>            // cf
			               && ::ztd::is_non_derived_compatible_pointer_v<                            // cf
			                    ::std::remove_reference_t<::ztd::ranges::iterator_reference_t<_It>>, // cf
			                    element_type                                                         // cf
			                    >                                                                    // cf
			          >* = nullptr>
			ZTD_EXPLICIT(extent != ::ztd::__span_detail::__dynamic_extent)
			constexpr span(_It __first, size_type __count) noexcept
			: __base_span_size(__count), _M_data(::ztd::to_address(__first)) {
			}

			constexpr span& operator=(const span&) noexcept = default;
			constexpr span& operator=(span&&) noexcept      = default;

			constexpr bool empty() const noexcept {
				return this->size() == 0;
			}

			constexpr pointer data() const noexcept {
				return this->_M_data;
			}

			constexpr iterator begin() const noexcept {
				return this->_M_data;
			}

			constexpr iterator end() const noexcept {
				return this->_M_data + this->size();
			}

			constexpr const_iterator cbegin() const noexcept {
				return this->_M_data;
			}

			constexpr const_iterator cend() const noexcept {
				return this->_M_data + this->size();
			}

			constexpr iterator rbegin() const noexcept {
				return reverse_iterator(this->end());
			}

			constexpr reverse_iterator rend() const noexcept {
				return reverse_iterator(this->begin());
			}

			constexpr const_reverse_iterator crbegin() const noexcept {
				return const_reverse_iterator(this->cend());
			}

			constexpr const_reverse_iterator crend() const noexcept {
				return const_reverse_iterator(this->cbegin());
			}

			constexpr reference front() noexcept {
				ZTD_CONSTEXPR_ASSERT(this->size() > 0);
				return this->_M_data[0];
			}

			constexpr const_reference front() const noexcept {
				ZTD_CONSTEXPR_ASSERT(this->size() > 0);
				return this->_M_data[0];
			}

			constexpr reference back() noexcept {
				ZTD_CONSTEXPR_ASSERT(this->size() > 0);
				return this->_M_data[this->size() - 1];
			}

			constexpr const_reference back() const noexcept {
				ZTD_CONSTEXPR_ASSERT(this->size() > 0);
				return this->_M_data[this->size() - 1];
			}

			constexpr reference operator[](size_type __index) const noexcept {
				ZTD_CONSTEXPR_ASSERT(__index < this->size());
				return this->_M_data[__index];
			}

			constexpr size_type size() const noexcept {
				return this->__base_span_size::size();
			}

			constexpr size_type size_bytes() const noexcept {
				return (this->size() * sizeof(element_type)) / sizeof(unsigned char);
			}

			template <::std::size_t _Count>
			constexpr span<element_type, _Count> first() const noexcept {
				if constexpr (extent == ::ztd::__span_detail::__dynamic_extent) {
					ZTD_CONSTEXPR_ASSERT(_Count <= this->size());
				}
				else {
					static_assert(extent == ::ztd::__span_detail::__dynamic_extent || (_Count <= extent));
				}
				return span<element_type, _Count>(this->data(), _Count);
			}

			constexpr span<element_type, ::ztd::__span_detail::__dynamic_extent> first(
			     size_type __count) const noexcept {
				ZTD_CONSTEXPR_ASSERT(__count <= this->size());
				return span<element_type, ::ztd::__span_detail::__dynamic_extent>(this->data(), __count);
			}

			template <::std::size_t _Count>
			constexpr span<element_type, _Count> last() const {
				if constexpr (extent == ::ztd::__span_detail::__dynamic_extent) {
					ZTD_CONSTEXPR_ASSERT(_Count <= this->size());
				}
				else {
					static_assert(extent == ::ztd::__span_detail::__dynamic_extent || (_Count <= extent));
				}
				// NOTE: should we be `static_assert`ing the inability to use __dynamic_extent as a _Count?
				// or is it just so improbable it doesn't matter?
				return span<element_type, _Count>(this->_M_data + (this->size() - _Count), _Count);
			}

			constexpr span<element_type, ::ztd::__span_detail::__dynamic_extent> last(size_type __count) const {
				ZTD_CONSTEXPR_ASSERT(__count <= this->size());
				return span<element_type, ::ztd::__span_detail::__dynamic_extent>(
				     this->_M_data + (this->size() - __count), __count);
			}

			template <::std::size_t _Offset, std::size_t _Count = ::ztd::__span_detail::__dynamic_extent>
			constexpr auto subspan() const {
				static_assert(extent == ::ztd::__span_detail::__dynamic_extent || (extent <= _Offset));
				if constexpr (_Count == ::ztd::__span_detail::__dynamic_extent) {
					return span<element_type, ::ztd::__span_detail::__dynamic_extent>(
					     this->_M_data + _Offset, this->size() - _Offset);
				}
				else {
					static_assert(extent == ::ztd::__span_detail::__dynamic_extent
					     || ((extent <= _Offset) && ((extent - _Offset) >= _Count)));
					return span<element_type, _Count>(this->_M_data + _Offset, _Count);
				}
			}

			constexpr span<element_type, ::ztd::__span_detail::__dynamic_extent> subspan(
			     size_type __offset, size_type __count = ::ztd::__span_detail::__dynamic_extent) const {
				if (__count == ::ztd::__span_detail::__dynamic_extent) {
					return span<element_type, ::ztd::__span_detail::__dynamic_extent>(
					     this->_M_data + __offset, this->size() - __offset);
				}
				else {
					ZTD_CONSTEXPR_ASSERT(this->size() <= __offset);
					ZTD_CONSTEXPR_ASSERT((this->size() - __offset) >= __count);
					return span<element_type, ::ztd::__span_detail::__dynamic_extent>(
					     this->_M_data + __offset, __count);
				}
			}

		private:
			_Ty* _M_data;

			template <typename _Range,
			     ::std::enable_if_t<
			          ::ztd::ranges::is_range_v<_Range>                                                        // cf
			               && ::ztd::ranges::is_range_contiguous_range_v<_Range>                               // cf
			                    && ::ztd::ranges::is_sized_range_v<_Range>                                     // cf
			                         && ::ztd::is_non_derived_compatible_pointer_v<                            // cf
			                              ::std::remove_reference_t<::ztd::ranges::range_reference_t<_Range>>, // cf
			                              element_type>                                                        // cf
			          && (::std::is_lvalue_reference_v<_Range>                                                 // cf
			                    ? (::std::is_const_v<::std::remove_reference_t<_Range>>                        // cf
			                              ? (::std::is_const_v<element_type>)
			                              : true)
			                    : (true)) // cf
			          >* = nullptr>
			ZTD_EXPLICIT(extent != ::ztd::__span_detail::__dynamic_extent)
			constexpr span(
			     ::ztd::__span_detail::__rng_key_t, ::ztd::__span_detail::__rng_key_t, _Range&& __range) noexcept
			: __base_span_size(::ztd::ranges::size(__range)), _M_data(::ztd::ranges::data(__range)) {
			}
		};

		template <typename _It, typename _ItOrSize>
		span(_It, _ItOrSize) -> span<::std::remove_reference_t<::ztd::ranges::iterator_reference_t<_It>>>;

		template <typename _Ty, ::std::size_t _Ex>
		span(_Ty (&)[_Ex]) -> span<_Ty, _Ex>;

		template <typename _Ty, ::std::size_t _Ex>
		span(std::array<_Ty, _Ex>&) -> span<_Ty, _Ex>;

		template <typename _Ty, ::std::size_t _Ex>
		span(const std::array<_Ty, _Ex>&) -> span<const _Ty, _Ex>;

		template <typename _Range>
		span(_Range&&) -> span<::std::remove_reference_t<::ztd::ranges::range_reference_t<_Range>>>;

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator==(span<_Ty1, _Ex1> const& __left, span<_Ty2, _Ex2> const& __right) {
			return (__left.size() == __right.size() && std::equal(__left.begin(), __left.end(), __right.begin()));
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator==(
		     ::ztd::type_identity_t<span<_Ty1, _Ex1>> const& __left, span<_Ty2, _Ex2> const& __right) {
			return (__left.size() == __right.size() && std::equal(__left.begin(), __left.end(), __right.begin()));
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator==(
		     span<_Ty1, _Ex1> const& __left, ::ztd::type_identity_t<span<_Ty2, _Ex2>> const& __right) {
			return (__left.size() == __right.size() && std::equal(__left.begin(), __left.end(), __right.begin()));
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator<(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return ::std::lexicographical_compare(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator<(::ztd::type_identity_t<::ztd::__span_detail::span<_Ty1, _Ex1>> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return ::std::lexicographical_compare(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator<(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::type_identity_t<::ztd::__span_detail::span<_Ty2, _Ex2>> const& __right) noexcept {
			return ::std::lexicographical_compare(__left.cbegin(), __left.cend(), __right.cbegin(), __right.cend());
		}


		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator!=(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return !(__left == __right);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator!=(::ztd::type_identity_t<::ztd::__span_detail::span<_Ty1, _Ex1>> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return !(__left == __right);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator!=(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::type_identity_t<::ztd::__span_detail::span<_Ty2, _Ex2>> const& __right) noexcept {
			return !(__left == __right);
		}


		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator<=(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return !(__right < __left);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator<=(::ztd::type_identity_t<::ztd::__span_detail::span<_Ty1, _Ex1>> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return !(__right < __left);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator<=(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::type_identity_t<::ztd::__span_detail::span<_Ty2, _Ex2>> const& __right) noexcept {
			return !(__right < __left);
		}


		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator>(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return (__right < __left);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator>(::ztd::type_identity_t<::ztd::__span_detail::span<_Ty1, _Ex1>> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return (__right < __left);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator>(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::type_identity_t<::ztd::__span_detail::span<_Ty2, _Ex2>> const& __right) noexcept {
			return (__right < __left);
		}


		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator>=(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return !(__left < __right);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator>=(::ztd::type_identity_t<::ztd::__span_detail::span<_Ty1, _Ex1>> const& __left,
		     ::ztd::__span_detail::span<_Ty2, _Ex2> const& __right) noexcept {
			return !(__left < __right);
		}

		template <typename _Ty1, ::std::size_t _Ex1, typename _Ty2, ::std::size_t _Ex2>
		inline constexpr bool operator>=(::ztd::__span_detail::span<_Ty1, _Ex1> const& __left,
		     ::ztd::type_identity_t<::ztd::__span_detail::span<_Ty2, _Ex2>> const& __right) noexcept {
			return !(__left < __right);
		}

		template <typename _Ty, ::std::size_t _Ex>
		constexpr span<const std::byte, _Ex> as_bytes(::ztd::__span_detail::span<_Ty, _Ex> __source) noexcept {
			return ::ztd::__span_detail::span<const std::byte, _Ex>(
			     reinterpret_cast<::std::byte const*>(__source.data()), __source.size_bytes());
		}

		template <typename _Ty, ::std::size_t _Ex>
		constexpr span<std::byte, _Ex> as_writable_bytes(::ztd::__span_detail::span<_Ty, _Ex> __source) noexcept {
			return ::ztd::__span_detail::span<std::byte, _Ex>(
			     reinterpret_cast<::std::byte*>(__source.data()), __source.size_bytes());
		}

		template <typename _Ty>
		inline constexpr ::ztd::__span_detail::span<_Ty> make_span(_Ty* __ptr, size_t __count) noexcept {
			return ::ztd::__span_detail::span<_Ty>(__ptr, __count);
		}

		template <typename _Ty>
		inline constexpr ::ztd::__span_detail::span<_Ty> make_span(_Ty* __first, _Ty* __last) noexcept {
			return ::ztd::__span_detail::span<_Ty>(__first, __last);
		}

		template <typename _Ty, ::std::size_t _N>
		inline constexpr ::ztd::__span_detail::span<_Ty, _N> make_span(_Ty (&__arr)[_N]) noexcept {
			return ::ztd::__span_detail::span<_Ty, _N>(__arr + 0, _N);
		}

		template <typename _Container, typename _EP = decltype(std::data(std::declval<_Container&>()))>
		inline constexpr auto make_span(_Container& __cont) noexcept
		     -> ::ztd::__span_detail::span<typename std::remove_pointer<_EP>::type> {
			return ::ztd::__span_detail::span<typename ::std::remove_pointer<_EP>::type>(__cont);
		}

		template <typename _Container, typename _EP = decltype(std::data(std::declval<_Container&>()))>
		inline constexpr auto make_span(const _Container& __cont) noexcept
		     -> ::ztd::__span_detail::span<const typename ::std::remove_pointer<_EP>::type> {
			return ::ztd::__span_detail::span<const typename ::std::remove_pointer<_EP>::type>(__cont);
		}

	} // namespace __span_detail

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#endif
