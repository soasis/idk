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

function (crunch_dependency_jail)
	FetchContent_Declare(crunch
		GIT_REPOSITORY https://github.com/dragonmux/crunch.git
		GIT_TAG        main
	)
	FetchContent_GetProperties(crunch)
	if (NOT crunch_POPULATED)
		# Fetch the content using previously declared details
		FetchContent_MakeAvailable(crunch)
		# Now build it using meson
		find_program(meson_executable
			NAMES
				meson meson.exe
			REQUIRED
		)
		file(GLOB_RECURSE crunch_sources
			LIST_DIRECTORIES false
			CONFIGURE_DEPENDS
			${crunch_SOURCE_DIR}/*.*
		)
		add_custom_command(OUTPUT ${crunch_BINARY_DIR}/meson-info/meson-info.json
			COMMAND
				${meson_executable} setup
				--warnlevel 0
				--optimization 3
				--prefix ${crunch_BINARY_DIR}/crunch-install
				${crunch_BINARY_DIR} ${crunch_SOURCE_DIR} 
			DEPENDS ${crunch_sources}
		)
		add_custom_command(OUTPUT
			${crunch_BINARY_DIR}/crunch/${CMAKE_STATIC_LIBRARY_PREFIX}crunch.${CMAKE_STATIC_LIBRARY_SUFFIX}
			${crunch_BINARY_DIR}/crunch/version.h
			COMMAND
				${meson_executable} compile -C ${crunch_BINARY_DIR}
			COMMAND
				${meson_executable} install -C ${crunch_BINARY_DIR}
			DEPENDS
				${crunch_sources}
				${crunch_BINARY_DIR}/meson-info/meson-info.json
		)
		add_custom_target(crunch_build
			DEPENDS
				${crunch_BINARY_DIR}/crunch/${CMAKE_STATIC_LIBRARY_PREFIX}crunch.${CMAKE_STATIC_LIBRARY_SUFFIX}
				${crunch_BINARY_DIR}/crunch/version.h
				${crunch_sources}
				${crunch_BINARY_DIR}/meson-info/meson-info.json
		)
		add_library(crunch INTERFACE)
		target_link_libraries(crunch
			INTERFACE
				${crunch_BINARY_DIR}/crunch/${CMAKE_STATIC_LIBRARY_PREFIX}crunch.${CMAKE_STATIC_LIBRARY_SUFFIX}
		)
		target_include_directories(crunch
			INTERFACE
				${crunch_BINARY_DIR}/crunch
				${crunch_SOURCE_DIR}/substrate/substrate
		)
		add_library(crunch::crunch ALIAS crunch)
	endif()
endfunction()
#crunch_dependency_jail()

# # Tests
file(GLOB_RECURSE ztd.idk.tests.basic_run_time_c.sources
	LIST_DIRECTORIES FALSE
	CONFIGURE_DEPENDS
	source/*.c
)
add_executable(ztd.idk.tests.basic_run_time_c ${ztd.idk.tests.basic_run_time_c.sources})
target_compile_options(ztd.idk.tests.basic_run_time_c
	PRIVATE
	${--utf8-literal-encoding}
	${--utf8-source-encoding}
	${--disable-permissive}
	${--warn-pedantic}
	${--warn-default}
	${--warn-extra}
	${--warn-errors})
target_link_libraries(ztd.idk.tests.basic_run_time_c
	PRIVATE
	ztd::idk
	${CMAKE_DL_LIBS}
)
add_test(NAME ztd.idk.tests.basic_run_time_c COMMAND ztd.idk.tests.basic_run_time_c)
