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

#ifndef ZTD_IDK_DETAIL_THREADS_PTHREADS_H
#define ZTD_IDK_DETAIL_THREADS_PTHREADS_H

#include <ztd/idk/version.h>

#include <pthread.h>

#if ZTD_IS_OFF(ZTD_HEADER_THREADS_H)

#if ZTD_IS_ON(ZTD_CXX)
#include <cstdint>
#else
#include <stdint.h>
#endif

typedef pthread_t thrd_t;

typedef int(thrd_start_t)(void*);

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

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_create(thrd_t* __thr, thrd_start_t __func, void* __arg);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_join(thrd_t __thr, int* __res);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_ATTR_NO_RETURN)
void thrd_exit(int __res);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_detach(thrd_t __thr);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_detach(thrd_t __thr);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_equal(thrd_t __left, thrd_t __right);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
thrd_t thrd_current(void);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
void thrd_yield(void);

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_sleep(const struct timespec* __duration, struct timespec* __remaining);
#endif

#endif
