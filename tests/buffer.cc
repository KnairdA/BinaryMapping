#include "gtest/gtest.h"

#include <memory>
#include <cstdint>

#include "detail/io/buffer.h"

class BufferTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
			this->buffer_ = std::unique_ptr<BinaryMapping::dtl::Buffer>(
				new BinaryMapping::dtl::Buffer(10 * sizeof(std::uint32_t))
			);
		}

		std::unique_ptr<BinaryMapping::dtl::Buffer> buffer_;

};

TEST_F(BufferTest, Basic) {
	EXPECT_EQ(this->buffer_->size<sizeof(std::uint32_t)>(), 10);
	EXPECT_EQ(this->buffer_->size(),                        40);

	EXPECT_EQ(this->buffer_->at<sizeof(std::uint32_t)>(0), this->buffer_->front());
	EXPECT_EQ(this->buffer_->at(0),                        this->buffer_->front());
	EXPECT_EQ(this->buffer_->at<sizeof(std::uint32_t)>(1), this->buffer_->front() + sizeof(std::uint32_t));
	EXPECT_EQ(this->buffer_->at(4),                        this->buffer_->front() + sizeof(std::uint32_t));

	EXPECT_EQ((*this->buffer_)[4], this->buffer_->front() + sizeof(std::uint32_t));

	EXPECT_THROW(this->buffer_->at<sizeof(std::uint32_t)>(10), std::out_of_range);
	EXPECT_THROW(this->buffer_->at(40),                        std::out_of_range);
	EXPECT_NO_THROW((*this->buffer_)[40]);
}

TEST_F(BufferTest, Iterator) {
	auto iter1 = this->buffer_->begin<sizeof(std::uint32_t)>();
	auto iter2 = this->buffer_->end<sizeof(std::uint32_t)>();

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
