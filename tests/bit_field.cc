#include "gtest/gtest.h"

#include "custom/bit_field.h"

class BitFieldTest : public ::testing::Test {
	protected:
		BinaryMapping::BitField<2> bit_field_{42, 170};

};

TEST_F(BitFieldTest, Test) {
	EXPECT_FALSE(this->bit_field_[0]);
	EXPECT_FALSE(this->bit_field_.test(0));
	EXPECT_FALSE(this->bit_field_[1]);
	EXPECT_FALSE(this->bit_field_.test(1));

	for ( size_t i = 3; i < 16; ++i ) {
		if ( i % 2 == 0 ) {
			EXPECT_TRUE( this->bit_field_[i]);
		} else {
			EXPECT_FALSE(this->bit_field_[i]);
		}
	}

	EXPECT_THROW(this->bit_field_.test(16), std::out_of_range);
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
		EXPECT_TRUE(this->bit_field_.test(i));
		this->bit_field_.reset(i);
	}

	this->bit_field_.set();

	for ( size_t i = 0; i < 16; ++i ) {
		EXPECT_TRUE(this->bit_field_.test(i));
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
		EXPECT_FALSE(this->bit_field_.test(i));
		this->bit_field_.set(i);
	}

	this->bit_field_.reset();

	for ( size_t i = 0; i < 16; ++i ) {
		EXPECT_FALSE(this->bit_field_.test(i));
	}

	EXPECT_THROW(this->bit_field_.reset(16), std::out_of_range);
}

TEST_F(BitFieldTest, Flip) {
	for ( size_t i = 0; i < 16; ++i ) {
		this->bit_field_.flip(i);
	}

	EXPECT_TRUE(this->bit_field_[0]);
	EXPECT_TRUE(this->bit_field_.test(0));
	EXPECT_TRUE(this->bit_field_[1]);
	EXPECT_TRUE(this->bit_field_.test(1));

	for ( size_t i = 3; i < 16; ++i ) {
		if ( i % 2 == 0 ) {
			EXPECT_FALSE(this->bit_field_[i]);
		} else {
			EXPECT_TRUE( this->bit_field_[i]);
		}
	}

	this->bit_field_.flip();

	EXPECT_FALSE(this->bit_field_.test(0));
	EXPECT_FALSE(this->bit_field_.test(1));

	for ( size_t i = 3; i < 16; ++i ) {
		if ( i % 2 == 0 ) {
			EXPECT_TRUE( this->bit_field_[i]);
		} else {
			EXPECT_FALSE(this->bit_field_[i]);
		}
	}

	EXPECT_THROW(this->bit_field_.flip(16), std::out_of_range);
}

TEST_F(BitFieldTest, Reference) {
	this->bit_field_[1].flip();

	EXPECT_TRUE(this->bit_field_.test(1));
	EXPECT_FALSE(~this->bit_field_[1]);

	this->bit_field_[2] = false;

	EXPECT_FALSE(this->bit_field_.test(2));
}
