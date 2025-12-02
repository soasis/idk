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

#include <cstdlib>
#include <cstdint>
#include <cstddef>

namespace {
	typedef struct arg {
		int (*fn)(struct arg*);
		int* k;
		struct arg *x1, *x2, *x3, *x4, *x5;
	} ARG;

	static int f_1(ARG* _) {
		return -1;
	}

	static int f0(ARG* _) {
		return 0;
	}

	static int f1(ARG* _) {
		return 1;
	}

	// --- helper
	static int eval(ARG* a) {
		return a->fn(a);
	}

	static int A(ARG*);

	// --- functions
	static int B(ARG* a) {
		int k    = *a->k -= 1;
		ARG args = { B, &k, a, a->x1, a->x2, a->x3, a->x4 };
		return A(&args);
	}

	static int A(ARG* a) {
		return *a->k <= 0 ? eval(a->x4) + eval(a->x5) : B(a);
	}
} // namespace

static void normal_functions_rosetta(benchmark::State& state) {
	const int initial_k  = k_value();
	const int expected_k = expected_k_value();
	int64_t result       = 0;

	for (auto _ : state) {
		int k     = initial_k;
		ARG arg1  = { f1, NULL, NULL, NULL, NULL, NULL, NULL };
		ARG arg2  = { f_1, NULL, NULL, NULL, NULL, NULL, NULL };
		ARG arg3  = { f_1, NULL, NULL, NULL, NULL, NULL, NULL };
		ARG arg4  = { f1, NULL, NULL, NULL, NULL, NULL, NULL };
		ARG arg5  = { f0, NULL, NULL, NULL, NULL, NULL, NULL };
		ARG args  = { B, &k, &arg1, &arg2, &arg3, &arg4, &arg5 };
		int value = A(&args);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(normal_functions_rosetta);
