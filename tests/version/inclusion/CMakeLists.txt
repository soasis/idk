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

# # Tests
file(GLOB_RECURSE ztd.idk.version.tests.inclusion.sources
	LIST_DIRECTORIES FALSE
	CONFIGURE_DEPENDS
	source/*.cpp)

add_executable(ztd.idk.version.tests.inclusion ${ztd.idk.version.tests.inclusion.sources})
target_include_directories(ztd.idk.version.tests.inclusion
	PRIVATE
	../../shared/include)
target_compile_options(ztd.idk.version.tests.inclusion
	PRIVATE
	${--utf8-literal-encoding}
	${--utf8-source-encoding}
	${--disable-permissive}
	${--warn-pedantic}
	${--warn-default}
	${--warn-extra}
	${--warn-errors})
target_link_libraries(ztd.idk.version.tests.inclusion
	PRIVATE
	ztd::version
	Catch2::Catch2
	${CMAKE_DL_LIBS}
)
add_test(NAME ztd.idk.version.tests.inclusion COMMAND ztd.idk.version.tests.inclusion)
