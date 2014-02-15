#include "gtest/gtest.h"

#include "bitmap.h"

class BitmapTest : public ::testing::Test {
	protected:
		BinaryMapping::BitMap<10> bit_map_{42, 128};

};

TEST_F(BitmapTest, ByteRounding) {
	EXPECT_EQ(BinaryMapping::dtl::round_to_byte<6>::value,  1);
	EXPECT_EQ(BinaryMapping::dtl::round_to_byte<10>::value, 2);
	EXPECT_EQ(BinaryMapping::dtl::round_to_byte<19>::value, 3);

	EXPECT_EQ(static_cast<size_t>(BinaryMapping::BitMap<10>::size),      2);
	EXPECT_EQ(static_cast<size_t>(BinaryMapping::BitMap<10>::bit_size), 10);
}

TEST_F(BitmapTest, Get) {
	EXPECT_FALSE(this->bit_map_[0]);
	EXPECT_FALSE(this->bit_map_[1]);
	EXPECT_TRUE( this->bit_map_[2]);
	EXPECT_FALSE(this->bit_map_[3]);
	EXPECT_TRUE( this->bit_map_[4]);
	EXPECT_FALSE(this->bit_map_[5]);
	EXPECT_TRUE( this->bit_map_[6]);
	EXPECT_FALSE(this->bit_map_[7]);
	EXPECT_TRUE( this->bit_map_[8]);
	EXPECT_FALSE(this->bit_map_[9]);

	EXPECT_FALSE(this->bit_map_.get(0));
	EXPECT_FALSE(this->bit_map_.get(1));
	EXPECT_TRUE( this->bit_map_.get(2));
	EXPECT_FALSE(this->bit_map_.get(3));
	EXPECT_TRUE( this->bit_map_.get(4));
	EXPECT_FALSE(this->bit_map_.get(5));
	EXPECT_TRUE( this->bit_map_.get(6));
	EXPECT_FALSE(this->bit_map_.get(7));
	EXPECT_TRUE( this->bit_map_.get(8));
	EXPECT_FALSE(this->bit_map_.get(9));

	EXPECT_THROW(this->bit_map_.get(10), std::out_of_range);
}

TEST_F(BitmapTest, Set) {
	this->bit_map_.set(0);
	this->bit_map_.set(1);
	this->bit_map_.set(3);
	this->bit_map_.set(5);
	this->bit_map_.set(7);
	this->bit_map_.set(9);

	EXPECT_TRUE(this->bit_map_.get(0));
	EXPECT_TRUE(this->bit_map_.get(1));
	EXPECT_TRUE(this->bit_map_.get(2));
	EXPECT_TRUE(this->bit_map_.get(3));
	EXPECT_TRUE(this->bit_map_.get(4));
	EXPECT_TRUE(this->bit_map_.get(5));
	EXPECT_TRUE(this->bit_map_.get(6));
	EXPECT_TRUE(this->bit_map_.get(7));
	EXPECT_TRUE(this->bit_map_.get(8));
	EXPECT_TRUE(this->bit_map_.get(9));

	EXPECT_THROW(this->bit_map_.set(10), std::out_of_range);
}

TEST_F(BitmapTest, Reset) {
	this->bit_map_.reset(2);
	this->bit_map_.reset(4);
	this->bit_map_.reset(6);
	this->bit_map_.reset(8);

	EXPECT_FALSE(this->bit_map_.get(0));
	EXPECT_FALSE(this->bit_map_.get(1));
	EXPECT_FALSE(this->bit_map_.get(2));
	EXPECT_FALSE(this->bit_map_.get(3));
	EXPECT_FALSE(this->bit_map_.get(4));
	EXPECT_FALSE(this->bit_map_.get(5));
	EXPECT_FALSE(this->bit_map_.get(6));
	EXPECT_FALSE(this->bit_map_.get(7));
	EXPECT_FALSE(this->bit_map_.get(8));
	EXPECT_FALSE(this->bit_map_.get(9));

	EXPECT_THROW(this->bit_map_.reset(10), std::out_of_range);
}

TEST_F(BitmapTest, Toggle) {
	this->bit_map_.toggle(0);
	this->bit_map_.toggle(1);
	this->bit_map_.toggle(2);
	this->bit_map_.toggle(3);
	this->bit_map_.toggle(4);
	this->bit_map_.toggle(5);
	this->bit_map_.toggle(6);
	this->bit_map_.toggle(7);
	this->bit_map_.toggle(8);
	this->bit_map_.toggle(9);

	EXPECT_TRUE( this->bit_map_.get(0));
	EXPECT_TRUE( this->bit_map_.get(1));
	EXPECT_FALSE(this->bit_map_.get(2));
	EXPECT_TRUE( this->bit_map_.get(3));
	EXPECT_FALSE(this->bit_map_.get(4));
	EXPECT_TRUE( this->bit_map_.get(5));
	EXPECT_FALSE(this->bit_map_.get(6));
	EXPECT_TRUE( this->bit_map_.get(7));
	EXPECT_FALSE(this->bit_map_.get(8));
	EXPECT_TRUE( this->bit_map_.get(9));

	EXPECT_THROW(this->bit_map_.toggle(10), std::out_of_range);
}
