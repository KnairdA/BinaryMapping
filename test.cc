#include "gtest/gtest.h"

#include "tuple/tuple.h"
#include "endianess/little.h"
#include "endianess/big.h"
#include "container.h"

class BinaryMappingTest : public ::testing::Test {
	
};

TEST_F(BinaryMappingTest, BasicMapping) {
	typedef BinaryMapping::PlainTuple<
		uint64_t,
		uint8_t,
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::tuple_size, sizeof(uint8_t))
		),
		TestMapping::tuple_size
	);

	TestMapping mapping(testBuffer);

	mapping.set<0>(UINT64_MAX);
	mapping.set<1>(UINT8_MAX);
	mapping.set<2>(UINT32_MAX);
	mapping.set<3>(UINT16_MAX);

	EXPECT_EQ(mapping.get<0>(), UINT64_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT8_MAX);
	EXPECT_EQ(mapping.get<2>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<3>(), UINT16_MAX);
}

TEST_F(BinaryMappingTest, SlidingMapping) {
	typedef BinaryMapping::PlainTuple<
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::tuple_size * 10, sizeof(uint8_t))
		),
		TestMapping::tuple_size * 10
	);

	TestMapping mapping(testBuffer);

	for ( size_t i = 0; i < 10; ++i ) {
		mapping.set<0>(i);
		mapping.set<1>(i);

		++mapping;
	}

	mapping.move(0);

	for ( size_t i = 0; i < 10; ++i ) {
		EXPECT_EQ(mapping.get<0>(), i);
		EXPECT_EQ(mapping.get<1>(), i);

		++mapping;
	}
}

TEST_F(BinaryMappingTest, LittleEndianMapping) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		uint64_t,
		uint32_t
	> TestMapping;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::tuple_size, sizeof(uint8_t))
		),
		TestMapping::tuple_size
	);

	TestMapping mapping(testBuffer);

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
}

TEST_F(BinaryMappingTest, BigEndianMapping) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		uint64_t,
		uint32_t
	> TestMapping;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::tuple_size, sizeof(uint8_t))
		),
		TestMapping::tuple_size
	);

	TestMapping mapping(testBuffer);

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
}

TEST_F(BinaryMappingTest, MixedEndianMapping) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		uint64_t,
		uint32_t
	> BigTestMapping;

	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		uint64_t,
		uint32_t
	> LittleTestMapping;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(BigTestMapping::tuple_size, sizeof(uint8_t))
		),
		BigTestMapping::tuple_size
	);

	BigTestMapping bigMapping(testBuffer);

	bigMapping.set<0>(UINT32_MAX);
	bigMapping.set<1>(UINT16_MAX);

	LittleTestMapping littleMapping(testBuffer);

	EXPECT_EQ(littleMapping.get<0>(), 18446744069414584320ul);
	EXPECT_EQ(littleMapping.get<1>(), 4294901760);
}

TEST_F(BinaryMappingTest, CarbonCopyMapping) {
	typedef BinaryMapping::PlainTuple<
		uint64_t,
		uint8_t,
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::tuple_size, sizeof(uint8_t))
		),
		TestMapping::tuple_size
	);

	TestMapping mapping(testBuffer);

	mapping.set<0>(UINT64_MAX);
	mapping.set<1>(UINT8_MAX);
	mapping.set<2>(UINT32_MAX);
	mapping.set<3>(UINT16_MAX);

	TestMapping::CarbonCopy copy = mapping.carbonCopy();

	mapping.set<0>(1);
	mapping.set<1>(2);
	mapping.set<2>(3);
	mapping.set<3>(4);

	EXPECT_EQ(copy.get<0>(), UINT64_MAX);
	EXPECT_EQ(copy.get<1>(), UINT8_MAX);
	EXPECT_EQ(copy.get<2>(), UINT32_MAX);
	EXPECT_EQ(copy.get<3>(), UINT16_MAX);
}

TEST_F(BinaryMappingTest, BasicContainer) {
	typedef BinaryMapping::PlainContainer<
		uint64_t,
		uint16_t
	> TestContainer;

	BinaryMapping::BufferGuard testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestContainer::type::tuple_size * 10, sizeof(uint8_t))
		),
		TestContainer::type::tuple_size * 10
	);

	TestContainer container(testBuffer);

	EXPECT_EQ(container.size(), 10);

	TestContainer::type* tuple = container.data();

	for ( size_t i = 0; i < 10; ++i ) {
		tuple->set<0>(i);
		tuple->set<1>(i);

		++(*tuple);
	}

	for ( size_t i = 0; i < 10; ++i ) {
		EXPECT_EQ(container.at(i).get<0>(), i);
		EXPECT_EQ(container[i].get<1>(), i);
	}

	EXPECT_EQ(container.front().get<0>(), 0);
	EXPECT_EQ(container.back().get<1>(), 9);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
