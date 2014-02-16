#ifndef BINARY_MAPPING_SRC_BIT_FIELD_H_
#define BINARY_MAPPING_SRC_BIT_FIELD_H_

#include <array>
#include <algorithm>

#include "detail/utility.h"

namespace BinaryMapping {

template <size_t Size>
struct BitField {
	static const size_t size = Size * 8;

	std::array<uint8_t, Size> bytes;

	template <typename... Bytes>
	BitField(Bytes&&... bytes):
		bytes{ std::forward<Bytes>(bytes)... } { }

	BitField(const std::initializer_list<uint8_t>&& tmp) {
		assert(tmp.size() == Size);

		std::copy(
			tmp.begin(),
			tmp.end(),
			this->bytes.begin()
		);
	}

	BitField(BitField&&)                 = default;
	BitField(BitField&)                  = default;
	BitField(const BitField&)            = default;
	BitField& operator=(const BitField&) = default;

	inline bool operator==(dtl::const_lvalue_reference<BitField> tmp) const {
		return this->bytes == tmp.bytes;
	}

	inline bool operator!=(dtl::const_lvalue_reference<BitField> tmp) const {
		return !this->operator==(tmp);
	}

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
