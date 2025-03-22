// ============================================================================
//
// ztd.idk
// Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.cuneicode licenses may use this file
// in accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ========================================================================= //

#ifndef ZTD_IDK_MBSTATE_H
#define ZTD_IDK_MBSTATE_H

#pragma once

#include <ztd/version.h>

#if ZTD_IS_ON(ZTD_HEADER_CWCHAR)
#include <cwchar>
#elif ZTD_IS_ON(ZTD_HEADER_WCHAR_H)
#include <wchar.h>
#endif
#if ZTD_IS_ON(ZTD_HEADER_CUCHAR)
#include <cuchar>
#elif ZTD_IS_ON(ZTD_HEADER_UCHAR_H)
ZTD_EXTERN_C_OPEN_I_
#include <uchar.h>
ZTD_EXTERN_C_CLOSE_I_
#endif

typedef ZTD_MBSTATE_SCOPE_I_ mbstate_t ztd_mbstate_t;

#endif
