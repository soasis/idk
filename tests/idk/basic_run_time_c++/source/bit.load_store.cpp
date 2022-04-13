// =============================================================================
//
// ztd.idk
// Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================>

#include <ztd/idk/bit.h>
#include <ztd/idk/endian.h>
#include <ztd/idk/type_traits.hpp>

#include <catch2/catch_all.hpp>

#include <cstring>

template <typename TYPE>
constexpr TYPE pick_constant() noexcept {
	if constexpr (std::is_unsigned_v<TYPE>) {
		if constexpr (std::is_same_v<TYPE, char>)
			return 0x12U;
		if constexpr (std::is_same_v<TYPE, unsigned char>)
			return 0x12U;
		else if constexpr (std::is_same_v<TYPE, unsigned short>)
			return 0x1234U;
		else if constexpr (std::is_same_v<TYPE, unsigned int>)
			return 0x1234U;
		else if constexpr (std::is_same_v<TYPE, unsigned long>)
			return 0x12345678UL;
		else if constexpr (std::is_same_v<TYPE, unsigned long long>)
			return 0x0123456789ABCDEFULL;
		else
			static_assert(ztd::always_false_v<TYPE>);
	}
	else {
		if constexpr (std::is_same_v<TYPE, char>)
			return -0x12;
		if constexpr (std::is_same_v<TYPE, signed char>)
			return -0x12;
		else if constexpr (std::is_same_v<TYPE, short>)
			return -0x1234;
		else if constexpr (std::is_same_v<TYPE, int>)
			return -0x1234U;
		else if constexpr (std::is_same_v<TYPE, long>)
			return -0x12345678L;
		else if constexpr (std::is_same_v<TYPE, long long>)
			return -0x0123456789ABCDEFLL;
		else
			static_assert(ztd::always_false_v<TYPE>);
	}
}

