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

#include <benchmark/benchmark.h>

#include <ztd/idk/bit.h>
#include <opaque/opaque.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <cstdlib>
#include <climits>

static void is_sorted_naive(benchmark::State& state) {
	using C = std::array<bool, 100032>;
	C c;
	c.fill(opaque_false());
	c[c.size() - 1] = opaque_true();

	bool result = true;
	for (auto _ : state) {
		bool is_sorted = true;
		auto end_it    = c.cend();
		bool seen_true = false;
		for (auto it = c.cbegin(); it != end_it; ++it) {
			const bool& value = *it;
			if (!seen_true) {
				if (value) {
					seen_true = true;
				}
			}
			else {
				if (!value) {
					is_sorted = false;
					break;
				}
			}
		}
		result &= is_sorted;
	}
	if (!result) {
		state.SkipWithError("bad benchmark result");
	}
}

static void is_sorted_naive_packed(benchmark::State& state) {
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(static_cast<std::size_t>(opaque_false()));
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(100032 - 1), size_bits);
		std::size_t& target_word = c[static_cast<std::size_t>(rem.quot)];
		target_word |= (static_cast<std::size_t>(opaque_true()) << static_cast<std::size_t>(rem.rem));
	}

	bool result = true;
	for (auto _ : state) {
		bool is_sorted = true;
		auto end_it    = c.cend();
		bool seen_true = false;
		for (auto it = c.cbegin(); it != end_it && is_sorted; ++it) {
			const std::size_t& target_word = *it;
			for (std::size_t bit_index = 0; bit_index < size_bits; ++bit_index) {
				std::size_t mask = (static_cast<std::size_t>(1) << bit_index);
				bool value       = (target_word & mask) != 0;
				if (!seen_true) {
					if (value) {
						seen_true = true;
					}
				}
				else {
					if (!value) {
						is_sorted = false;
						break;
					}
				}
			}
		}
		result &= is_sorted;
	}
	if (!result) {
		state.SkipWithError("bad benchmark result");
	}
}

static void is_sorted_ztdc_packed(benchmark::State& state) {
	constexpr std::size_t size_bits = sizeof(std::size_t) * CHAR_BIT;
	using C                         = std::array<std::size_t, (100032 + size_bits - 1) / (size_bits)>;
	C c;
	c.fill(static_cast<std::size_t>(opaque_false()));
	{
		std::lldiv_t rem         = std::lldiv(static_cast<std::size_t>(100032 - 1), size_bits);
		std::size_t& target_word = c[static_cast<std::size_t>(rem.quot)];
		target_word |= (static_cast<std::size_t>(opaque_true()) << static_cast<std::size_t>(rem.rem));
	}

	bool result = true;
	for (auto _ : state) {
		bool is_sorted = true;
		auto end_it    = c.cend();
		bool seen_true = false;
		for (auto it = c.cbegin(); it != end_it; ++it) {
			const std::size_t& target_word = *it;
			if (!seen_true) {
				std::size_t bs = ztdc_first_trailing_one(target_word);
				if (bs != 0) {
					seen_true          = true;
					bool found_anamoly = false;
					for (std::size_t i = bs - 1; i < size_bits; ++i) {
						std::size_t mask = (static_cast<std::size_t>(1) << i);
						if ((target_word & mask) == 0) {
							// found bad one
							is_sorted     = false;
							found_anamoly = true;
							break;
						}
					}
					if (found_anamoly) {
						break;
					}
				}
			}
			else {
				std::size_t bs = ztdc_first_trailing_zero(target_word);
				if (bs != 0) {
					is_sorted = false;
					break;
				}
			}
		}
		result &= is_sorted;
	}
	if (!result) {
		state.SkipWithError("bad benchmark result");
	}
}

static void is_sorted_cpp_std_array_bool(benchmark::State& state) {
	using C = std::array<bool, 100032>;
	C c;
	c.fill(opaque_false());
	c[c.size() - 1] = opaque_true();

	bool result = true;
	for (auto _ : state) {
		bool is_sorted = std::is_sorted(c.cbegin(), c.cend());
		result &= is_sorted;
	}
	if (!result) {
		state.SkipWithError("bad benchmark result");
	}
}

static void is_sorted_cpp_std_vector_bool(benchmark::State& state) {
	using C = std::vector<bool>;
	C c(100032, opaque_false());
	c[c.size() - 1] = opaque_true();

	bool result = true;
	for (auto _ : state) {
		bool is_sorted = std::is_sorted(c.cbegin(), c.cend());
		result &= is_sorted;
	}
	if (!result) {
		state.SkipWithError("bad benchmark result");
	}
}

static void is_sorted_cpp_std_bitset(benchmark::State& state) {
	using C = std::bitset<100032>;
	C c;
	c.reset();
	c[c.size() - 1] = opaque_true();

	bool result = true;
	for (auto _ : state) {
		std::size_t i    = 0;
		std::size_t last = c.size();
		std::size_t next = i;
		while (++next != last) {
			bool next_val = c[next];
			bool i_val    = c[i];
			if (next_val < i_val)
				break;
			i = next;
		}
		result &= (next == last);
	}
	if (!result) {
		state.SkipWithError("bad benchmark result");
	}
}

BENCHMARK(is_sorted_naive);
BENCHMARK(is_sorted_naive_packed);
BENCHMARK(is_sorted_ztdc_packed);
BENCHMARK(is_sorted_cpp_std_array_bool);
BENCHMARK(is_sorted_cpp_std_vector_bool);
BENCHMARK(is_sorted_cpp_std_bitset);
