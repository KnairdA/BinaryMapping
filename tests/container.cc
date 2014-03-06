#include "gtest/gtest.h"

#include <memory>

#include "container.h"
#include "type/tuple.h"

class ContainerTest : public ::testing::Test {
	protected:
		typedef BinaryMapping::Container<
			BinaryMapping::PlainTuple<
				uint64_t,
				uint16_t
			>
		> TestContainer;

		virtual void SetUp() {
			this->container_ = std::unique_ptr<TestContainer>(
				new TestContainer(10)
			);

			for ( size_t i = 0; i != 10; ++i ) {
				(*this->container_)[i] = TestContainer::element_type::value_type(i, i);
			}
		}

		std::unique_ptr<TestContainer> container_;

};

TEST_F(ContainerTest, Basic) {
	EXPECT_EQ(this->container_->front().get<0>(), 0);
	EXPECT_EQ(this->container_->back().get<1>(),  9);
	EXPECT_EQ(this->container_->size(),          10);

	for ( size_t i = 0; i != 10; ++i ) {
		EXPECT_EQ(this->container_->at(i).get<0>(), i);
		EXPECT_EQ((*this->container_)[i].get<1>(),  i);
	}

	EXPECT_THROW(this->container_->at(10), std::out_of_range);
	EXPECT_NO_THROW((*(this->container_.get()))[10]);
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
	EXPECT_EQ((*iter1).get<0>(), 1);
	EXPECT_EQ(iter2 - iter1,     9);
	iter1 += 3;
	EXPECT_EQ((*iter1).get<0>(), 4);
	EXPECT_EQ(iter2 - iter1,     6);
	--iter1;
	EXPECT_EQ((*iter1).get<0>(), 3);
	EXPECT_EQ(iter2 - iter1,     7);
	iter1 -= 3;
	EXPECT_EQ((*iter1).get<0>(), 0);
	EXPECT_EQ(iter2 - iter1,    10);
	EXPECT_EQ(iter2-- - iter1,  10);
	EXPECT_EQ(iter2++ - iter1,   9);
	EXPECT_EQ(iter2-- - iter1,  10);

	auto iter3 = iter2 - 5;
	auto iter4 = iter3 + 2;
	auto iter5 = 2 + iter3;

	EXPECT_EQ(iter2 - iter3, 5);
	EXPECT_EQ(iter2 - iter4, 3);
	EXPECT_EQ(iter2 - iter5, 3);
}

TEST_F(ContainerTest, Dereference) {
	for ( TestContainer::iterator_type iter(this->container_->begin());
	      iter != this->container_->end();
	      ++iter ) {
		TestContainer::iterator_type::element_type::value_type values(*iter);

		EXPECT_EQ(std::get<0>(values), iter - this->container_->begin());
		EXPECT_EQ(std::get<1>(values), iter - this->container_->begin());

		TestContainer::iterator_type::element_type& tuple(*iter);

		EXPECT_EQ(tuple.get<0>(), iter - this->container_->begin());
		EXPECT_EQ(tuple.get<1>(), iter - this->container_->begin());
	}
}

TEST_F(ContainerTest, ConstContainer) {
	const TestContainer* constContainer = this->container_.get();

	EXPECT_EQ(constContainer->front(), TestContainer::element_value_type(0, 0));
	EXPECT_EQ(constContainer->back(),  TestContainer::element_value_type(9, 9));

	for ( TestContainer::const_iterator_type iter(constContainer->begin());
	      iter != constContainer->end();
	      ++iter ) {
		EXPECT_EQ((*iter).get<0>(), iter - constContainer->begin());
		EXPECT_EQ((*iter).get<1>(), iter - constContainer->begin());

		EXPECT_EQ(
			*static_cast<const TestContainer::const_iterator_type>(iter),
			TestContainer::element_type::value_type(
				iter - constContainer->begin(),
				iter - constContainer->begin()
			)
		);
	}
}
