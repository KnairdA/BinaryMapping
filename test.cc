#include "gtest/gtest.h"

#include "tuple/tuple.h"
#include "endianess/little.h"
#include "endianess/big.h"
#include "container.h"

class BinaryMappingTest : public ::testing::Test {
	
};

TEST_F(BinaryMappingTest, Buffer) {
	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(10 * sizeof(uint32_t), sizeof(uint8_t))
		),
		10 * sizeof(uint32_t)
	);

	EXPECT_EQ(testBuffer.size<sizeof(uint32_t)>(), 10);
	EXPECT_EQ(testBuffer.at<sizeof(uint32_t)>(0), testBuffer.front());
	EXPECT_EQ(testBuffer.at<sizeof(uint32_t)>(1),
	          testBuffer.front() + sizeof(uint32_t));
	EXPECT_EQ(testBuffer[4],
	          testBuffer.front() + sizeof(uint32_t));
}

TEST_F(BinaryMappingTest, BufferIterator) {
	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(10 * sizeof(uint32_t), sizeof(uint8_t))
		),
		10 * sizeof(uint32_t)
	);

	auto iter1 = testBuffer.begin<sizeof(uint32_t)>();
	auto iter2 = testBuffer.end<sizeof(uint32_t)>();

	EXPECT_EQ(iter2 - iter1, 10);
	++iter1;
	EXPECT_EQ(iter2 - iter1, 9);
	iter1 += 3;
	EXPECT_EQ(iter2 - iter1, 6);
	--iter1;
	EXPECT_EQ(iter2 - iter1, 7);
	iter1 -= 3;
	EXPECT_EQ(iter2 - iter1, 10);

	auto iter3 = iter2 - 5;
	auto iter4 = iter3 + 2;
	auto iter5 = 2 + iter3;

	EXPECT_EQ(iter2 - iter3, 5);
	EXPECT_EQ(iter2 - iter4, 3);
	EXPECT_EQ(iter2 - iter5, 3);
}

TEST_F(BinaryMappingTest, BasicMapping) {
	typedef BinaryMapping::PlainTuple<
		uint64_t,
		uint8_t,
		uint32_t,
		uint16_t,
		int64_t,
		int32_t,
		int16_t,
		int8_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::size, sizeof(uint8_t))
		),
		TestMapping::size
	);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(UINT64_MAX);
	mapping.set<1>(UINT8_MAX);
	mapping.set<2>(UINT32_MAX);
	mapping.set<3>(UINT16_MAX);
	mapping.set<4>(INT64_MIN);
	mapping.set<5>(INT32_MIN);
	mapping.set<6>(INT16_MIN);
	mapping.set<7>(INT8_MIN);

	EXPECT_EQ(mapping.get<0>(), UINT64_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT8_MAX);
	EXPECT_EQ(mapping.get<2>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<3>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<4>(), INT64_MIN);
	EXPECT_EQ(mapping.get<5>(), INT32_MIN);
	EXPECT_EQ(mapping.get<6>(), INT16_MIN);
	EXPECT_EQ(mapping.get<7>(), INT8_MIN);
}

TEST_F(BinaryMappingTest, SlidingMapping) {
	typedef BinaryMapping::PlainTuple<
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::size * 10, sizeof(uint8_t))
		),
		TestMapping::size * 10
	);

	auto iter = testBuffer.begin<TestMapping::size>();
	TestMapping mapping(iter);

	for ( size_t i = 0; i < 10; ++i ) {
		mapping.set<0>(i);
		mapping.set<1>(i);

		++iter;
	}

	iter -= 10;

	for ( size_t i = 0; i < 10; ++i ) {
		EXPECT_EQ(mapping.get<0>(), i);
		EXPECT_EQ(mapping.get<1>(), i);

		++iter;
	}
}

TEST_F(BinaryMappingTest, LittleEndianMapping) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		uint64_t,
		uint32_t,
		int16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::size, sizeof(uint8_t))
		),
		TestMapping::size
	);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
}

TEST_F(BinaryMappingTest, BigEndianMapping) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		uint64_t,
		uint32_t,
		int16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::size, sizeof(uint8_t))
		),
		TestMapping::size
	);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
}

TEST_F(BinaryMappingTest, MixedEndianMapping) {
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

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(BigTestMapping::size, sizeof(uint8_t))
		),
		BigTestMapping::size
	);

	BigTestMapping bigMapping(&testBuffer);

	bigMapping.set<0>(UINT32_MAX);
	bigMapping.set<1>(UINT16_MAX);
	bigMapping.set<2>(INT8_MIN);

	LittleTestMapping littleMapping(&testBuffer);

	EXPECT_EQ(littleMapping.get<0>(), 18446744069414584320ul);
	EXPECT_EQ(littleMapping.get<1>(), 4294901760);
	EXPECT_EQ(littleMapping.get<2>(), -32513);
}

TEST_F(BinaryMappingTest, CarbonCopyMapping) {
	typedef BinaryMapping::PlainTuple<
		uint64_t,
		uint8_t,
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestMapping::size, sizeof(uint8_t))
		),
		TestMapping::size
	);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(UINT64_MAX);
	mapping.set<1>(UINT8_MAX);
	mapping.set<2>(UINT32_MAX);
	mapping.set<3>(UINT16_MAX);

	TestMapping::carbon_copy copy = mapping.carbonCopy();

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

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestContainer::tuple_type::size * 10, sizeof(uint8_t))
		),
		TestContainer::tuple_type::size * 10
	);

	TestContainer container(&testBuffer);
	const TestContainer& constContainer = container;

	EXPECT_EQ(container.size(), 10);

	for ( size_t i = 0; i < 10; ++i ) {
		auto tuple = container.at(i);

		tuple.set<0>(i);
		tuple.set<1>(i);
	}

	for ( size_t i = 0; i < 10; ++i ) {
		EXPECT_EQ(container.at(i).get<0>(), i);
		EXPECT_EQ(container[i].get<1>(), i);

		EXPECT_EQ(constContainer.at(i).get<0>(), i);
		EXPECT_EQ(constContainer[i].get<1>(), i);
	}

	EXPECT_EQ(container.front().get<0>(), 0);
	EXPECT_EQ(container.back().get<1>(), 9);
}

TEST_F(BinaryMappingTest, BasicIterator) {
	typedef BinaryMapping::PlainContainer<
		uint64_t,
		uint16_t
	> TestContainer;

	BinaryMapping::Buffer testBuffer(
		reinterpret_cast<uint8_t*>(
			std::calloc(TestContainer::tuple_type::size * 10, sizeof(uint8_t))
		),
		TestContainer::tuple_type::size * 10
	);

	TestContainer container(&testBuffer);

	for ( size_t i = 0; i < 10; ++i ) {
		auto tuple = container.at(i);

		tuple.set<0>(i);
		tuple.set<1>(i);
	}

	TestContainer::iterator_type iter(container.begin());

	for ( size_t i = 0; i < 10; ++i ) {
		EXPECT_EQ((*iter).get<0>(), i);
		EXPECT_EQ((*iter).get<1>(), i);

		++iter;
	}
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
