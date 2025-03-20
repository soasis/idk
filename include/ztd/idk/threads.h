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

#ifndef ZTD_IDK_THREADS_H
#define ZTD_IDK_THREADS_H

#include <ztd/idk/version.h>

#include <ztd/idk/charN_t.h>

#include <ztd/idk/detail/threads.attr.h>

#if ZTD_IS_ON(ZTD_HEADER_THREADS_H)
#if ZTD_IS_ON(ZTD_CXX)
#include <cthreads>
#else
#include <threads.h>
#endif
#elif ZTD_IS_ON(ZTD_PLATFORM_WINDOWS)
#include <ztd/idk/detail/threads.windows.h>
#elif ZTD_IS_ON(ZTD_PLATFORM_PTHREADS)
#include <ztd/idk/detail/threads.pthreads.h>
#else
#error "Unknown platform."
#endif

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int ztdc_thrd_create_attrs(
     thrd_t* __thr, thrd_start_t __func, void* __arg, size_t __attrs_size, ztdc_thrd_attr_kind** __attrs);

#endif
