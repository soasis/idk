// =============================================================================
//
// ztd.idk
// Copyright © 2022 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
// ============================================================================ //

#pragma once

#ifndef ZTD_TEXT_LATIN1_TABLES_H
#define ZTD_TEXT_LATIN1_TABLES_H

#include <ztd/idk/version.h>

#include <ztd/idk/charN_t.h>
#include <ztd/idk/encoding_types.tables.h>

#if ZTD_IS_ON(ZTD_C)
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include <cstddef>
#include <cstdint>
#endif

ZTD_EXTERN_C_I_ ZTD_INLINE_CONSTEXPR_IF_CXX_I_ const ztd_encoding_index16_code_point_t
     ztd_latin1_index_code_point_map[128]
     = { { 0, 0x20AC }, { 1, 0x0081 }, { 2, 0x201A }, { 3, 0x0192 }, { 4, 0x201E }, { 5, 0x2026 }, { 6, 0x2020 },
	       { 7, 0x2021 }, { 8, 0x02C6 }, { 9, 0x2030 }, { 10, 0x0160 }, { 11, 0x2039 }, { 12, 0x0152 }, { 13, 0x008D },
	       { 14, 0x017D }, { 15, 0x008F }, { 16, 0x0090 }, { 17, 0x2018 }, { 18, 0x2019 }, { 19, 0x201C },
	       { 20, 0x201D }, { 21, 0x2022 }, { 22, 0x2013 }, { 23, 0x2014 }, { 24, 0x02DC }, { 25, 0x2122 },
	       { 26, 0x0161 }, { 27, 0x203A }, { 28, 0x0153 }, { 29, 0x009D }, { 30, 0x017E }, { 31, 0x0178 },
	       { 32, 0x00A0 }, { 33, 0x00A1 }, { 34, 0x00A2 }, { 35, 0x00A3 }, { 36, 0x00A4 }, { 37, 0x00A5 },
	       { 38, 0x00A6 }, { 39, 0x00A7 }, { 40, 0x00A8 }, { 41, 0x00A9 }, { 42, 0x00AA }, { 43, 0x00AB },
	       { 44, 0x00AC }, { 45, 0x00AD }, { 46, 0x00AE }, { 47, 0x00AF }, { 48, 0x00B0 }, { 49, 0x00B1 },
	       { 50, 0x00B2 }, { 51, 0x00B3 }, { 52, 0x00B4 }, { 53, 0x00B5 }, { 54, 0x00B6 }, { 55, 0x00B7 },
	       { 56, 0x00B8 }, { 57, 0x00B9 }, { 58, 0x00BA }, { 59, 0x00BB }, { 60, 0x00BC }, { 61, 0x00BD },
	       { 62, 0x00BE }, { 63, 0x00BF }, { 64, 0x00C0 }, { 65, 0x00C1 }, { 66, 0x00C2 }, { 67, 0x00C3 },
	       { 68, 0x00C4 }, { 69, 0x00C5 }, { 70, 0x00C6 }, { 71, 0x00C7 }, { 72, 0x00C8 }, { 73, 0x00C9 },
	       { 74, 0x00CA }, { 75, 0x00CB }, { 76, 0x00CC }, { 77, 0x00CD }, { 78, 0x00CE }, { 79, 0x00CF },
	       { 80, 0x00D0 }, { 81, 0x00D1 }, { 82, 0x00D2 }, { 83, 0x00D3 }, { 84, 0x00D4 }, { 85, 0x00D5 },
	       { 86, 0x00D6 }, { 87, 0x00D7 }, { 88, 0x00D8 }, { 89, 0x00D9 }, { 90, 0x00DA }, { 91, 0x00DB },
	       { 92, 0x00DC }, { 93, 0x00DD }, { 94, 0x00DE }, { 95, 0x00DF }, { 96, 0x00E0 }, { 97, 0x00E1 },
	       { 98, 0x00E2 }, { 99, 0x00E3 }, { 100, 0x00E4 }, { 101, 0x00E5 }, { 102, 0x00E6 }, { 103, 0x00E7 },
	       { 104, 0x00E8 }, { 105, 0x00E9 }, { 106, 0x00EA }, { 107, 0x00EB }, { 108, 0x00EC }, { 109, 0x00ED },
	       { 110, 0x00EE }, { 111, 0x00EF }, { 112, 0x00F0 }, { 113, 0x00F1 }, { 114, 0x00F2 }, { 115, 0x00F3 },
	       { 116, 0x00F4 }, { 117, 0x00F5 }, { 118, 0x00F6 }, { 119, 0x00F7 }, { 120, 0x00F8 }, { 121, 0x00F9 },
	       { 122, 0x00FA }, { 123, 0x00FB }, { 124, 0x00FC }, { 125, 0x00FD }, { 126, 0x00FE }, { 127, 0x00FF } };

ZTD_EXTERN_C_I_ bool ztdc_latin1_index_to_code_point(
     size_t __lookup_index_pointer, ztd_char32_t* __p_code_point) ZTD_NOEXCEPT_IF_CXX_I_;
ZTD_EXTERN_C_I_ bool ztdc_latin1_code_point_to_index(
     ztd_char32_t __lookup_code_point, size_t* __p_index) ZTD_NOEXCEPT_IF_CXX_I_;

#endif
