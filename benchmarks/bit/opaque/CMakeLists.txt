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

# # Opaque Library
file(GLOB_RECURSE ztd.idk.benchmarks.opaque.sources
	CONFIGURE_DEPENDS
	source/**.cpp source/**.c)

add_library(ztd.idk.benchmarks.opaque SHARED ${ztd.idk.benchmarks.opaque.sources})
add_library(ztd::idk::benchmarks::opaque ALIAS ztd.idk.benchmarks.opaque)
target_include_directories(ztd.idk.benchmarks.opaque
	PUBLIC
	include/
)
target_link_libraries(ztd.idk.benchmarks.opaque PRIVATE
	ztd::idk
	${CMAKE_DL_LIBS}
)
target_compile_definitions(ztd.idk.benchmarks.opaque
	PRIVATE
	ZTD_OPAQUE_BUILD=1
)
target_compile_definitions(ztd.idk.benchmarks.opaque
	PUBLIC
	ZTD_OPAQUE_DLL=1
)
target_compile_options(ztd.idk.benchmarks.opaque PRIVATE 
	${--utf8-literal-encoding}
	${--utf8-source-encoding}
	${--disable-permissive}
	${--warn-pedantic}
	${--warn-default}
	${--warn-extra}
	${--warn-errors}
)
