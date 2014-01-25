#include "gtest/gtest.h"

#include "tuple/tuple.h"
#include "raw.h"

class TupleTest : public ::testing::Test { };

TEST_F(TupleTest, Basic) {
	typedef BinaryMapping::PlainTuple<
		uint64_t,
		uint8_t,
		uint32_t,
		uint16_t,
		int64_t,
		int32_t,
		int16_t,
		int8_t,
		BinaryMapping::Raw<3>
	> TestMapping;

	BinaryMapping::Buffer testBuffer(TestMapping::size);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(UINT64_MAX);
	mapping.set<1>(UINT8_MAX);
	mapping.set<2>(UINT32_MAX);
	mapping.set<3>(UINT16_MAX);
	mapping.set<4>(INT64_MIN);
	mapping.set<5>(INT32_MIN);
	mapping.set<6>(INT16_MIN);
	mapping.set<7>(INT8_MIN);
	mapping.set<8>(BinaryMapping::Raw<3>({1, 2, 3}));

	EXPECT_EQ(mapping.get<0>(), UINT64_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT8_MAX);
	EXPECT_EQ(mapping.get<2>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<3>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<4>(), INT64_MIN);
	EXPECT_EQ(mapping.get<5>(), INT32_MIN);
	EXPECT_EQ(mapping.get<6>(), INT16_MIN);
	EXPECT_EQ(mapping.get<7>(), INT8_MIN);
	EXPECT_EQ(mapping.get<8>(), BinaryMapping::Raw<3>({1, 2, 3}));
}

TEST_F(TupleTest, Iterator) {
	typedef BinaryMapping::PlainTuple<
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(TestMapping::size * 10);

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

		EXPECT_EQ(*mapping.ptr<0>(), i);
		EXPECT_EQ(*mapping.ptr<1>(), i);

		EXPECT_EQ(mapping.ptr(), *iter);
		EXPECT_EQ(mapping.get(), (std::tuple<uint32_t, uint16_t>(i, i)));

		++iter;
	}
}

TEST_F(TupleTest, Dereference) {
	typedef BinaryMapping::PlainTuple<
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(TestMapping::size);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(1);
	mapping.set<1>(2);

	EXPECT_TRUE((std::is_same<
		decltype(mapping.get()),
		std::tuple<uint32_t, uint16_t>
	>::value));

	auto tuple = mapping.get();

	mapping.set<0>(3);
	mapping.set<1>(4);

	EXPECT_EQ(std::get<0>(tuple), 1);
	EXPECT_EQ(std::get<1>(tuple), 2);
}
