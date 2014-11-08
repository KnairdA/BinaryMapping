#ifndef BINARY_MAPPING_SRC_TYPE_BIT_FIELD_H_
#define BINARY_MAPPING_SRC_TYPE_BIT_FIELD_H_

#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <functional>

#include "custom_serializable.h"
#include "detail/type/transformation.h"

namespace BinaryMapping {

namespace dtl {

template <std::size_t Size>
struct bits_to_bytes : std::integral_constant<
	std::size_t,
	Size / 8
> {
	static_assert(
		Size % 8 == 0,
		"Bit count has to be byte aligned"
	);
};

}

template <std::size_t Size>
struct BitField : public CustomSerializable<
	dtl::bits_to_bytes<Size>::value
> {
	static const std::size_t size = Size;

	class reference;

	using CustomSerializable<
		dtl::bits_to_bytes<Size>::value
	>::CustomSerializable;

	reference operator[](std::size_t index) {
		return reference(*this, index);
	}

	bool operator[](std::size_t index) const {
		return this->test(index);
	}

	bool test(std::size_t index) const {
		return this->bytes.at(index / 8) & (
			1 << (7 - index % 8)
		);
	}

	bool any() const {
		return std::any_of(
			this->bytes.begin(),
			this->bytes.end(),
			[](dtl::const_lvalue_reference<std::uint8_t> tmp) -> bool {
				return tmp != 0;
			}
		);
	}

	bool all() const {
		return std::all_of(
			this->bytes.begin(),
			this->bytes.end(),
			[](dtl::const_lvalue_reference<std::uint8_t> tmp) -> bool {
				return tmp == UINT8_MAX;
			}
		);
	}

	bool none() const {
		return !this->any();
	}

	std::size_t count() const {
		std::size_t count{};

		for ( std::uint8_t byte : this->bytes ) {
			for ( ; byte; ++count ) {
				byte &= byte - 1;
			}
		}

		return count;
	}

	void set(std::size_t index, bool value = true) {
		if ( value ) {
			this->bytes.at(index / 8) |= (
				1 << (7 - index % 8)
			);
		} else {
			this->reset(index);
		}
	}

	void reset(std::size_t index) {
		this->bytes.at(index / 8) &= (
			~(1 << (7 - index % 8))
		);
	}

	void flip(std::size_t index) {
		this->bytes.at(index / 8) ^= (
			1 << (7 - index % 8)
		);
	}

	void set() {
		std::fill(
			this->bytes.begin(),
			this->bytes.end(),
			UINT8_MAX
		);
	}

	void reset() {
		std::fill(
			this->bytes.begin(),
			this->bytes.end(),
			0
		);
	}

	void flip() {
		std::for_each(
			this->bytes.begin(),
			this->bytes.end(),
			[](std::uint8_t& tmp) {
				tmp = ~tmp;
			}
		);
	}

	void operator&=(dtl::const_lvalue_reference<BitField> rhs) {
		std::transform(
			this->bytes.begin(),
			this->bytes.end(),
			rhs.bytes.begin(),
			this->bytes.begin(),
			std::bit_and<std::uint8_t>()
		);
	}

	void operator|=(dtl::const_lvalue_reference<BitField> rhs) {
		std::transform(
			this->bytes.begin(),
			this->bytes.end(),
			rhs.bytes.begin(),
			this->bytes.begin(),
			std::bit_or<std::uint8_t>()
		);
	}

	void operator^=(dtl::const_lvalue_reference<BitField> rhs) {
		std::transform(
			this->bytes.begin(),
			this->bytes.end(),
			rhs.bytes.begin(),
			this->bytes.begin(),
			std::bit_xor<std::uint8_t>()
		);
	}
};

}

#include "bit_field_reference.h"

#endif  // BINARY_MAPPING_SRC_TYPE_BIT_FIELD_H_
