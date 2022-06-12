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

#ifndef ZTD_IDK_UNINIT_HPP
#define ZTD_IDK_UNINIT_HPP

#include <ztd/idk/version.hpp>
#include <ztd/idk/unwrap.hpp>

#include <utility>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

	//////
	/// @brief A class for holding a value inside of an unnamed union which is composed of two objects, one of `char`
	/// and one of `_Type`.
	template <typename _Type>
	class alignas(_Type) uninit {
	public:
		//////
		/// @brief Constructs an empty placeholder.
		constexpr uninit() : placeholder() {
		}

		//////
		/// @brief Constructs the `value` from the given arguments
		///
		/// @param[in] __args The arguments to construct `value` with.
		template <typename... _Args>
		constexpr uninit(::std::in_place_t, _Args&&... __args) : value(::std::forward<_Args>(__args)...) {
		}

		//////
		/// @brief Extension point for returning the value inside of this uninitialized type.
		friend _Type& unwrap_value(uninit& __wrapped_value) noexcept {
			return __wrapped_value.value;
		}

		//////
		/// @brief Extension point for returning the value inside of this uninitialized type.
		friend const _Type& unwrap_value(const uninit& __wrapped_value) noexcept {
			return __wrapped_value.value;
		}

		//////
		/// @brief Extension point for returning the value inside of this uninitialized type.
		friend _Type&& unwrap_value(uninit&& __wrapped_value) noexcept {
			return ::std::move(__wrapped_value.value);
		}

		union {
			//////
			/// @brief Placeholder empty value for default / empty  initialization, esp. with arrays.
			char placeholder;
			//////
			/// @brief Actual value.
			_Type value;
		};

		//////
		/// @brief An empty destructor. Required, as there is a union object present.
		~uninit() {
			// No action.
		}
	};


	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#endif // ZTD_IDK_UNINIT_HPP
