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

#include <k_value/k_value.h>

#include <ztd/idk/type_traits.hpp>

#include <exception>
#include <iostream>

namespace {
	template <int recursion = 0>
	static int a(int k, const auto& x1, const auto& x2, const auto& x3, const auto& x4, const auto& x5) {
		if constexpr (recursion == 11) {
			::std::cerr << "This should never happen and this code should never have been generated." << std::endl;
			::std::terminate();
			return 0;
		}
		else {
			auto B = [&](this const auto& self) { return a<recursion + 1>(--k, self, x1, x2, x3, x4); };
			return k <= 0 ? x4() + x5() : B();
		}
	}

	inline static int f_1() {
		return -1;
	}

	inline static int f0() {
		return 0;
	}

	inline static int f1() {
		return 1;
	}
} // namespace

static void lambda(benchmark::State& state) {
	int k          = k_value();
	int expected_k = expected_k_value();

	int64_t result = 0;

	for (auto _ : state) {
		int value = a(k, f1, f_1, f_1, f1, f0);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(lambda);
