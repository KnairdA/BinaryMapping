#ifndef BINARY_MAPPING_SRC_CUSTOM_BIT_FIELD_H_
#define BINARY_MAPPING_SRC_CUSTOM_BIT_FIELD_H_

#include <algorithm>
#include <functional>

#include "custom_serializable.h"

namespace BinaryMapping {

template <size_t Size>
struct BitField : public CustomSerializable<Size> {
	class reference;

	static const size_t size = Size * 8;

	using CustomSerializable<Size>::CustomSerializable;

	inline reference operator[](size_t index) {
		return reference(*this, index);
	}

	inline bool operator[](size_t index) const {
		return this->test(index);
	}

	inline bool test(size_t index) const {
		return this->bytes.at(index / 8) & (
			1 << (7 - index % 8)
		);
	}

	inline bool any() const {
		return std::any_of(
			this->bytes.begin(),
			this->bytes.end(),
			[](dtl::const_lvalue_reference<uint8_t> tmp) -> bool {
				return tmp != 0;
			}
		);
	}

	inline bool all() const {
		return std::all_of(
			this->bytes.begin(),
			this->bytes.end(),
			[](dtl::const_lvalue_reference<uint8_t> tmp) -> bool {
				return tmp == UINT8_MAX;
			}
		);
	}

	inline bool none() const {
		return !this->any();
	}

	inline size_t count() const {
		size_t count{};

		for ( uint8_t byte : this->bytes ) {
			for ( ; byte; ++count ) {
				byte &= byte - 1;
			}
		}

		return count;
	}

	inline void set(size_t index, bool value = true) {
		if ( value ) {
			this->bytes.at(index / 8) |= (
				1 << (7 - index % 8)
			);
		} else {
			this->reset(index);
		}
	}

	inline void reset(size_t index) {
		this->bytes.at(index / 8) &= (
			~(1 << (7 - index % 8))
		);
	}

	inline void flip(size_t index) {
		this->bytes.at(index / 8) ^= (
			1 << (7 - index % 8)
		);
	}

	inline void set() {
		std::fill(
			this->bytes.begin(),
			this->bytes.end(),
			UINT8_MAX
		);
	}

	inline void reset() {
		std::fill(
			this->bytes.begin(),
			this->bytes.end(),
			0
		);
	}

	inline void flip() {
		std::for_each(
			this->bytes.begin(),
			this->bytes.end(),
			[](uint8_t& tmp) {
				tmp = ~tmp;
			}
		);
	}

	inline void operator&=(dtl::const_lvalue_reference<BitField> rhs) {
		std::transform(
			this->bytes.begin(),
			this->bytes.end(),
			rhs.bytes.begin(),
			this->bytes.begin(),
			std::bit_and<uint8_t>()
		);
	}

	inline void operator|=(dtl::const_lvalue_reference<BitField> rhs) {
		std::transform(
			this->bytes.begin(),
			this->bytes.end(),
			rhs.bytes.begin(),
			this->bytes.begin(),
			std::bit_or<uint8_t>()
		);
	}

	inline void operator^=(dtl::const_lvalue_reference<BitField> rhs) {
		std::transform(
			this->bytes.begin(),
			this->bytes.end(),
			rhs.bytes.begin(),
			this->bytes.begin(),
			std::bit_xor<uint8_t>()
		);
	}
};

}

#include "bit_field_reference.h"

#endif  // BINARY_MAPPING_SRC_CUSTOM_BIT_FIELD_H_
