# =============================================================================
#
# ztd.idk
# Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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

cmake_minimum_required(VERSION 3.16.0)
cmake_policy(VERSION 3.16)
# # Project kickstart
# Includes a bunch of basic flags and utilities shared across projects
# See more at the github repository link below
include(FetchContent)
FetchContent_Declare(ztd.cmake
	GIT_REPOSITORY https://github.com/soasis/cmake.git
	GIT_TAG main)
FetchContent_MakeAvailable(ztd.cmake)
set(CMAKE_PROJECT_INCLUDE ${ZTD_CMAKE_PROJECT_PRELUDE})

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(ztd.idk
	VERSION 0.0.0
	DESCRIPTION "The IDK (Industrial Development Kit) Library, for useful tools that get the job done!"
	HOMEPAGE_URL "https://ztdidk.rtfd.io/"
	LANGUAGES CXX)

if (ZTD_IDK_READTHEDOCS)
	# ReadTheDocs seems unable to handle the include at the project level: something must be going wrong?
	include(CheckCXXCompilerFlag)
	include(CheckCCompilerFlag)
	include(CheckIPOSupported)
	include(CMakePackageConfigHelpers)
	include(CMakeDependentOption)
	include(CMakePrintHelpers)
	include(GNUInstallDirs)
	include(FeatureSummary)
	include(FetchContent)
	include(CTest)
endif()

# # # Top-Level Directories
# Check if this is the top-level project or not
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(ZTD_IDK_IS_TOP_LEVEL_PROJECT YES)
else()
	set(ZTD_IDK_IS_TOP_LEVEL_PROJECT NO)
endif()
string(CONCAT ztd-idk-is-top-level $<STREQUAL:${PROJECT_NAME},${CMAKE_PROJECT_NAME}>)

# # Options
option(ZTD_IDK_CI "Whether or not we are in continuous integration mode" OFF)
option(ZTD_IDK_READTHEDOCS "Whether or not we are building inside of ReadTheDocs" OFF)
option(ZTD_IDK_TESTS "Enable build of tests" OFF)
option(ZTD_IDK_DOCUMENTATION "Enable build of documentation" OFF)
option(ZTD_IDK_DOCUMENTATION_NO_SPHINX "Turn off Sphinx usage (useful for ReadTheDocs builds)" OFF)
option(ZTD_IDK_EXAMPLES "Enable build of examples" OFF)
option(ZTD_IDK_BENCHMARKS "Enable build of benchmarks" OFF)
option(ZTD_IDK_GENERATE_SINGLE "Enable generation of a single header and its target" OFF)

