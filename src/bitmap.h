#ifndef BINARY_MAPPING_SRC_BITMAP_H_
#define BINARY_MAPPING_SRC_BITMAP_H_

#include <stdexcept>

#include "detail/utility.h"
#include "raw.h"

namespace BinaryMapping {

template<size_t Size>
struct BitMap : public Raw<
	dtl::round_to_byte<Size>::value
> {
	static const size_t bit_size = Size;

	using Raw<BitMap::size>::Raw;

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

#endif  // BINARY_MAPPING_SRC_BITMAP_H_
