#ifndef BINARY_MAPPING_SRC_TYPE_TYPE_SERIALIZABLE_H_
#define BINARY_MAPPING_SRC_TYPE_TYPE_SERIALIZABLE_H_

#include <array>
#include <cassert>

#include "detail/utility.h"

namespace BinaryMapping {

template <size_t Size>
struct CustomSerializable {
	std::array<uint8_t, Size> bytes;

	CustomSerializable(): bytes{} { }
	CustomSerializable(CustomSerializable&&) = default;
	CustomSerializable(CustomSerializable&)  = default;

	CustomSerializable(
		dtl::const_lvalue_reference<CustomSerializable> src):
		bytes(src.bytes) { }

	CustomSerializable(const std::initializer_list<uint8_t>&& tmp) {
		assert(tmp.size() == Size);

		std::copy(
			tmp.begin(),
			tmp.end(),
			this->bytes.begin()
		);
	}

	CustomSerializable& operator=(
		dtl::const_lvalue_reference<CustomSerializable> src) {
		this->bytes = src.bytes;

		return *this;
	}

	inline bool operator==(
		dtl::const_lvalue_reference<CustomSerializable> tmp) const {
		return this->bytes == tmp.bytes;
	}

	inline bool operator!=(
		dtl::const_lvalue_reference<CustomSerializable> tmp) const {
		return !this->operator==(tmp);
	}
};

template <size_t Size>
using ByteField = CustomSerializable<Size>;

}

#endif  // BINARY_MAPPING_SRC_TYPE_TYPE_SERIALIZABLE_H_