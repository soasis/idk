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

#include <ztd/idk/version.h>

#include <closures/gnu_nested_functions_impl.h>

#if ZTD_IS_ON(ZTD_COMPILER_GCC)

#define INT(VAL)             \
	({                      \
		int lambda(void) { \
			return VAL;   \
		};                 \
		lambda;            \
	})

inline static int f_1() {
	return -1;
}

inline static int f0() {
	return 0;
}

inline static int f1() {
	return 1;
}

inline static int gnu_nested_functions_a(int k, int xl(void), int x2(void), int x3(void), int x4(void), int x5(void)) {
	int b(void) {
		return gnu_nested_functions_a(--k, b, xl, x2, x3, x4);
	}
	return k <= 0 ? x4() + x5() : b();
}

extern int gnu_nested_functions_benchmark(int k) {
	return gnu_nested_functions_a(k, f1, f_1, f_1, f1, f0);
}

extern int gnu_nested_functions_benchmark_rosetta(int k) {
	f_t* argf1  = INT(+1);
	f_t* argf_1 = INT(-1);
	f_t* argf0  = INT(0);
	return gnu_nested_functions_a(k, argf1, argf_1, argf_1, argf1, argf0);
}

#endif
