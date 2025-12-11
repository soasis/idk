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
	struct Arg {
		virtual int run() = 0;
		virtual ~Arg() { };
	};

	int A(int, std::shared_ptr<Arg>, std::shared_ptr<Arg>, std::shared_ptr<Arg>, std::shared_ptr<Arg>,
	     std::shared_ptr<Arg>);

	class B : public Arg, public std::enable_shared_from_this<B> {
	private:
		int k;
		const std::shared_ptr<Arg> x1, x2, x3, x4;

	public:
		B(int _k, std::shared_ptr<Arg> _x1, std::shared_ptr<Arg> _x2, std::shared_ptr<Arg> _x3,
		     std::shared_ptr<Arg> _x4)
		: k(_k), x1(_x1), x2(_x2), x3(_x3), x4(_x4) {
		}
		int run() {
			return A(--k, this->shared_from_this(), x1, x2, x3, x4);
		}
	};

	class Const : public Arg {
	private:
		const int x;

	public:
		Const(int _x) : x(_x) {
		}
		int run() {
			return x;
		}
	};

	int A(int k, std::shared_ptr<Arg> x1, std::shared_ptr<Arg> x2, std::shared_ptr<Arg> x3, std::shared_ptr<Arg> x4,
	     std::shared_ptr<Arg> x5) {
		if (k <= 0)
			return x4->run() + x5->run();
		else {
			std::shared_ptr<Arg> b(new B(k, x1, x2, x3, x4));
			return b->run();
		}
	}
} // namespace

static void cxx03_shared_ptr_rosetta(benchmark::State& state) {
	int k          = k_value();
	int expected_k = expected_k_value();

	int64_t result = 0;
	auto arg1      = std::make_shared<Const>(1);
	auto arg2      = std::make_shared<Const>(-1);
	auto arg3      = std::make_shared<Const>(-1);
	auto arg4      = std::make_shared<Const>(1);
	auto arg5      = std::make_shared<Const>(0);

	for (auto _ : state) {
		int value = A(k, arg1, arg2, arg3, arg4, arg5);
		result += value == expected_k ? 1 : 0;
	}

	if (result != state.iterations()) {
		state.SkipWithError("failed: did not produce the right answer!");
	}
}

BENCHMARK(cxx03_shared_ptr_rosetta);
