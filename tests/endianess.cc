#include "gtest/gtest.h"

#include <memory>

#include "tuple/tuple.h"
#include "endianess/little.h"
#include "endianess/big.h"
#include "raw.h"

class EndianTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
			const size_t tupleSize = sizeof(uint64_t) +
			                         sizeof(uint32_t) +
			                         sizeof(int16_t);

			this->buffer_ = std::unique_ptr<BinaryMapping::Buffer>(
				new BinaryMapping::Buffer(tupleSize)
			);
		}

		std::unique_ptr<BinaryMapping::Buffer> buffer_;

};

TEST_F(EndianTest, LittleEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		uint64_t,
		uint32_t,
		int16_t,
		BinaryMapping::Raw<3>
	> TestMapping;

	TestMapping mapping(this->buffer_.get());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);
	mapping.set<3>(BinaryMapping::Raw<3>({1, 2, 3}));

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::Raw<3>({1, 2, 3}));
}

TEST_F(EndianTest, BigEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		uint64_t,
		uint32_t,
		int16_t,
		BinaryMapping::Raw<3>
	> TestMapping;

	TestMapping mapping(this->buffer_.get());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);
	mapping.set<3>(BinaryMapping::Raw<3>({1, 2, 3}));

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::Raw<3>({1, 2, 3}));
}

TEST_F(EndianTest, UndefinedEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::UndefinedEndian,
		uint64_t,
		uint32_t,
		int16_t,
		BinaryMapping::Raw<3>
	> TestMapping;

	TestMapping mapping(this->buffer_.get());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);
	mapping.set<3>(BinaryMapping::Raw<3>({1, 2, 3}));

	mapping.serialize<BinaryMapping::BigEndian>();

	EXPECT_NE(mapping.get<0>(), UINT32_MAX);
	EXPECT_NE(mapping.get<1>(), UINT16_MAX);
	EXPECT_NE(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::Raw<3>({1, 2, 3}));

	mapping.deserialize<BinaryMapping::BigEndian>();

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
	EXPECT_EQ(mapping.get<3>(), BinaryMapping::Raw<3>({1, 2, 3}));
}

TEST_F(EndianTest, MixedEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		uint64_t,
		uint32_t,
		int16_t
	> BigTestMapping;

	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		uint64_t,
		uint32_t,
		int16_t
	> LittleTestMapping;

	BigTestMapping bigMapping(this->buffer_.get());

	bigMapping.set<0>(UINT32_MAX);
	bigMapping.set<1>(UINT16_MAX);
	bigMapping.set<2>(INT8_MIN);

	LittleTestMapping littleMapping(this->buffer_.get());

	EXPECT_EQ(littleMapping.get<0>(), 18446744069414584320ul);
	EXPECT_EQ(littleMapping.get<1>(), 4294901760);
	EXPECT_EQ(littleMapping.get<2>(), -32513);
}