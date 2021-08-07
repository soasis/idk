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

#ifndef ZTD_IDK_C_SPAN_H
#define ZTD_IDK_C_SPAN_H

#include <ztd/idk/version.h>
#include <ztd/idk/charN_t.h>

#define ZTD_IDK_C_SPAN_TYPE char
#include <ztd/idk/c_span.g.h>

#define ZTD_IDK_C_SPAN_TYPE wchar_t
#include <ztd/idk/c_span.g.h>

#define ZTD_IDK_C_SPAN_TYPE ztd_char8_t
#define ZTD_IDK_C_SPAN_TYPE_NAME char8_t
#include <ztd/idk/c_span.g.h>

#define ZTD_IDK_C_SPAN_TYPE ztd_char16_t
#define ZTD_IDK_C_SPAN_TYPE_NAME char16_t
#include <ztd/idk/c_span.g.h>

#define ZTD_IDK_C_SPAN_TYPE ztd_char32_t
#define ZTD_IDK_C_SPAN_TYPE_NAME char32_t
#include <ztd/idk/c_span.g.h>

#define ZTD_IDK_C_SPAN_TYPE unsigned char
#define ZTD_IDK_C_SPAN_TYPE_NAME uchar
#include <ztd/idk/c_span.g.h>

#endif // ZTD_IDK_C_SPAN_H
