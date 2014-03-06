#include "gtest/gtest.h"

#include <memory>

#include "type/tuple.h"
#include "type/custom_serializable.h"
#include "detail/io/buffer.h"

class TupleTest : public ::testing::Test {
	protected:
		typedef BinaryMapping::PlainTuple<
			uint64_t,
			uint8_t,
			uint32_t,
			uint16_t,
			int64_t,
			int32_t,
			int16_t,
			int8_t,
			BinaryMapping::ByteField<3>
		>::type<uint8_t> TestTuple;

		virtual void SetUp() {
			this->buffer_ = std::unique_ptr<BinaryMapping::dtl::Buffer>(
				new BinaryMapping::dtl::Buffer(TestTuple::size)
			);

			this->tuple_  = std::unique_ptr<TestTuple>(
				new TestTuple(this->buffer_->front())
			);

			this->tuple_->set<0>(UINT64_MAX);
			this->tuple_->set<1>(UINT8_MAX);
			this->tuple_->set<2>(UINT32_MAX);
			this->tuple_->set<3>(UINT16_MAX);
			this->tuple_->set<4>(INT64_MIN);
			this->tuple_->set<5>(INT32_MIN);
			this->tuple_->set<6>(INT16_MIN);
			this->tuple_->set<7>(INT8_MIN);
			this->tuple_->set<8>({1, 2, 3});
		}

		std::unique_ptr<BinaryMapping::dtl::Buffer> buffer_;
		std::unique_ptr<TestTuple> tuple_;

};

TEST_F(TupleTest, Basic) {
	EXPECT_EQ(this->tuple_->get<0>(), UINT64_MAX);
	EXPECT_EQ(this->tuple_->get<1>(), UINT8_MAX);
	EXPECT_EQ(this->tuple_->get<2>(), UINT32_MAX);
	EXPECT_EQ(this->tuple_->get<3>(), UINT16_MAX);
	EXPECT_EQ(this->tuple_->get<4>(), INT64_MIN);
	EXPECT_EQ(this->tuple_->get<5>(), INT32_MIN);
	EXPECT_EQ(this->tuple_->get<6>(), INT16_MIN);
	EXPECT_EQ(this->tuple_->get<7>(), INT8_MIN);
	EXPECT_EQ(this->tuple_->get<8>(), (BinaryMapping::ByteField<3>{1, 2, 3}));
}

TEST_F(TupleTest, Direct) {
	EXPECT_EQ(*this->tuple_->ptr<0>(), UINT64_MAX);
	EXPECT_EQ(*this->tuple_->ptr<1>(), UINT8_MAX);
	EXPECT_EQ(*this->tuple_->ptr<2>(), UINT32_MAX);
	EXPECT_EQ(*this->tuple_->ptr<3>(), UINT16_MAX);
	EXPECT_EQ(*this->tuple_->ptr<4>(), INT64_MIN);
	EXPECT_EQ(*this->tuple_->ptr<5>(), INT32_MIN);
	EXPECT_EQ(*this->tuple_->ptr<6>(), INT16_MIN);
	EXPECT_EQ(*this->tuple_->ptr<7>(), INT8_MIN);
	EXPECT_EQ(*this->tuple_->ptr<8>(), (BinaryMapping::ByteField<3>{1, 2, 3}));
}

TEST_F(TupleTest, Dereference) {
	TestTuple::value_type tuple = *this->tuple_;

	this->tuple_->set<0>(0);
	this->tuple_->set<1>(0);
	this->tuple_->set<2>(0);
	this->tuple_->set<3>(0);
	this->tuple_->set<4>(0);
	this->tuple_->set<5>(0);
	this->tuple_->set<6>(0);
	this->tuple_->set<7>(0);
	this->tuple_->set<8>({3, 2, 1});

	EXPECT_EQ(std::get<0>(tuple), UINT64_MAX);
	EXPECT_EQ(std::get<1>(tuple), UINT8_MAX);
	EXPECT_EQ(std::get<2>(tuple), UINT32_MAX);
	EXPECT_EQ(std::get<3>(tuple), UINT16_MAX);
	EXPECT_EQ(std::get<4>(tuple), INT64_MIN);
	EXPECT_EQ(std::get<5>(tuple), INT32_MIN);
	EXPECT_EQ(std::get<6>(tuple), INT16_MIN);
	EXPECT_EQ(std::get<7>(tuple), INT8_MIN);
	EXPECT_EQ(std::get<8>(tuple), (BinaryMapping::ByteField<3>{1, 2, 3}));
}

TEST_F(TupleTest, Populate) {
	*this->tuple_ = TestTuple::value_type(
		1, 2, 3, 4, 5, 6, 7, 8, {3, 2, 1}
	);

	EXPECT_EQ(this->tuple_->get<0>(), 1);
	EXPECT_EQ(this->tuple_->get<1>(), 2);
	EXPECT_EQ(this->tuple_->get<2>(), 3);
	EXPECT_EQ(this->tuple_->get<3>(), 4);
	EXPECT_EQ(this->tuple_->get<4>(), 5);
	EXPECT_EQ(this->tuple_->get<5>(), 6);
	EXPECT_EQ(this->tuple_->get<6>(), 7);
	EXPECT_EQ(this->tuple_->get<7>(), 8);
	EXPECT_EQ(this->tuple_->get<8>(), (BinaryMapping::ByteField<3>{3, 2, 1}));
}
