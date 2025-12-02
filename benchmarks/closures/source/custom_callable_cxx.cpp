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

	typedef int(fn_t)(void);
	typedef struct call_t call_t_t;

	static int A(int k, const call_t& x1, const call_t& x2, const call_t& x3, const call_t& x4, const call_t& x5);

	typedef struct call_t {
		typedef struct direct_t {
			fn_t* direct;
		} direct_t;
		typedef struct recurse_t {
			mutable int k;
			const call_t *x1, *x2, *x3, *x4, *x5;
		} recurse_t;
		bool type;
		union {
			direct_t d;
			recurse_t r;
		};

		inline int operator()(void) const {
			if (type) {
				return d.direct();
			}
			else {
				return A(--r.k, *r.x1, *r.x2, *r.x3, *r.x4, *r.x5);
			}
		}
	} call_t;

	static int A(int k, const call_t& x1, const call_t& x2, const call_t& x3, const call_t& x4, const call_t& x5) {
		call_t B { .type = false, .r = call_t::recurse_t { k, &B, &x1, &x2, &x3, &x4 } };
		return B.r.k <= 0 ? x4() + x5() : B();
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

static void custom_callable_cxx(benchmark::State& state) {
	int k          = k_value();
	int expected_k = expected_k_value();

	int64_t result = 0;
	auto arg1      = call_t { true, call_t::direct_t { f1 } };
	auto arg2      = call_t { true, call_t::direct_t { f_1 } };
	auto arg3      = call_t { true, call_t::direct_t { f_1 } };
	auto arg4      = call_t { true, call_t::direct_t { f1 } };
	auto arg5      = call_t { true, call_t::direct_t { f0 } };

	for (auto _ : state) {
		int value = A(k, arg1, arg2, arg3, arg4, arg5);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(custom_callable_cxx);
