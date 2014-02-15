#include "gtest/gtest.h"

#include "bitmap.h"

class BitmapTest : public ::testing::Test { };

TEST_F(BitmapTest, ByteRounding) {
	EXPECT_EQ(BinaryMapping::dtl::round_to_byte<6>::value,  1);
	EXPECT_EQ(BinaryMapping::dtl::round_to_byte<10>::value, 2);
	EXPECT_EQ(BinaryMapping::dtl::round_to_byte<19>::value, 3);
}

TEST_F(BitmapTest, Check) {
	BinaryMapping::BitMap<10> test{42, 128};

	EXPECT_FALSE(test[0]);
	EXPECT_FALSE(test[1]);
	EXPECT_TRUE( test[2]);
	EXPECT_FALSE(test[3]);
	EXPECT_TRUE( test[4]);
	EXPECT_FALSE(test[5]);
	EXPECT_TRUE( test[6]);
	EXPECT_FALSE(test[7]);
	EXPECT_TRUE( test[8]);
	EXPECT_FALSE(test[9]);

	EXPECT_FALSE(test.at(0));
	EXPECT_FALSE(test.at(1));
	EXPECT_TRUE( test.at(2));
	EXPECT_FALSE(test.at(3));
	EXPECT_TRUE( test.at(4));
	EXPECT_FALSE(test.at(5));
	EXPECT_TRUE( test.at(6));
	EXPECT_FALSE(test.at(7));
	EXPECT_TRUE( test.at(8));
	EXPECT_FALSE(test.at(9));
}
