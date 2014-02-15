#ifndef BINARY_MAPPING_SRC_BIT_FIELD_H_
#define BINARY_MAPPING_SRC_BIT_FIELD_H_

#include <array>

#include "detail/utility.h"

namespace BinaryMapping {

template <size_t Size>
struct BitField {
	static const size_t size     = Size;
	static const size_t bit_size = Size * 8;

	std::array<uint8_t, Size> data;

	BitField(BitField&&)                 = default;
	BitField(BitField&)                  = default;
	BitField(const BitField&)            = default;
	BitField& operator=(const BitField&) = default;

	template <typename... Bytes>
	BitField(Bytes&&... bytes):
		data{ std::forward<Bytes>(bytes)... } { }

	BitField(const std::initializer_list<uint8_t>&& bytes) {
		assert(bytes.size() == Size);

		std::copy(
			bytes.begin(),
			bytes.end(),
			this->data.begin()
		);
	}

	inline bool operator==(dtl::const_lvalue_reference<BitField> tmp) const {
		return this->data == tmp.data;
	}

	inline bool operator!=(dtl::const_lvalue_reference<BitField> tmp) const {
		return !this->operator==(tmp);
	}

	inline bool operator[](size_t index) const {
		return this->data[index / 8] & (
			1 << (7 - index % 8)
		);
	}

	inline bool get(size_t index) const {
		if ( index < bit_size ) {
			return this->operator[](index);
		} else {
			throw std::out_of_range("range_violated");
		}
	}

	inline void set(size_t index) {
		if ( index < bit_size ) {
			this->data[index / 8] |= (
				1 << (7 - index % 8)
			);
		} else {
			throw std::out_of_range("range_violated");
		}
	}

	inline void reset(size_t index) {
		if ( index < bit_size ) {
			this->data[index / 8] &= (
				~(1 << (7 - index % 8))
			);
		} else {
			throw std::out_of_range("range_violated");
		}
	}

	inline void toggle(size_t index) {
		if ( index < bit_size ) {
			this->data[index / 8] ^= (
				1 << (7 - index % 8)
			);
		} else {
			throw std::out_of_range("range_violated");
		}
	}

};

}

#endif  // BINARY_MAPPING_SRC_BIT_FIELD_H_
