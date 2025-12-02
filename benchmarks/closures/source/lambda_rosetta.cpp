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

namespace {
	using f_t = std::function<int(void)>;

	inline static int A(int k, const f_t& x1, const f_t& x2, const f_t& x3, const f_t& x4, const f_t& x5) {
		f_t B = [=, &k, &B] { return A(--k, B, x1, x2, x3, x4); };
		return k <= 0 ? x4() + x5() : B();
	}

	inline static f_t L(int n) {
		return [n] { return n; };
	}
} // namespace

static void lambda_rosetta(benchmark::State& state) {
	int k          = k_value();
	int expected_k = expected_k_value();

	int64_t result = 0;
	auto arg1      = L(1);
	auto arg2      = L(-1);
	auto arg3      = L(-1);
	auto arg4      = L(1);
	auto arg5      = L(0);

	for (auto _ : state) {
		int value = A(k, arg1, arg2, arg3, arg4, arg5);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(lambda_rosetta);
