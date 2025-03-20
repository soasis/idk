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

#ifndef ZTD_IDK_CHAR_TRAITS_HPP
#define ZTD_IDK_CHAR_TRAITS_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/charN_t.hpp>
#include <ztd/idk/mbstate_t.hpp>
#include <ztd/idk/type_traits.hpp>
#include <ztd/ranges/algorithm.hpp>

#include <string_view>

#include <ztd/prologue.hpp>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	template <typename _CharType>
	class unsigned_8bit_traits {
	public:
		static_assert(::std::is_unsigned_v<_CharType>, "the _CharType must be unsigned to be used here");

		using char_type  = _CharType;
		using int_type   = ::std::int_least32_t;
		using pos_type   = ::std::streampos;
		using off_type   = ::std::streamoff;
		using state_type = ztd_mbstate_t;

		static constexpr char_type* copy(
		     char_type* __destination, const char_type* __source, ::std::size_t __count) noexcept {
			(void)::ztd::ranges::__rng_detail::__copy_n_unsafe(__source, __count, __destination);
			return __destination;
		}

		static constexpr char_type* move(
		     char_type* __destination, const char_type* __source, ::std::size_t __count) noexcept {
			(void)::ztd::ranges::__rng_detail::__copy_n_unsafe(__source, __count, __destination);
			return __destination;
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr int compare(
		     const char_type* __left, const char_type* __right, ::std::size_t __count) noexcept {
			if (__count == 0) {
				return 0;
			}
			return ::ztd::ranges::__rng_detail::__lexicographical_compare_three_way_basic(
			     __left, __left + __count, __right, __right + __count);
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr size_t length(const char_type* __it) noexcept {
			size_t __count = 0;
			const char_type __null_value {};
			while (*__it != __null_value) {
				++__count;
				++__it;
			}
			return __count;
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr const char_type* find(
		     const char_type* __it, size_t __count, const char_type& __c) noexcept {
			for (; 0 < __count; --__count, (void)++__it) {
				if (*__it == __c) {
					return __it;
				}
			}
			return nullptr;
		}

		static constexpr char_type* assign(char_type* __first, size_t __count, const char_type __c) noexcept {
			for (char_type* __it = __first; __count > 0; --__count, (void)++__it) {
				*__it = __c;
			}
			return __first;
		}

		static constexpr void assign(char_type& __left, const char_type& __right) noexcept {
			__left = __right;
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr bool eq(const char_type& __left, const char_type& __right) noexcept {
			return __left == __right;
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr bool lt(const char_type& __left, const char_type& __right) noexcept {
			return __left < __right;
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr char_type to_char_type(const int_type& __c_as_int) noexcept {
			return char_type(static_cast<char32_t>(__c_as_int));
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr int_type to_int_type(const char_type& __c) noexcept {
			return static_cast<int_type>(__c);
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr bool eq_int_type(
		     const int_type& __left, const int_type& __right) noexcept {
			return __left == __right;
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr int_type not_eof(const int_type& __c_as_int) noexcept {
			return __c_as_int != eof() ? __c_as_int : !eof();
		}

		ZTD_ATTR_NODISCARD_I_ static constexpr int_type eof() noexcept {
			return static_cast<int_type>(EOF);
		}
	};

	using unsigned_char_traits = unsigned_8bit_traits<unsigned char>;

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

namespace std {

	template <>
	class char_traits<unsigned char> : public ::ztd::unsigned_char_traits { };

} // namespace std

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	//////
	/// @brief A traits type for ztd_char8_t / ztd::uchar8_t for whatever it is aliased to.
	using uchar8_traits =
#if ZTD_IS_ON(ZTD_NATIVE_CHAR8_T)
	     ::std::conditional_t<::std::is_same_v<::ztd::uchar8_t, char8_t>, ::std::char_traits<::ztd::uchar8_t>,
	          ::ztd::unsigned_8bit_traits<::ztd::uchar8_t>>
#else
	     ::ztd::unsigned_char_traits
#endif
	     ;

	template <typename _CharType>
	using char_traits_for = ::std::conditional_t<::std::is_same_v<_CharType, ::ztd::uchar8_t>, uchar8_traits,
	     ::std::char_traits<_CharType>>;

	template <>
	class is_char_traitable<unsigned char> : public std::true_type { };

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#include <ztd/epilogue.hpp>

#endif
