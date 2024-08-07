# =============================================================================
#
# ztd.idk
# Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
# Contact: opensource@soasis.org
#
# Commercial License Usage
# Licensees holding valid commercial ztd.idk licenses may use this file in
# accordance with the commercial license agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and Shepherd's Oasis, LLC.
# For licensing terms and conditions see your agreement. For
# further information contact opensource@soasis.org.
#
# Apache License Version 2 Usage
# Alternatively, this file may be used under the terms of Apache License
# Version 2.0 (the "License") for non-commercial use; you may not use this
# file except in compliance with the License. You may obtain a copy of the
# License at
#
# https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ============================================================================>

# # Dependencies
# google benchmark
function (google_benchmark_dependency_jail)
	FetchContent_Declare(
		google_benchmark
		GIT_REPOSITORY https://github.com/google/benchmark.git
		GIT_TAG main
		EXCLUDE_FROM_ALL
	)
	# Benchmark variables, internal setup
	set(BENCHMARK_ENABLE_EXCEPTIONS ON)
	set(BENCHMARK_ENABLE_TESTING OFF)
	set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF)
	set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
	set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
	set(BENCHMARK_ENABLE_WERROR OFF)
	set(BENCHMARK_FORCE_WERROR OFF)
	set(BENCHMARK_ENABLE_INSTALL OFF)
	set(BENCHMARK_ENABLE_TESTING OFF)
	set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
	set(BENCHMARK_ENABLE_WERROR OFF)
	set(BENCHMARK_FORCE_WERROR OFF)
	if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND WIN32)
		# google benchmark is broken, so we need to force HAVE_STD_REGEX to be on for this.
		set(HAVE_STD_REGEX ON)
	endif()
	FetchContent_MakeAvailable(google_benchmark)
endfunction()
google_benchmark_dependency_jail()

# # Benchmarks
# Bit benchmarks
add_subdirectory(bit)
