#include "gtest/gtest.h"

#include "bit_field.h"

class BitFieldTest : public ::testing::Test {
	protected:
		BinaryMapping::BitField<2> bit_field_{42, 170};

};

TEST_F(BitFieldTest, Get) {
	EXPECT_FALSE(this->bit_field_[0]);
	EXPECT_FALSE(this->bit_field_[1]);
	EXPECT_TRUE( this->bit_field_[2]);
	EXPECT_FALSE(this->bit_field_[3]);
	EXPECT_TRUE( this->bit_field_[4]);
	EXPECT_FALSE(this->bit_field_[5]);
	EXPECT_TRUE( this->bit_field_[6]);
	EXPECT_FALSE(this->bit_field_[7]);
	EXPECT_TRUE( this->bit_field_[8]);
	EXPECT_FALSE(this->bit_field_[9]);
	EXPECT_TRUE( this->bit_field_[10]);
	EXPECT_FALSE(this->bit_field_[11]);
	EXPECT_TRUE( this->bit_field_[12]);
	EXPECT_FALSE(this->bit_field_[13]);
	EXPECT_TRUE( this->bit_field_[14]);
	EXPECT_FALSE(this->bit_field_[15]);

	EXPECT_FALSE(this->bit_field_.get(0));
	EXPECT_FALSE(this->bit_field_.get(1));
	EXPECT_TRUE( this->bit_field_.get(2));
	EXPECT_FALSE(this->bit_field_.get(3));
	EXPECT_TRUE( this->bit_field_.get(4));
	EXPECT_FALSE(this->bit_field_.get(5));
	EXPECT_TRUE( this->bit_field_.get(6));
	EXPECT_FALSE(this->bit_field_.get(7));
	EXPECT_TRUE( this->bit_field_.get(8));
	EXPECT_FALSE(this->bit_field_.get(9));
	EXPECT_TRUE( this->bit_field_.get(10));
	EXPECT_FALSE(this->bit_field_.get(11));
	EXPECT_TRUE( this->bit_field_.get(12));
	EXPECT_FALSE(this->bit_field_.get(13));
	EXPECT_TRUE( this->bit_field_.get(14));
	EXPECT_FALSE(this->bit_field_.get(15));

	EXPECT_THROW(this->bit_field_.get(16), std::out_of_range);
}

TEST_F(BitFieldTest, Set) {
	this->bit_field_.set(0);
	this->bit_field_.set(1);
	this->bit_field_.set(3);
	this->bit_field_.set(5);
	this->bit_field_.set(7);
	this->bit_field_.set(9);
	this->bit_field_.set(11);
	this->bit_field_.set(13);
	this->bit_field_.set(15);

	EXPECT_TRUE(this->bit_field_.get(0));
	EXPECT_TRUE(this->bit_field_.get(1));
	EXPECT_TRUE(this->bit_field_.get(2));
	EXPECT_TRUE(this->bit_field_.get(3));
	EXPECT_TRUE(this->bit_field_.get(4));
	EXPECT_TRUE(this->bit_field_.get(5));
	EXPECT_TRUE(this->bit_field_.get(6));
	EXPECT_TRUE(this->bit_field_.get(7));
	EXPECT_TRUE(this->bit_field_.get(8));
	EXPECT_TRUE(this->bit_field_.get(9));
	EXPECT_TRUE(this->bit_field_.get(10));
	EXPECT_TRUE(this->bit_field_.get(11));
	EXPECT_TRUE(this->bit_field_.get(12));
	EXPECT_TRUE(this->bit_field_.get(13));
	EXPECT_TRUE(this->bit_field_.get(14));
	EXPECT_TRUE(this->bit_field_.get(15));

	EXPECT_THROW(this->bit_field_.set(16), std::out_of_range);
}

TEST_F(BitFieldTest, Reset) {
	this->bit_field_.reset(2);
	this->bit_field_.reset(4);
	this->bit_field_.reset(6);
	this->bit_field_.reset(8);
	this->bit_field_.reset(10);
	this->bit_field_.reset(12);
	this->bit_field_.reset(14);

	EXPECT_FALSE(this->bit_field_.get(0));
	EXPECT_FALSE(this->bit_field_.get(1));
	EXPECT_FALSE(this->bit_field_.get(2));
	EXPECT_FALSE(this->bit_field_.get(3));
	EXPECT_FALSE(this->bit_field_.get(4));
	EXPECT_FALSE(this->bit_field_.get(5));
	EXPECT_FALSE(this->bit_field_.get(6));
	EXPECT_FALSE(this->bit_field_.get(7));
	EXPECT_FALSE(this->bit_field_.get(8));
	EXPECT_FALSE(this->bit_field_.get(9));
	EXPECT_FALSE(this->bit_field_.get(10));
	EXPECT_FALSE(this->bit_field_.get(11));
	EXPECT_FALSE(this->bit_field_.get(12));
	EXPECT_FALSE(this->bit_field_.get(13));
	EXPECT_FALSE(this->bit_field_.get(14));
	EXPECT_FALSE(this->bit_field_.get(15));

	EXPECT_THROW(this->bit_field_.reset(16), std::out_of_range);
}

TEST_F(BitFieldTest, Toggle) {
	this->bit_field_.toggle(0);
	this->bit_field_.toggle(1);
	this->bit_field_.toggle(2);
	this->bit_field_.toggle(3);
	this->bit_field_.toggle(4);
	this->bit_field_.toggle(5);
	this->bit_field_.toggle(6);
	this->bit_field_.toggle(7);
	this->bit_field_.toggle(8);
	this->bit_field_.toggle(9);
	this->bit_field_.toggle(10);
	this->bit_field_.toggle(11);
	this->bit_field_.toggle(12);
	this->bit_field_.toggle(13);
	this->bit_field_.toggle(14);
	this->bit_field_.toggle(15);

	EXPECT_TRUE( this->bit_field_.get(0));
	EXPECT_TRUE( this->bit_field_.get(1));
	EXPECT_FALSE(this->bit_field_.get(2));
	EXPECT_TRUE( this->bit_field_.get(3));
	EXPECT_FALSE(this->bit_field_.get(4));
	EXPECT_TRUE( this->bit_field_.get(5));
	EXPECT_FALSE(this->bit_field_.get(6));
	EXPECT_TRUE( this->bit_field_.get(7));
	EXPECT_FALSE(this->bit_field_.get(8));
	EXPECT_TRUE( this->bit_field_.get(9));
	EXPECT_FALSE(this->bit_field_.get(10));
	EXPECT_TRUE( this->bit_field_.get(11));
	EXPECT_FALSE(this->bit_field_.get(12));
	EXPECT_TRUE( this->bit_field_.get(13));
	EXPECT_FALSE(this->bit_field_.get(14));
	EXPECT_TRUE( this->bit_field_.get(15));

	EXPECT_THROW(this->bit_field_.toggle(16), std::out_of_range);
}
