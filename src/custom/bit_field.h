#ifndef BINARY_MAPPING_SRC_BIT_FIELD_H_
#define BINARY_MAPPING_SRC_BIT_FIELD_H_

#include <algorithm>

#include "custom_serializable.h"

namespace BinaryMapping {

template <size_t Size>
struct BitField : public CustomSerializable<Size> {
	static const size_t size = Size * 8;

	using CustomSerializable<Size>::CustomSerializable;

	inline bool operator[](size_t index) const {
		return this->bytes[index / 8] & (
			1 << (7 - index % 8)
		);
	}

	inline bool test(size_t index) const {
		return this->bytes.at(index / 8) & (
			1 << (7 - index % 8)
		);
	}

	inline void set(size_t index) {
		this->bytes.at(index / 8) |= (
			1 << (7 - index % 8)
		);
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
		std::for_each(
			this->bytes.begin(),
			this->bytes.end(),
			[](uint8_t& tmp) {
				tmp = UINT8_MAX;
			}
		);
	}

	inline void reset() {
		std::for_each(
			this->bytes.begin(),
			this->bytes.end(),
			[](uint8_t& tmp) {
				tmp = 0;
			}
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
};

}

#endif  // BINARY_MAPPING_SRC_BIT_FIELD_H_
