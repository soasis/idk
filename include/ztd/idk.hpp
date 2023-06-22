// =============================================================================
//
// ztd.idk
// Copyright © 2022-2023 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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

#ifndef ZTD_IDK_HPP
#define ZTD_IDK_HPP

#include <ztd/idk/version.hpp>

#include <ztd/idk/align.hpp>
#include <ztd/idk/assert.hpp>
#include <ztd/idk/assume_aligned.hpp>
#include <ztd/idk/basic_c_string_view.hpp>
#include <ztd/idk/binary_digits.hpp>
#include <ztd/idk/bit.hpp>
#include <ztd/idk/charN_t.hpp>
#include <ztd/idk/char_traits.hpp>
#include <ztd/idk/c_string_view.hpp>
#include <ztd/idk/construct_destroy.hpp>
#include <ztd/idk/contiguous_iterator_tag.hpp>
#include <ztd/idk/ebco.hpp>
#include <ztd/idk/empty_string.hpp>
#include <ztd/idk/encoding_detection.hpp>
#include <ztd/idk/encoding_name.hpp>
#include <ztd/idk/generic.hpp>
#include <ztd/idk/hijack.hpp>
#include <ztd/idk/reference_wrapper.hpp>
#include <ztd/idk/size.hpp>
#include <ztd/idk/span.hpp>
#include <ztd/idk/static_assert.hpp>
#include <ztd/idk/tag.hpp>
#include <ztd/idk/text_encoding_id.hpp>
#include <ztd/idk/to_address.hpp>
#include <ztd/idk/to_mutable_iter.hpp>
#include <ztd/idk/to_underlying.hpp>
#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/uninit.hpp>
#include <ztd/idk/unreachable.hpp>
#include <ztd/idk/unwrap.hpp>

#include <ztd/idk.h>

#endif
