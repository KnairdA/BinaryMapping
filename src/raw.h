#ifndef BINARY_MAPPING_SRC_RAW_H_
#define BINARY_MAPPING_SRC_RAW_H_

#include <array>

namespace BinaryMapping {

template <size_t Size>
struct Raw {
	static const size_t size = Size;

	union {
		std::array<uint8_t, Size> data;
	};

	Raw(Raw<Size>&&)       = default;
	Raw(Raw<Size>&)        = default;
	Raw(const Raw<Size>&)  = default;

	template <typename... Bytes>
	Raw(Bytes&&... bytes):
		data{ std::forward<Bytes>(bytes)... } { }

	Raw(const std::initializer_list<uint8_t>&& bytes) {
		assert(bytes.size() == Size);

		std::move(
			bytes.begin(),
			bytes.end(),
			this->data.begin()
		);
	}

	Raw<Size>& operator=(const Raw<Size>&) = default;

	inline bool operator==(const Raw<Size>& tmp) const {
		return this->data == tmp.data;
	}

	inline bool operator!=(const Raw<Size>& tmp) const {
		return !this->operator==(tmp);
	}
};

}

#endif  // BINARY_MAPPING_SRC_RAW_H_
