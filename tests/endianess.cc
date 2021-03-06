#include "gtest/gtest.h"

#include <memory>
#include <cstddef>
#include <cstdint>

#include "detail/io/buffer.h"

#include "type/tuple.h"
#include "type/custom_serializable.h"

#include "endianess/little.h"
#include "endianess/big.h"

class EndianTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
			const std::size_t tupleSize = sizeof(std::uint64_t) +
			                              sizeof(std::uint32_t) +
			                              sizeof(std::int16_t);

			this->buffer_ = std::unique_ptr<BinaryMapping::dtl::Buffer>(
				new BinaryMapping::dtl::Buffer(tupleSize)
			);
		}

		std::unique_ptr<BinaryMapping::dtl::Buffer> buffer_;

		std::tuple<
			std::uint64_t,
			std::uint32_t,
			std::int16_t,
			BinaryMapping::ByteField<3>
		> test_ = std::make_tuple(
			UINT32_MAX,
			UINT16_MAX,
			INT8_MIN,
			BinaryMapping::ByteField<3>({1, 2, 3})
		);


};

TEST_F(EndianTest, LittleEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		std::uint64_t,
		std::uint32_t,
		std::int16_t,
		BinaryMapping::ByteField<3>
	>::type<std::uint8_t> TestMapping;

	TestMapping mapping(this->buffer_->front());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);
	mapping.set<3>(BinaryMapping::ByteField<3>({1, 2, 3}));

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::ByteField<3>({1, 2, 3}));

	EXPECT_EQ(static_cast<TestMapping::value_type>(mapping), this->test_);
}

TEST_F(EndianTest, BigEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		std::uint64_t,
		std::uint32_t,
		std::int16_t,
		BinaryMapping::ByteField<3>
	>::type<std::uint8_t> TestMapping;

	TestMapping mapping(this->buffer_->front());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);
	mapping.set<3>(BinaryMapping::ByteField<3>({1, 2, 3}));

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::ByteField<3>({1, 2, 3}));

	EXPECT_EQ(static_cast<TestMapping::value_type>(mapping), this->test_);
}

TEST_F(EndianTest, UndefinedEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::UndefinedEndian,
		std::uint64_t,
		std::uint32_t,
		std::int16_t,
		BinaryMapping::ByteField<3>
	>::type<std::uint8_t> TestMapping;

	TestMapping mapping(this->buffer_->front());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);
	mapping.set<3>(BinaryMapping::ByteField<3>({1, 2, 3}));

	mapping.serialize<BinaryMapping::BigEndian>();

	EXPECT_NE(mapping.get<0>(), UINT32_MAX);
	EXPECT_NE(mapping.get<1>(), UINT16_MAX);
	EXPECT_NE(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::ByteField<3>({1, 2, 3}));

	mapping.deserialize<BinaryMapping::BigEndian>();

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::ByteField<3>({1, 2, 3}));

	EXPECT_EQ(static_cast<TestMapping::value_type>(mapping), this->test_);
}

TEST_F(EndianTest, MixedEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		std::uint64_t,
		std::uint32_t,
		std::int16_t
	>::type<std::uint8_t> BigTestMapping;

	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		std::uint64_t,
		std::uint32_t,
		std::int16_t
	>::type<std::uint8_t> LittleTestMapping;

	BigTestMapping bigMapping(this->buffer_->front());

	bigMapping.set<0>(UINT32_MAX);
	bigMapping.set<1>(UINT16_MAX);
	bigMapping.set<2>(INT8_MIN);

	LittleTestMapping littleMapping(this->buffer_->front());

	EXPECT_EQ(littleMapping.get<0>(), 18446744069414584320ul);
	EXPECT_EQ(littleMapping.get<1>(), 4294901760);
	EXPECT_EQ(littleMapping.get<2>(), -32513);
}
