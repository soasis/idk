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
# k_value library
add_subdirectory(k_value)
# nontype_functional
FetchContent_Declare(
	nontype_functional
	GIT_REPOSITORY https://github.com/zhihaoy/nontype_functional.git
	GIT_TAG main
	EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(nontype_functional)

# # Benchmark Executable
file(GLOB_RECURSE ztd.idk.benchmarks.closures.sources CONFIGURE_DEPENDS source/**)

# # Needed flags
check_compiler_flag(use-blocks GCC -fblocks Clang -fblocks)
check_compiler_diagnostic(c99-extensions)

add_executable(ztd.idk.benchmarks.closures ${ztd.idk.benchmarks.closures.sources})
target_include_directories(ztd.idk.benchmarks.closures PRIVATE
	include
	source/include
)
target_link_libraries(ztd.idk.benchmarks.closures PRIVATE
	ztd::blocks
	ztd::idk
	ztd::idk::benchmarks::closures::k_value
	std23::nontype_functional
	benchmark
	${CMAKE_DL_LIBS}
)
target_compile_options(ztd.idk.benchmarks.closures
	PRIVATE
	${--utf8-literal-encoding}
	${--utf8-source-encoding}
	${--use-blocks}
	${--allow-microsoft-enum-value}
	${--allow-c99-extensions}
)
set_target_properties(ztd.idk.benchmarks.closures
	PROPERTIES
	CXX_EXTENSIONS TRUE
)

ztd_tools_add_benchmark_grapher(
	NAME
		closures
	CONFIG
		"${CMAKE_CURRENT_SOURCE_DIR}/graph_config.json"
	TARGETS
		ztd.idk.benchmarks.closures
	REPETITIONS
		${ZTD_IDK_BENCHMARKS_CLOSURE_REPETITIONS}
)
