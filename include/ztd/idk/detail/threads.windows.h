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

#ifndef ZTD_IDK_DETAIL_THREADS_WINDOWS_H
#define ZTD_IDK_DETAIL_THREADS_WINDOWS_H

#include <ztd/idk/version.h>

typedef enum __mtx_type_t {
	mtx_plain     = 0,
	mtx_recursive = 1,
	mtx_timed     = 2,
} __mtx_type;

typedef enum __thrd_error_code {
	thrd_success  = 0,
	thrd_timedout = 1,
	thrd_busy     = 2,
	thrd_error    = 3,
	thrd_nomem    = 4
} __thrd_error_code;

#endif
