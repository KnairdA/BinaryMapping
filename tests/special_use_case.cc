#include "gtest/gtest.h"

#include "container.h"
#include "type/tuple.h"

class SpecialUseCaseTest : public ::testing::Test { };

TEST_F(SpecialUseCaseTest, ContainerNesting) {
	BinaryMapping::Container<
		BinaryMapping::PlainTuple<
			uint32_t,
			BinaryMapping::ByteField<16>
		>
	> container(10);

	for ( auto level1(container.begin());
	      level1 != container.end();
	      ++level1 ) {
		(*level1).set<0>(level1 - container.begin());

		BinaryMapping::Container<
			BinaryMapping::PlainTuple<
				uint16_t,
				int16_t
			>
		> nestedContainer((*level1).ptr<1>());

		for ( auto level2(nestedContainer.begin());
		      level2 != nestedContainer.end();
		      ++level2 ) {
			(*level2).set<0>(level2 - nestedContainer.begin());
			(*level2).set<1>(level2 - nestedContainer.begin());
		}
	}

	for ( auto level1(container.begin());
	      level1 != container.end();
	      ++level1 ) {
		EXPECT_EQ((*level1).get<0>(), level1 - container.begin());

		BinaryMapping::Container<
			BinaryMapping::PlainTuple<
				uint16_t,
				int16_t
			>
		> nestedContainer((*level1).ptr<1>());

		for ( auto level2(nestedContainer.begin());
		      level2 != nestedContainer.end();
		      ++level2 ) {
			EXPECT_EQ((*level2).get<0>(), level2 - nestedContainer.begin());
			EXPECT_EQ((*level2).get<1>(), level2 - nestedContainer.begin());
		}
	}
}

