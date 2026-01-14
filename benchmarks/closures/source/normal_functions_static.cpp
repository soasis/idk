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

#include <stdlib.h>
#include <benchmark/benchmark.h>

#include <k_value/k_value.h>

namespace {
	typedef struct all {
		int (*B)();
		int k;
		struct all *x1, *x2, *x3, *x4, *x5;
	} all;

	static int A(int k, all* x1, all* x2, all* x3, all* x4, all* x5);

	static all* B_self_transport;
	static int B() {
		all* self = B_self_transport;
		return A(--self->k, self, self->x1, self->x2, self->x3, self->x4);
	}

	static int A(int k, all* x1, all* x2, all* x3, all* x4, all* x5) {
		if (k <= 0) {
			B_self_transport = x4;
			int a            = x4->B();
			B_self_transport = x5;
			int b            = x5->B();
			return a + b;
		}
		else {
			all y = { .B = B, .k = k, .x1 = x1, .x2 = x2, .x3 = x3, .x4 = x4, .x5 = x5 };
			return (B_self_transport = &y, B());
		}
	}

	static int f1() {
		return 1;
	}

	static int f_1() {
		return -1;
	}

	static int f0() {
		return 0;
	}


} // namespace

static void normal_functions_static(benchmark::State& state) {
	int k          = k_value();
	int expected_k = expected_k_value();

	int64_t result = 0;
	all arg1       = { .B = f1 };
	all arg_1      = { .B = f_1 };
	all arg0       = { .B = f0 };

	for (auto _ : state) {
		int value = A(k, &arg1, &arg_1, &arg_1, &arg1, &arg0);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(normal_functions_static);
