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

#include <ztd/idk/bit.h>
#include <ztd/idk/endian.h>
#include <ztd/idk/type_traits.hpp>

#include <catch2/catch_all.hpp>

#include <random>


TEST_CASE("bit/memreverse", "Ensure that hte 8-bit memory reverse algorithm works.") {
#if CHAR_BIT == 8
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, std::numeric_limits<unsigned char>::max());
	const std::vector<unsigned char> data = [&rng, &dist]() {
		std::vector<unsigned char> data_init(50000);
		for (unsigned char& val : data_init) {
			val = static_cast<unsigned char>(dist(rng));
		}
		return data_init;
	}();

	const std::vector<unsigned char> reverse_data(data.rbegin(), data.rend());
	std::vector<unsigned char> target = data;
	REQUIRE(target == data);
	ztdc_memreverse8(target.size(), target.data());
	REQUIRE(target == reverse_data);
#else
#error This test must be upated to work on (CHAR_BIT != 8) and ((CHAR_BIT % 8) == 0) environments!
#endif
}
