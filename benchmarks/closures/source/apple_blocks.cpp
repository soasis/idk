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

#include <ztd/idk/version.hpp>

#if ZTD_IS_ON(ZTD_COMPILER_CLANG)

#define INT(body) ^() { body; }

namespace {

	typedef int(fn_t)(void);

	static int a(int arg_k, fn_t ^ x1, fn_t ^ x2, fn_t ^ x3, fn_t ^ x4, fn_t ^ x5) {
		__block int k    = arg_k;
		__block fn_t ^ b = ^(void) { return a(--k, b, x1, x2, x3, x4); };
		return k <= 0 ? x4() + x5() : b();
	}

	static void apple_blocks(benchmark::State& state) {
		int k          = k_value();
		int expected_k = expected_k_value();
		int64_t result = 0;

		fn_t ^ arg1 = ^() { return 1; };
		fn_t ^ arg2 = ^() { return -1; };
		fn_t ^ arg3 = ^() { return -1; };
		fn_t ^ arg4 = ^() { return 1; };
		fn_t ^ arg5 = ^() { return 0; };

		for (auto _ : state) {
			int value = a(k, arg1, arg2, arg3, arg4, arg5);
			result += value == expected_k ? 1 : 0;
		}

		if (result != state.iterations()) {
			state.SkipWithError("failed: did not produce the right answer!");
		}
	}
} // namespace

BENCHMARK(apple_blocks);

#endif
