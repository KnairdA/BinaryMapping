#include "gtest/gtest.h"

#include <memory>

#include "tuple/tuple.h"
#include "endianess/little.h"
#include "endianess/big.h"
#include "container.h"

class BufferTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
			this->buffer_ = std::unique_ptr<BinaryMapping::Buffer>(
				new BinaryMapping::Buffer(10 * sizeof(uint32_t))
			);
		}

		std::unique_ptr<BinaryMapping::Buffer> buffer_;

};

TEST_F(BufferTest, Basic) {
	EXPECT_EQ(this->buffer_->size<sizeof(uint32_t)>(), 10);

	EXPECT_EQ(this->buffer_->at<sizeof(uint32_t)>(0), this->buffer_->front());
	EXPECT_EQ(this->buffer_->at<sizeof(uint32_t)>(1), this->buffer_->front() + sizeof(uint32_t));

	EXPECT_EQ((*this->buffer_)[4], this->buffer_->front() + sizeof(uint32_t));
}

TEST_F(BufferTest, Iterator) {
	auto iter1 = this->buffer_->begin<sizeof(uint32_t)>();
	auto iter2 = this->buffer_->end<sizeof(uint32_t)>();

	EXPECT_EQ(iter2 - iter1, 10);
	EXPECT_EQ(iter2 > iter1, true);
	EXPECT_EQ(iter2 < iter1, false);
	++iter1;
	EXPECT_EQ(iter2 - iter1, 9);
	iter1 += 3;
	EXPECT_EQ(iter2 - iter1, 6);
	--iter1;
	EXPECT_EQ(iter2 - iter1, 7);
	iter1 -= 3;
	EXPECT_EQ(iter2 - iter1, 10);
	EXPECT_EQ(iter2-- - iter1, 10);
	EXPECT_EQ(iter2++ - iter1, 9);
	EXPECT_EQ(iter2-- - iter1, 10);

	auto iter3 = iter2 - 5;
	auto iter4 = iter3 + 2;
	auto iter5 = 2 + iter3;

	EXPECT_EQ(iter2 - iter3, 5);
	EXPECT_EQ(iter2 - iter4, 3);
	EXPECT_EQ(iter2 - iter5, 3);
}

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
		int8_t
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

	EXPECT_EQ(mapping.get<0>(), UINT64_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT8_MAX);
	EXPECT_EQ(mapping.get<2>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<3>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<4>(), INT64_MIN);
	EXPECT_EQ(mapping.get<5>(), INT32_MIN);
	EXPECT_EQ(mapping.get<6>(), INT16_MIN);
	EXPECT_EQ(mapping.get<7>(), INT8_MIN);
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

		++iter;
	}
}

TEST_F(TupleTest, CarbonCopy) {
	typedef BinaryMapping::PlainTuple<
		uint32_t,
		uint16_t
	> TestMapping;

	BinaryMapping::Buffer testBuffer(TestMapping::size);

	TestMapping mapping(&testBuffer);

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);

	TestMapping::carbon_copy copy = mapping.carbonCopy();

	mapping.set<0>(1);
	mapping.set<1>(2);

	EXPECT_EQ(copy.get<0>(), UINT32_MAX);
	EXPECT_EQ(copy.get<1>(), UINT16_MAX);
}


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
		int16_t
	> TestMapping;

	TestMapping mapping(this->buffer_.get());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
}

TEST_F(EndianTest, BigEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::BigEndian,
		uint64_t,
		uint32_t,
		int16_t
	> TestMapping;

	TestMapping mapping(this->buffer_.get());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
}

TEST_F(EndianTest, UndefinedEndian) {
	typedef BinaryMapping::Tuple<
		BinaryMapping::UndefinedEndian,
		uint64_t,
		uint32_t,
		int16_t
	> TestMapping;

	TestMapping mapping(this->buffer_.get());

	mapping.set<0>(UINT32_MAX);
	mapping.set<1>(UINT16_MAX);
	mapping.set<2>(INT8_MIN);

	mapping.serialize<BinaryMapping::BigEndian>();

	EXPECT_NE(mapping.get<0>(), UINT32_MAX);
	EXPECT_NE(mapping.get<1>(), UINT16_MAX);
	EXPECT_NE(mapping.get<2>(), INT8_MIN);

	mapping.deserialize<BinaryMapping::BigEndian>();

	EXPECT_EQ(mapping.get<0>(), UINT32_MAX);
	EXPECT_EQ(mapping.get<1>(), UINT16_MAX);
	EXPECT_EQ(mapping.get<2>(), INT8_MIN);
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

class ContainerTest : public ::testing::Test {
	protected:
		typedef BinaryMapping::PlainContainer<
			uint64_t,
			uint16_t
		> TestContainer;

		virtual void SetUp() {
			this->buffer_ = std::unique_ptr<BinaryMapping::Buffer>(
				new BinaryMapping::Buffer(10 * TestContainer::tuple_type::size)
			);

			this->container_ = std::unique_ptr<TestContainer>(
				new TestContainer(this->buffer_.get())
			);

			for ( size_t i = 0; i != 10; ++i ) {
				TestContainer::tuple_type tuple(this->container_->at(i));

				tuple.set<0>(i);
				tuple.set<1>(i);
			}
		}

		std::unique_ptr<BinaryMapping::Buffer> buffer_;
		std::unique_ptr<TestContainer> container_;

};

TEST_F(ContainerTest, Basic) {
	const TestContainer& constContainer = *this->container_.get();

	EXPECT_EQ(this->container_->front().get<0>(), 0);
	EXPECT_EQ(this->container_->back().get<1>(),  9);
	EXPECT_EQ(this->container_->size(),          10);

	for ( size_t i = 0; i != 10; ++i ) {
		EXPECT_EQ(this->container_->at(i).get<0>(), i);
		EXPECT_EQ((*this->container_)[i].get<1>(),  i);

		EXPECT_EQ(constContainer.at(i).get<0>(),    i);
		EXPECT_EQ(constContainer[i].get<1>(),       i);
	}
}

TEST_F(ContainerTest, Iterator) {
	TestContainer::iterator_type iter(this->container_->begin());

	for ( size_t i = 0; i < 10; ++i ) {
		EXPECT_EQ((*iter).get<0>(), i);
		EXPECT_EQ((*iter).get<1>(), i);

		++iter;
	}

	auto iter1 = this->container_->begin();
	auto iter2 = this->container_->end();

	EXPECT_EQ(iter2 - iter1, 10);
	EXPECT_EQ(iter2 > iter1, true);
	EXPECT_EQ(iter2 < iter1, false);
	++iter1;
	EXPECT_EQ(iter2 - iter1, 9);
	iter1 += 3;
	EXPECT_EQ(iter2 - iter1, 6);
	--iter1;
	EXPECT_EQ(iter2 - iter1, 7);
	iter1 -= 3;
	EXPECT_EQ(iter2 - iter1, 10);
	EXPECT_EQ(iter2-- - iter1, 10);
	EXPECT_EQ(iter2++ - iter1, 9);
	EXPECT_EQ(iter2-- - iter1, 10);

	auto iter3 = iter2 - 5;
	auto iter4 = iter3 + 2;
	auto iter5 = 2 + iter3;

	EXPECT_EQ(iter2 - iter3, 5);
	EXPECT_EQ(iter2 - iter4, 3);
	EXPECT_EQ(iter2 - iter5, 3);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
