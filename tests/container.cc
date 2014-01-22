#include "gtest/gtest.h"

#include <memory>

#include "container.h"

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
