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
typedef struct All {
  int (*B)(struct All *);
  int k;
  struct All *x1, *x2, *x3, *x4, *x5;
} All_t;

int A(int k, All_t *x1, All_t *x2, All_t *x3, All_t *x4, All_t *x5);

int B(struct All *self) {
  return A(--self->k, self, self->x1, self->x2, self->x3, self->x4);
}

int A(int k, All_t *x1, All_t *x2, All_t *x3, All_t *x4, All_t *x5) {
  if (k <= 0) {
    return x4->B(x4) + x5->B(x5);
  } else {
    struct All y = { B: B, k: k, x1: x1, x2: x2, x3: x3, x4: x4, x5: x5};
    return B(&y);
 }
}

int p1(struct All *p) { return 1; }

int m1(struct All *p) { return -1; }

int z0(struct All *p) { return 0; }


} // namespace

static void plain_c(benchmark::State& state) {
	int k          = k_value();
	int expected_k = expected_k_value();

	int64_t result = 0;
	struct All P1 = {.B = p1};
 	struct All M1 = {.B = m1};
  	struct All Z0 = {.B = z0};

	for (auto _ : state) {
		int value =  A(k, &P1, &M1, &M1, &P1, &Z0);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(plain_c);
