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

#include <ztd/idk/bit.hpp>

#include <catch2/catch_all.hpp>

#include <limits>
#include <cstring>

TEMPLATE_TEST_CASE("bit_operations with count_ones", "[bit_operations][count_ones]", std::uint64_t, std::uint32_t,
     std::uint16_t, std::uint8_t, std::byte, char32_t, char16_t, unsigned char, std::size_t) {
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones
	     = static_cast<TestType>(std::numeric_limits<ztd::any_to_underlying_t<TestType>>::max());
	const int zeroes_val                  = ztd::count_ones(zeroes);
	const int expected_zeroes_val         = 0;
	const int expected_inverse_zeroes_val = ztd::binary_digits_v<TestType>;
	const int ones_val                    = ztd::count_ones(ones);
	const int expected_ones_val           = ztd::binary_digits_v<TestType>;
	const int expected_inverse_ones_val   = 0;
	REQUIRE(zeroes_val == expected_zeroes_val);
	REQUIRE(ones_val == expected_ones_val);

	SECTION("value lsb -> msb") {
		TestType val {};
		for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
			val |= static_cast<TestType>(static_cast<TestType>(1) << i);
			const int value                  = ztd::count_ones(val);
			const int inverse_value          = ztd::count_zeros(val);
			const int expected_value         = static_cast<int>(i + 1);
			const int expected_inverse_value = ztd::binary_digits_v<TestType> - expected_value;
			REQUIRE(value == expected_value);
			REQUIRE(inverse_value == expected_inverse_value);
		}
	}
	SECTION("value msb -> lsb") {
		TestType val {};
		for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
			val |= TestType(static_cast<TestType>(1) << i);
			const int value                  = ztd::count_ones(val);
			const int inverse_value          = ztd::count_zeros(val);
			const int expected_value         = static_cast<int>(ztd::binary_digits_v<TestType> - i);
			const int expected_inverse_value = ztd::binary_digits_v<TestType> - expected_value;
			REQUIRE(value == expected_value);
			REQUIRE(inverse_value == expected_inverse_value);
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with first_(trailing/leading)_one", "[bit_operations][first_(trailing/leading)_one]",
     std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, char32_t, char16_t, unsigned char,
     std::size_t) {
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones
	     = static_cast<TestType>(std::numeric_limits<ztd::any_to_underlying_t<TestType>>::max());

	const int first_trailing_one_zeroes_val          = ztd::first_trailing_one(zeroes);
	const int first_leading_one_zeroes_val           = ztd::first_leading_one(zeroes);
	const int expected_first_trailing_one_zeroes_val = 0;
	const int expected_first_leading_one_zeroes_val  = 0;
	const int first_trailing_one_ones_val            = ztd::first_trailing_one(ones);
	const int first_leading_one_ones_val             = ztd::first_leading_one(ones);
	const int expected_first_trailing_one_ones_val   = 1;
	const int expected_first_leading_one_ones_val    = 1;
	REQUIRE(first_trailing_one_ones_val == expected_first_trailing_one_ones_val);
	REQUIRE(first_leading_one_ones_val == expected_first_leading_one_ones_val);
	REQUIRE(first_trailing_one_zeroes_val == expected_first_trailing_one_zeroes_val);
	REQUIRE(first_leading_one_zeroes_val == expected_first_leading_one_zeroes_val);

	SECTION("val lsb -> msb") {
		SECTION("first_trailing_one") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_trailing_one(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
		}
		SECTION("first_leading_one") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_leading_one(val);
				const int expected_value = static_cast<int>(ztd::binary_digits_v<TestType> - i);
				REQUIRE(value == expected_value);
			}
		}
	}
	SECTION("val msb -> lsb") {
		SECTION("first_trailing_one") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_trailing_one(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
		}
		SECTION("first_leading_one") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				TestType val             = static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_leading_one(val);
				const int expected_value = static_cast<int>(ztd::binary_digits_v<TestType> - i);
				REQUIRE(value == expected_value);
			}
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with first_(trailing/leading)_zero",
     "[bit_operations][first_(trailing/leading)_zero]", std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t,
     std::byte, char32_t, char16_t, unsigned char, std::size_t) {
	TestType zeroes = static_cast<TestType>(0);
	TestType ones   = static_cast<TestType>(std::numeric_limits<ztd::any_to_underlying_t<TestType>>::max());
	int first_trailing_zero_zeroes_val                = ztd::first_trailing_zero(zeroes);
	int first_leading_zero_zeroes_val                 = ztd::first_leading_zero(zeroes);
	const int expected_first_trailing_zero_zeroes_val = 1;
	const int expected_first_leading_zero_zeroes_val  = 1;
	const int first_trailing_zero_ones_val            = ztd::first_trailing_zero(ones);
	const int first_leading_zero_ones_val             = ztd::first_leading_zero(ones);
	const int expected_first_trailing_zero_ones_val   = 0;
	const int expected_first_leading_zero_ones_val    = 0;
	REQUIRE(first_trailing_zero_zeroes_val == expected_first_trailing_zero_zeroes_val);
	REQUIRE(first_leading_zero_zeroes_val == expected_first_leading_zero_zeroes_val);
	REQUIRE(first_trailing_zero_ones_val == expected_first_trailing_zero_ones_val);
	REQUIRE(first_leading_zero_ones_val == expected_first_leading_zero_ones_val);

	SECTION("val lsb -> msb") {
		SECTION("first_trailing_zero") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_trailing_zero(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
		}
		SECTION("first_leading_zero") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_leading_zero(val);
				const int expected_value = static_cast<int>(ztd::binary_digits_v<TestType> - i);
				REQUIRE(value == expected_value);
			}
		}
	}
	SECTION("val msb -> lsb") {
		SECTION("first_trailing_zero") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_trailing_zero(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
		}
		SECTION("first_leading_zero") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				TestType val             = ones & ~static_cast<TestType>(static_cast<TestType>(1) << i);
				const int value          = ztd::first_leading_zero(val);
				const int expected_value = static_cast<int>(ztd::binary_digits_v<TestType> - i);
				REQUIRE(value == expected_value);
			}
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with count_(trailing/leading)_one", "[bit_operations][count_(trailing/leading)_one]",
     std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t, std::byte, char32_t, char16_t, unsigned char,
     std::size_t) {
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones
	     = static_cast<TestType>(std::numeric_limits<ztd::any_to_underlying_t<TestType>>::max());

	const int count_trailing_one_zeroes_val          = ztd::count_trailing_ones(zeroes);
	const int count_leading_one_zeroes_val           = ztd::count_leading_ones(zeroes);
	const int expected_count_trailing_one_zeroes_val = 0;
	const int expected_count_leading_one_zeroes_val  = 0;
	const int count_trailing_one_ones_val            = ztd::count_trailing_ones(ones);
	const int count_leading_one_ones_val             = ztd::count_leading_ones(ones);
	const int expected_count_trailing_one_ones_val   = ztd::binary_digits_v<TestType>;
	const int expected_count_leading_one_ones_val    = ztd::binary_digits_v<TestType>;
	REQUIRE(count_trailing_one_ones_val == expected_count_trailing_one_ones_val);
	REQUIRE(count_leading_one_ones_val == expected_count_leading_one_ones_val);
	REQUIRE(count_trailing_one_zeroes_val == expected_count_trailing_one_zeroes_val);
	REQUIRE(count_leading_one_zeroes_val == expected_count_leading_one_zeroes_val);

	SECTION("val lsb -> msb") {
		SECTION("count_trailing_ones") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask        = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val             = ones & val_mask;
				const int value          = ztd::count_trailing_ones(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
		}
		SECTION("count_leading_ones") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val      = ones & val_mask;
				const int value   = ztd::count_leading_ones(val);
				const int expected_value
				     = (i == (ztd::binary_digits_v<TestType> - 1)) ? ztd::binary_digits_v<TestType> : 0;
				REQUIRE(value == expected_value);
			}
		}
	}
	SECTION("val msb -> lsb") {
		SECTION("count_trailing_ones") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask        = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val             = ones & val_mask;
				const int value          = ztd::count_trailing_ones(val);
				const int expected_value = static_cast<int>(i + 1);
				REQUIRE(value == expected_value);
			}
		}
		SECTION("count_leading_ones") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val      = ones & val_mask;
				const int value   = ztd::count_leading_ones(val);
				const int expected_value
				     = (i == (ztd::binary_digits_v<TestType> - 1)) ? ztd::binary_digits_v<TestType> : 0;
				REQUIRE(value == expected_value);
			}
		}
	}
}