TEST_CASE("bit/load-store", "Ensure that the 8-bit load and store work properly for all array sizes.") {
#define SECTION_CASE(N)                                                                                     \
	SECTION("uint_least" #N "_t, little") {                                                                \
		SECTION("unaligned") {                                                                            \
			unsigned char arr[N / CHAR_BIT] {};                                                          \
			uint_least##N##_t data = static_cast<uint_least##N##_t>(pick_constant<uint_least##N##_t>()); \
			ztdc_store8_leu##N(data, arr);                                                               \
			uint_least##N##_t result = ztdc_load8_leu##N(arr);                                           \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_LITTLE_ENDIAN) {                                         \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) == 0);                                \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) != 0);                                \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
		SECTION("aligned") {                                                                              \
			alignas(N / CHAR_BIT) uint_least##N##_t arr {};                                              \
			uint_least##N##_t data = static_cast<uint_least##N##_t>(pick_constant<uint_least##N##_t>()); \
			ztdc_store8_leu##N(data, (unsigned char*)&arr);                                              \
			uint_least##N##_t result = ztdc_load8_aligned_leu##N((unsigned char*)&arr);                  \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_LITTLE_ENDIAN) {                                         \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
	}                                                                                                      \
	SECTION("int_least" #N "_t, little, negative") {                                                       \
		SECTION("unaligned") {                                                                            \
			unsigned char arr[N / CHAR_BIT] {};                                                          \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<int_least##N##_t>());    \
			ztdc_store8_les##N(data, (unsigned char*)&arr);                                              \
			int_least##N##_t result = ztdc_load8_les##N((unsigned char*)&arr);                           \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_LITTLE_ENDIAN) {                                         \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) == 0);                                \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) != 0);                                \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
		SECTION("aligned") {                                                                              \
			alignas(N / CHAR_BIT) int_least##N##_t arr {};                                               \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<int_least##N##_t>());    \
			ztdc_store8_les##N(data, (unsigned char*)&arr);                                              \
			int_least##N##_t result = ztdc_load8_les##N((unsigned char*)&arr);                           \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_LITTLE_ENDIAN) {                                         \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
	}                                                                                                      \
	SECTION("int_least" #N "_t, little, positive") {                                                       \
		SECTION("unaligned") {                                                                            \
			unsigned char arr[N / CHAR_BIT] {};                                                          \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<uint_least##N##_t>());   \
			ztdc_store8_les##N(data, arr);                                                               \
			int_least##N##_t result = ztdc_load8_les##N(arr);                                            \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_LITTLE_ENDIAN) {                                         \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) == 0);                                \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) != 0);                                \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
		SECTION("aligned") {                                                                              \
			alignas(N / CHAR_BIT) int_least##N##_t arr {};                                               \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<uint_least##N##_t>());   \
			ztdc_store8_les##N(data, (unsigned char*)&arr);                                              \
			int_least##N##_t result = ztdc_load8_les##N((unsigned char*)&arr);                           \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_LITTLE_ENDIAN) {                                         \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
	}                                                                                                      \
	SECTION("uint_least" #N "_t, big") {                                                                   \
		SECTION("unaligned") {                                                                            \
			unsigned char arr[N / CHAR_BIT] {};                                                          \
			uint_least##N##_t data = static_cast<uint_least##N##_t>(pick_constant<uint_least##N##_t>()); \
			ztdc_store8_beu##N(data, arr);                                                               \
			uint_least##N##_t result = ztdc_load8_beu##N(arr);                                           \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_BIG_ENDIAN) {                                            \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
		SECTION("aligned") {                                                                              \
			alignas(N / CHAR_BIT) uint_least##N##_t arr {};                                              \
			uint_least##N##_t data = static_cast<uint_least##N##_t>(pick_constant<uint_least##N##_t>()); \
			ztdc_store8_beu##N(data, (unsigned char*)&arr);                                              \
			uint_least##N##_t result = ztdc_load8_beu##N((unsigned char*)&arr);                          \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_BIG_ENDIAN) {                                            \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
	}                                                                                                      \
	SECTION("int_least" #N "_t, big, negative") {                                                          \
		SECTION("unaligned") {                                                                            \
			unsigned char arr[N / CHAR_BIT] {};                                                          \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<int_least##N##_t>());    \
			ztdc_store8_bes##N(data, arr);                                                               \
			int_least##N##_t result = ztdc_load8_bes##N(arr);                                            \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_BIG_ENDIAN) {                                            \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) == 0);                                \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) != 0);                                \
				}                                                                                       \
				REQUIRE(result == data);                                                                \
			}                                                                                            \
		}                                                                                                 \
		SECTION("aligned") {                                                                              \
			alignas(N / CHAR_BIT) int_least##N##_t arr {};                                               \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<int_least##N##_t>());    \
			ztdc_store8_bes##N(data, (unsigned char*)&arr);                                              \
			int_least##N##_t result = ztdc_load8_aligned_bes##N((unsigned char*)&arr);                   \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_BIG_ENDIAN) {                                            \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
	}                                                                                                      \
	SECTION("int_least" #N "_t, big, positive") {                                                          \
		SECTION("unaligned") {                                                                            \
			unsigned char arr[N / CHAR_BIT] {};                                                          \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<uint_least##N##_t>());   \
			ztdc_store8_bes##N(data, arr);                                                               \
			int_least##N##_t result = ztdc_load8_bes##N(arr);                                            \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_BIG_ENDIAN) {                                            \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) == 0);                                \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(arr, &data, sizeof(arr)) != 0);                                \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
		SECTION("aligned") {                                                                              \
			alignas(N / CHAR_BIT) int_least##N##_t arr {};                                               \
			int_least##N##_t data = static_cast<int_least##N##_t>(pick_constant<uint_least##N##_t>());   \
			ztdc_store8_bes##N(data, (unsigned char*)&arr);                                              \
			int_least##N##_t result = ztdc_load8_aligned_bes##N((unsigned char*)&arr);                   \
			if (N > 8) {                                                                                 \
				if (ZTDC_NATIVE_ENDIAN == ZTDC_BIG_ENDIAN) {                                            \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) == 0);                               \
				}                                                                                       \
				else {                                                                                  \
					REQUIRE(std::memcmp(&arr, &data, sizeof(arr)) != 0);                               \
				}                                                                                       \
			}                                                                                            \
			REQUIRE(result == data);                                                                     \
		}                                                                                                 \
	}                                                                                                      \
	static_assert(true, "👍")

	SECTION_CASE(8);
	SECTION_CASE(16);
	SECTION_CASE(32);
	SECTION_CASE(64);
}
