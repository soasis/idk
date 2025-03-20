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

#ifndef ZTD_IDK_BENCHMARKS_OPAQUE_OPAQUE_HPP
#define ZTD_IDK_BENCHMARKS_OPAQUE_OPAQUE_HPP

#pragma once

#include <opaque/version.hpp>

#include <cstddef>

ZTD_OPAQUE_API_LINKAGE_I_ std::size_t opaque_benchmark_loop_limit(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

ZTD_OPAQUE_API_LINKAGE_I_ std::size_t opaque_hardcoded_index(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

ZTD_OPAQUE_API_LINKAGE_I_ bool opaque_true(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

ZTD_OPAQUE_API_LINKAGE_I_ bool opaque_false(void) ZTD_USE(ZTD_NOEXCEPT_IF_CXX);

#endif
