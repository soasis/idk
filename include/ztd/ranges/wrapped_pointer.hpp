// =============================================================================
// ztd::fixed_container
//
// Written 2019 - 2022 by ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
// ============================================================================ //

#pragma once

#ifndef ZTD_RANGES_WRAPPED_POINTER_HPP
#define ZTD_RANGES_WRAPPED_POINTER_HPP

#include <ztd/ranges/version.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/to_address.hpp>
#include <ztd/idk/contiguous_iterator_tag.hpp>
#include <ztd/idk/unwrap.hpp>

#include <utility>
#include <iterator>

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	template <typename _Type>
	class wrapped_pointer {
	private:
		using __unwrapped_type = decltype(ztd::unwrap(::std::declval<_Type&>()));

	public:
		using iterator_category = ::ztd::contiguous_iterator_tag;
		using value_type        = ::ztd::remove_cvref_t<__unwrapped_type>;
		using element_type      = ::std::remove_reference_t<__unwrapped_type>;
		using reference         = ::std::add_lvalue_reference_t<__unwrapped_type>;
		using pointer           = ::std::add_pointer_t<element_type>;
		using difference_type   = decltype(::std::declval<const pointer&>() - ::std::declval<const pointer&>());

		constexpr wrapped_pointer() : wrapped_pointer(nullptr) {
		}
		constexpr wrapped_pointer(pointer __ptr) : _M_ptr(__ptr) {
		}
		constexpr wrapped_pointer(const wrapped_pointer&)            = default;
		constexpr wrapped_pointer(wrapped_pointer&&)                 = default;
		constexpr wrapped_pointer& operator=(const wrapped_pointer&) = default;
		constexpr wrapped_pointer& operator=(wrapped_pointer&&)      = default;

		constexpr explicit operator bool() const noexcept {
			return this->_M_ptr != nullptr;
		}

		constexpr pointer base() const noexcept {
			return this->_M_ptr;
		}

		constexpr reference operator[](difference_type __index) const noexcept {
			pointer __ptr = this->_M_ptr + __index;
			return ztd::unwrap(*__ptr);
		}

		constexpr reference operator*() const noexcept {
			return ztd::unwrap(*this->_M_ptr);
		}

		constexpr pointer operator->() const noexcept {
			return ::std::addressof(ztd::unwrap(*this->_M_ptr));
		}

		constexpr wrapped_pointer& operator++() noexcept {
			++this->_M_ptr;
			return *this;
		}

		constexpr wrapped_pointer operator++(int) noexcept {
			auto __copy = *this;
			++__copy;
			return __copy;
		}

		constexpr wrapped_pointer& operator--() noexcept {
			--this->_M_ptr;
			return *this;
		}

		constexpr wrapped_pointer operator--(int) noexcept {
			auto __copy = *this;
			--__copy;
			return __copy;
		}

		constexpr wrapped_pointer& operator+=(difference_type __right) noexcept {
			this->_M_ptr += __right;
			return *this;
		}

		constexpr wrapped_pointer& operator-=(difference_type __right) noexcept {
			this->_M_ptr -= __right;
			return *this;
		}

		constexpr wrapped_pointer operator+(difference_type __right) const noexcept {
			return wrapped_pointer(this->_M_ptr + __right);
		}

		constexpr wrapped_pointer operator-(difference_type __right) const noexcept {
			return wrapped_pointer(this->_M_ptr - __right);
		}

		constexpr difference_type operator-(const wrapped_pointer& __right) const noexcept {
			return __right.base() - this->_M_ptr;
		}

		friend constexpr pointer to_address(const wrapped_pointer& __wrapped) noexcept {
			return ztd::unwrap_iterator(__wrapped._M_ptr);
		}

	private:
		pointer _M_ptr;
	};

	template <typename _LeftType, typename _RightType>
	constexpr bool operator==(const wrapped_pointer<_LeftType>& __left, const wrapped_pointer<_RightType>& __right) {
		return __left.base() == __right.base();
	}

	template <typename _RightType>
	constexpr bool operator==(::std::nullptr_t __left, const wrapped_pointer<_RightType>& __right) {
		return __left == __right.base();
	}

	template <typename _LeftType>
	constexpr bool operator==(const wrapped_pointer<_LeftType>& __left, ::std::nullptr_t __right) {
		return __left.base() == __right;
	}

	template <typename _LeftType, typename _RightType>
	constexpr bool operator!=(const wrapped_pointer<_LeftType>& __left, const wrapped_pointer<_RightType>& __right) {
		return __left.base() != __right.base();
	}

	template <typename _RightType>
	constexpr bool operator!=(::std::nullptr_t __left, const wrapped_pointer<_RightType>& __right) {
		return __left != __right.base();
	}

	template <typename _LeftType>
	constexpr bool operator!=(const wrapped_pointer<_LeftType>& __left, ::std::nullptr_t __right) {
		return __left.base() != __right;
	}

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_

}} // namespace ztd::ranges

namespace std {

	template <typename _Type>
	struct pointer_traits<::ztd::ranges::wrapped_pointer<_Type>> {
		using pointer         = typename ::ztd::ranges::wrapped_pointer<_Type>::pointer;
		using element_type    = typename ::ztd::ranges::wrapped_pointer<_Type>::element_type;
		using difference_type = typename ::ztd::ranges::wrapped_pointer<_Type>::difference_type;

		static constexpr pointer pointer_to(element_type& __iter) noexcept {
			return ::std::addressof(__iter);
		}

		static constexpr pointer to_address(const ::ztd::ranges::wrapped_pointer<_Type>& __iter) noexcept(
		     noexcept(::ztd::idk_adl::adl_to_address(__iter))) {
			return ::ztd::idk_adl::adl_to_address(__iter);
		}
	};

} // namespace std

#endif // ZTD_RANGES_WRAPPED_POINTER_HPP