TEMPLATE_TEST_CASE("bit_operations with count_(trailing/leading)_zero",
     "[bit_operations][count_(trailing/leading)_zero]", std::uint64_t, std::uint32_t, std::uint16_t, std::uint8_t,
     std::byte, char32_t, char16_t, unsigned char, std::size_t) {
	static constexpr TestType zeroes = static_cast<TestType>(0);
	static constexpr TestType ones
	     = static_cast<TestType>(std::numeric_limits<::ztd::any_to_underlying_t<TestType>>::max());
	const int count_trailing_zero_zeroes_val          = ztd::count_trailing_zeros(zeroes);
	const int count_leading_zeros_zeroes_val          = ztd::count_leading_zeros(zeroes);
	const int expected_count_trailing_zero_zeroes_val = ztd::binary_digits_v<TestType>;
	const int expected_count_leading_zeros_zeroes_val = ztd::binary_digits_v<TestType>;
	const int count_trailing_zero_ones_val            = ztd::count_trailing_zeros(ones);
	const int count_leading_zeros_ones_val            = ztd::count_leading_zeros(ones);
	const int expected_count_trailing_zero_ones_val   = 0;
	const int expected_count_leading_zeros_ones_val   = 0;
	REQUIRE(count_trailing_zero_zeroes_val == expected_count_trailing_zero_zeroes_val);
	REQUIRE(count_leading_zeros_zeroes_val == expected_count_leading_zeros_zeroes_val);
	REQUIRE(count_trailing_zero_ones_val == expected_count_trailing_zero_ones_val);
	REQUIRE(count_leading_zeros_ones_val == expected_count_leading_zeros_ones_val);

	SECTION("val lsb -> msb") {
		SECTION("count_trailing_zeros") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask        = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val             = ones & val_mask;
				const int value          = ztd::count_trailing_zeros(val);
				const int expected_value = 0;
				REQUIRE(value == expected_value);
			}
		}
		SECTION("count_leading_zeros") {
			for (std::size_t i = 0; i < ztd::binary_digits_v<TestType>; ++i) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask        = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val             = ones & val_mask;
				const int value          = ztd::count_leading_zeros(val);
				const int expected_value = static_cast<int>(ztd::binary_digits_v<TestType> - (i + 1));
				REQUIRE(value == expected_value);
			}
		}
	}
	SECTION("val msb -> lsb") {
		SECTION("count_trailing_zeros") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask        = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val             = ones & val_mask;
				const int value          = ztd::count_trailing_zeros(val);
				const int expected_value = 0;
				REQUIRE(value == expected_value);
			}
		}
		SECTION("count_leading_zeros") {
			for (std::size_t i = ztd::binary_digits_v<TestType>; i-- > 0;) {
				auto underlying_val        = ::ztd::any_enum_or_char_to_underlying(static_cast<TestType>(1) << i);
				TestType val_previous_mask = static_cast<TestType>(underlying_val - 1);
				TestType val_mask        = static_cast<TestType>(static_cast<TestType>(1) << i) | val_previous_mask;
				TestType val             = ones & val_mask;
				const int value          = ztd::count_leading_zeros(val);
				const int expected_value = static_cast<int>(ztd::binary_digits_v<TestType> - (i + 1));
				REQUIRE(value == expected_value);
			}
		}
	}
}