# Modify bad flags / change defaults if we are the top level
if (ztd-idk-is-top-level)
	if (CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
	endif()

	if (NOT DEFINED CMAKE_CXX_STANDARD)
		set(CMAKE_CXX_STANDARD 17)
	endif()

	if (NOT DEFINED CMAKE_CXX_STANDARD)
		set(CMAKE_C_STANDARD 11)
	endif()

	if (ZTD_IDK_BENCHMARKS OR ZTD_IDK_EXAMPLES OR ZTD_IDK_TESTS OR ZTD_IDK_SCRATCH)
		# normal flags
		check_compiler_flag(disable-permissive MSVC /permissive- GCC -pedantic)
		# Warning flags
		check_compiler_flag(warn-pedantic MSVC /permissive- GCC -pedantic)
		check_compiler_flag(warn-all MSVC /W4 GCC -Wall)
		check_compiler_flag(warn-errors MSVC /WX GCC -Werror)
		check_compiler_flag(warn-errors CLANG -Wextra)
		check_compiler_flag(utf8-literal-encoding MSVC /execution-charset:utf-8 GCC -fexec-charset=utf-8)
		check_compiler_flag(utf8-source-encoding MSVC /source-charset:utf-8 GCC -finput-charset=utf-8)
		check_compiler_flag(extra-constexpr-depth MSVC /constexpr:depth2147483647 GCC -fconstexpr-depth=2147483647 CLANG -fconstexpr-depth=2147483647)
		check_compiler_flag(extra-constexpr-steps MSVC /constexpr:steps2147483647 GCC -fconstexpr-ops-limit=2147483647 CLANG -fconstexpr-steps=2147483647)
		check_compiler_flag(template-debugging-mode GCC -ftemplate-backtrace-limit=0)
	endif()
endif()

# # Main library declarations
# ztd.version
add_library(ztd.version INTERFACE)
add_library(ztd::version ALIAS ztd.version)
target_include_directories(ztd.version
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_sources(ztd.version INTERFACE include/ztd/version.hpp include/ztd/version/version.hpp)
install(DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_package_config_file(
	cmake/ztd.version-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.version/ztd.version-config.cmake"
	INSTALL_DESTINATION lib/cmake/ztd.version
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.version/ztd.version-config-version.cmake"
	COMPATIBILITY SameMajorVersion)

export(TARGETS ztd.version
	FILE
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.version/ztd.version-targets.cmake")

# ztd.tag_invoke
file(GLOB_RECURSE ztd.tag_invoke.includes CONFIGURE_DEPENDS include/tag_invoke*.hpp)

add_library(ztd.tag_invoke INTERFACE)
add_library(ztd::tag_invoke ALIAS ztd.tag_invoke)
target_include_directories(ztd.tag_invoke
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(ztd.tag_invoke
	INTERFACE
		ztd::version
)
target_sources(ztd.tag_invoke INTERFACE ${ztd.tag_invoke.includes})
install(DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_package_config_file(
	cmake/ztd.tag_invoke-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.tag_invoke/ztd.tag_invoke-config.cmake"
	INSTALL_DESTINATION lib/cmake/ztd.tag_invoke
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.tag_invoke/ztd.tag_invoke-config-version.cmake"
	COMPATIBILITY SameMajorVersion)

export(TARGETS ztd.tag_invoke
	FILE
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.tag_invoke/ztd.tag_invoke-targets.cmake")

# ztd.idk
file(GLOB_RECURSE ztd.idk.includes CONFIGURE_DEPENDS include/idk*.hpp)

add_library(ztd.idk INTERFACE)
add_library(ztd::idk ALIAS ztd.idk)
target_include_directories(ztd.idk
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_sources(ztd.idk INTERFACE ${ztd.idk.includes})
target_link_libraries(ztd.idk
	INTERFACE
		ztd::version
		ztd::tag_invoke
)
install(DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

configure_package_config_file(
	cmake/ztd.idk-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.idk/ztd.idk-config.cmake"
	INSTALL_DESTINATION lib/cmake/ztd.idk
	NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.idk/ztd.idk-config-version.cmake"
	COMPATIBILITY SameMajorVersion)

export(TARGETS ztd.idk
	FILE
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/ztd.idk/ztd.idk-targets.cmake")


if (ZTD_IDK_GENERATE_SINGLE)
	add_subdirectory(single)
endif()


# # Benchmarks, Tests, Examples and Documentation
if (ZTD_IDK_TESTS)
	include(CTest)
	add_subdirectory(tests)
endif()

if (ZTD_IDK_DOCUMENTATION)
	add_subdirectory(documentation)
endif()
if (ZTD_IDK_BENCHMARKS)
	add_subdirectory(benchmarks)
endif()
if (ZTD_IDK_EXAMPLES)
	add_subdirectory(examples)
endif()

# For quick debugging and development only: don't peek! 🙈
mark_as_advanced(ZTD_IDK_SCRATCH)
if (ZTD_IDK_SCRATCH)
	add_executable(scratch main.cpp)
	target_link_libraries(scratch PRIVATE ztd::idk)
	target_include_directories(scratch PRIVATE tests/shared/include)
	target_compile_options(scratch
		PRIVATE
		${--template-debugging-mode}
		${--disable-permissive}
		${--warn-pedantic}
		${--warn-all}
		${--warn-extra}
		${--warn-errors})
endif()
