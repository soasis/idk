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

#pragma once

#ifndef ZTD_IDK_ENDIAN_HPP
#define ZTD_IDK_ENDIAN_HPP

#include <ztd/version.hpp>

#if ZTD_IS_ON(ZTD_STD_LIBRARY_ENDIAN_I_)
#include <bit>
#endif

#include <ztd/idk/detail/windows.hpp>

#include <ztd/prologue.hpp>

namespace ztd {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_

#if ZTD_IS_OFF(ZTD_STD_LIBRARY_ENDIAN_I_)
	namespace __idk_detail {
		enum class __endian {
#if ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_)
			//////
			/// @brief Little endian, in which the least significant byte as the first byte value.
			///
			//////
			little = 0,
			//////
			/// @brief Big endian, in which the most significant byte as the first byte value.
			///
			//////
			big = 1,
		// clang-format off
	#if defined(REG_DWORD)
		#if (REG_DWORD == REG_DWORD_LITTLE_ENDIAN)
		//////
		/// @brief Native endian, whcih is big, little, or some implementation-defined ordering (e.g., middle endian).
		/// If it is big or little, then ``ztd::text::endian::little`` == `ztd::text::endian::big``.
		//////
			native = little
		#else
		//////
		/// @brief Native endian, whcih is big, little, or some implementation-defined ordering (e.g., middle endian).
		/// If it is big or little, then ``ztd::text::endian::little`` == `ztd::text::endian::big``.
		//////
			native = big
		#endif
	#else
		//////
		/// @brief Native endian, whcih is big, little, or some implementation-defined ordering (e.g., middle endian).
		/// If it is big or little, then ``ztd::text::endian::little`` == `ztd::text::endian::big``.
		//////
		native = big
	#endif
		// clang-format on
#else
			//////
			/// @brief Little endian, in which the least significant byte as the first byte value.
			///
			//////
			little = __ORDER_LITTLE_ENDIAN__,
			//////
			/// @brief Big endian, in which the most significant byte as the first byte value.
			///
			//////
			big = __ORDER_BIG_ENDIAN__,
			//////
			/// @brief Native endian, whcih is big, little, or some implementation-defined ordering (e.g., middle
			/// endian).
			/// If it is big or little, then ``ztd::text::endian::little`` == `ztd::text::endian::big``.
			//////
			native = __BYTE_ORDER__
#endif
		};
	} // namespace __idk_detail

#endif

	//////
	/// @brief An endian enumeration.
	///
	/// @remarks It may include little, big, or native values. The native value can be the same as the little or big
	/// values, but if on a middle-endian machine it may be an implementation-defined "middle endian" value that is not
	/// equal to either little or big (as on the PDP-11). We don't expect many relevant architectures to be using
	/// middle-endian, though.
	//////
	using endian =
#if ZTD_IS_OFF(ZTD_STD_LIBRARY_ENDIAN_I_)
	     __idk_detail::__endian;
#else
	     ::std::endian;
#endif

	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
} // namespace ztd

#include <ztd/epilogue.hpp>

#endif // ZTD_IDK_ENDIAN_HPP
