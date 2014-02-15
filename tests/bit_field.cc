#include "gtest/gtest.h"

#include "bit_field.h"

class BitFieldTest : public ::testing::Test {
	protected:
		BinaryMapping::BitField<2> bit_field_{42, 170};

};

TEST_F(BitFieldTest, Get) {
	EXPECT_FALSE(this->bit_field_[0]);
	EXPECT_FALSE(this->bit_field_.get(0));
	EXPECT_FALSE(this->bit_field_[1]);
	EXPECT_FALSE(this->bit_field_.get(1));

	for ( size_t i = 3; i < 16; ++i ) {
		if ( i % 2 == 0 ) {
			EXPECT_TRUE( this->bit_field_[i]);
		} else {
			EXPECT_FALSE(this->bit_field_[i]);
		}
	}

	EXPECT_THROW(this->bit_field_.get(16), std::out_of_range);
}

TEST_F(BitFieldTest, Set) {
	this->bit_field_.set(0);
	this->bit_field_.set(1);

	for ( size_t i = 3; i < 16; ++i ) {
		if ( i % 2 == 1 ) {
			this->bit_field_.set(i);
		}
	}

	for ( size_t i = 0; i < 16; ++i ) {
		EXPECT_TRUE(this->bit_field_.get(i));
	}

	EXPECT_THROW(this->bit_field_.set(16), std::out_of_range);
}

TEST_F(BitFieldTest, Reset) {
	for ( size_t i = 2; i < 16; ++i ) {
		if ( i % 2 == 0 ) {
			this->bit_field_.reset(i);
		}
	}

	for ( size_t i = 0; i < 16; ++i ) {
		EXPECT_FALSE(this->bit_field_.get(i));
	}

	EXPECT_THROW(this->bit_field_.reset(16), std::out_of_range);
}

TEST_F(BitFieldTest, Toggle) {
	for ( size_t i = 0; i < 16; ++i ) {
		this->bit_field_.toggle(i);
	}

	EXPECT_TRUE(this->bit_field_[0]);
	EXPECT_TRUE(this->bit_field_.get(0));
	EXPECT_TRUE(this->bit_field_[1]);
	EXPECT_TRUE(this->bit_field_.get(1));

	for ( size_t i = 3; i < 16; ++i ) {
		if ( i % 2 == 0 ) {
			EXPECT_FALSE( this->bit_field_[i]);
		} else {
			EXPECT_TRUE(this->bit_field_[i]);
		}
	}

	EXPECT_THROW(this->bit_field_.toggle(16), std::out_of_range);
}
