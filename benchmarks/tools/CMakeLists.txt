# =============================================================================
#
# ztd.idk
# Copyright © 2022 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
#		http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ============================================================================>

# # Dependencies
# Standard Dependencies
find_package(Python3)
# Needed utilities
include(identify_stdlib)

# # Setup
identify_stdlib(current_stdlib)
message(STATUS "[ztd.idk.benchmarks.tools] benchmarks will be reported for ${current_stdlib} ...")

set(ZTD_IDK_BENCHMARKS_CONFIG_SOURCEFILE "${CMAKE_CURRENT_SOURCE_DIR}/../bit/graph_config.json")
set(ZTD_IDK_BENCHMARKS_CONFIG_INPUTFILE "${CMAKE_CURRENT_BINARY_DIR}/results/bit/graph_config.json")
set(ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE "${CMAKE_CURRENT_BINARY_DIR}/results/bit/${current_stdlib}.ztd.idk.benchmarks.bit.json")
set(ZTD_IDK_BENCHMARKS_RESULTS_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/results/bit")
set(ZTD_IDK_BENCHMARKS_ANALYSIS_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/results/bit")

# # Commands and Targets
add_custom_command(
	OUTPUT ${ZTD_IDK_BENCHMARKS_CONFIG_INPUTFILE}
	COMMAND ${CMAKE_COMMAND} -E copy
		${ZTD_IDK_BENCHMARKS_CONFIG_SOURCEFILE}
		${ZTD_IDK_BENCHMARKS_CONFIG_INPUTFILE}
	DEPENDS ${ZTD_IDK_BENCHMARKS_CONFIG_SOURCEFILE}
	COMMENT "[ztd.idk/benchmarks] Copying configuration file from '${ZTD_IDK_BENCHMARKS_CONFIG_SOURCEFILE}' to '${ZTD_IDK_BENCHMARKS_CONFIG_INPUTFILE}'."
)

add_custom_target(ztd.idk.benchmarks.config_generator
	DEPENDS "${ZTD_IDK_BENCHMARKS_CONFIG_SOURCEFILE}" "${ZTD_IDK_BENCHMARKS_CONFIG_INPUTFILE}"
)

add_custom_command(
	OUTPUT "${ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE}"
	COMMAND ztd.idk.benchmarks.bit
		--benchmark_out=${ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE}
		--benchmark_out_format=json
		--benchmark_repetitions=${ZTD_IDK_BENCHMARKS_REPETITIONS}
	DEPENDS ztd.idk.benchmarks.bit
	COMMENT "[ztd.idk/benchmarks] Executing Benchmarks and outputting to '${ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE}'"
)

add_custom_target(ztd.idk.benchmarks.data_generator
	DEPENDS "${ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE}"
)

if (Python3_Interpreter_FOUND)
	add_custom_target(ztd.idk.benchmarks.graphs_generator
		COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_graphs/__main__.py
			-c "${ZTD_IDK_BENCHMARKS_CONFIG_SOURCEFILE}"
			-i "${ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE}"
			-o "${ZTD_IDK_BENCHMARKS_ANALYSIS_OUTDIR}"
		DEPENDS ztd.idk.benchmarks.data_generator ztd.idk.benchmarks.config_generator
		COMMENT "[ztd.idk/benchmarks] Graphing '${ZTD_IDK_BENCHMARKS_RESULTS_OUTFILE}' data to '${ZTD_IDK_BENCHMARKS_RESULTS_OUTDIR}'"
	)
endif()

function (make_benchmark_targets)

endfunction()
