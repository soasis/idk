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

#include <benchmark/benchmark.h>

#include <ztd/idk/bit.h>
#include <opaque/opaque.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void find_naive(benchmark::State& state) {
	using C = std::array<bool, 100032>;
	C c;
	c.fill(opaque_false());
	c[opaque_hardcoded_index()] = opaque_true();

	std::size_t result       = 0;
	std::size_t result_index = (std::numeric_limits<std::size_t>::max)();
	for (auto _ : state) {
		std::size_t index = 0;
		auto end_it       = c.cend();
		for (auto it = c.cbegin(); it != end_it; ++it) {
			const bool& value = *it;
			if (value) {
				index = it - c.begin();
				result += 1;
				break;
			}
		}
		result_index &= index;
	}
	if (result_index != opaque_hardcoded_index() || result != static_cast<std::size_t>(state.iterations())) {
		state.SkipWithError("bad benchmark result");
	}
}

static void find_naive_packed(benchmark::State& state) {
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(0);
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(opaque_hardcoded_index()), size_bits);
		std::size_t& target_word = c[static_cast<std::size_t>(rem.quot)];
		target_word |= (static_cast<std::size_t>(opaque_true()) << static_cast<std::size_t>(rem.rem));
	}

	std::size_t result       = 0;
	std::size_t result_index = (std::numeric_limits<std::size_t>::max)();
	for (auto _ : state) {
		std::size_t index = 0;
		auto end_it       = c.cend();
		for (auto it = c.cbegin(); it != end_it; ++it) {
			const std::size_t& target_word = *it;
			for (std::size_t bit_index = 0; bit_index < size_bits; ++bit_index) {
				std::size_t mask = (static_cast<std::size_t>(1) << bit_index);
				if ((target_word & mask) != 0) {
					index = ((it - c.begin()) * size_bits) + bit_index;
					result += 1;
					break;
				}
			}
			if (index != 0)
				break;
		}
		result_index &= index;
	}
	if (result_index != opaque_hardcoded_index() || result != static_cast<std::size_t>(state.iterations())) {
		state.SkipWithError("bad benchmark result");
	}
}

static void find_ztdc_packed(benchmark::State& state) {
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(0);
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(opaque_hardcoded_index()), size_bits);
		std::size_t& target_word = c[static_cast<std::size_t>(rem.quot)];
		target_word |= (static_cast<std::size_t>(opaque_true()) << static_cast<std::size_t>(rem.rem));
	}

	std::size_t result       = 0;
	std::size_t result_index = (std::numeric_limits<std::size_t>::max)();
	for (auto _ : state) {
		std::size_t index = 0;
		auto end_it       = c.cend();
		for (auto it = c.cbegin(); it != end_it; ++it) {
			const std::size_t& target_word = *it;
			std::size_t bs                 = ztdc_first_trailing_one(target_word);
			if (bs != 0) {
				--bs;
				std::size_t mask = (static_cast<std::size_t>(1) << bs);
				index            = ((it - c.begin()) * size_bits) + bs;
				result += 1;
				break;
			}
		}
		result_index &= index;
	}
	if (result_index != opaque_hardcoded_index() || result != static_cast<std::size_t>(state.iterations())) {
		state.SkipWithError("bad benchmark result");
	}
}

static void find_cpp_std_array_bool(benchmark::State& state) {
	using C = std::array<bool, 100032>;
	C c;
	c.fill(opaque_false());
	c[opaque_hardcoded_index()] = opaque_true();

	std::size_t result       = 0;
	std::size_t result_index = (std::numeric_limits<std::size_t>::max)();
	for (auto _ : state) {
		auto it = std::find(c.cbegin(), c.cend(), true);
		if (it != c.cend()) {
			result_index &= static_cast<std::size_t>(it - c.begin());
			result += 1;
		}
	}
	if (result_index != opaque_hardcoded_index() || result != static_cast<std::size_t>(state.iterations())) {
		state.SkipWithError("bad benchmark result");
	}
}

static void find_cpp_std_vector_bool(benchmark::State& state) {
	using C = std::vector<bool>;
	C c(100032, opaque_false());
	c[opaque_hardcoded_index()] = opaque_true();

	std::size_t result       = 0;
	std::size_t result_index = (std::numeric_limits<std::size_t>::max)();
	for (auto _ : state) {
		auto it = std::find(c.cbegin(), c.cend(), true);
		if (it != c.cend()) {
			std::size_t index = it - c.cbegin();
			result_index &= index;
			result += 1;
		}
	}
	if (result_index != opaque_hardcoded_index() || result != static_cast<std::size_t>(state.iterations())) {
		state.SkipWithError("bad benchmark result");
	}
}

static void find_cpp_std_bitset(benchmark::State& state) {
	using C = std::bitset<100032>;
	C c {};
	c[opaque_hardcoded_index()] = opaque_true();

	std::size_t result       = 0;
	std::size_t result_index = (std::numeric_limits<std::size_t>::max)();
	for (auto _ : state) {
		std::size_t index = 0;
		for (std::size_t i = 0; i < c.size(); ++i) {
			if (c.test(i)) {
				index = i;
				result += 1;
				break;
			}
		}
		result_index &= index;
	}
	if (result_index != opaque_hardcoded_index() || result != static_cast<std::size_t>(state.iterations())) {
		state.SkipWithError("bad benchmark result");
	}
}

BENCHMARK(find_naive);
BENCHMARK(find_naive_packed);
BENCHMARK(find_ztdc_packed);
BENCHMARK(find_cpp_std_array_bool);
BENCHMARK(find_cpp_std_vector_bool);
BENCHMARK(find_cpp_std_bitset);
