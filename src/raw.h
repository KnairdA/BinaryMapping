#ifndef BINARY_MAPPING_SRC_RAW_H_
#define BINARY_MAPPING_SRC_RAW_H_

#include <algorithm>

namespace BinaryMapping {

template <size_t Size>
struct Raw {
	static const size_t size = Size;

	union {
		uint8_t data[Size];
	};

	Raw(Raw<Size>&&)       = default;
	Raw(Raw<Size>&)        = default;
	Raw(const Raw<Size>&)  = default;

	template <typename... Bytes>
	Raw(Bytes&&... bytes):
		data{ std::forward<Bytes>(bytes)... } { }

	Raw<Size>& operator=(const Raw<Size>&) = default;

	inline bool operator==(const Raw<Size>& tmp) const {
		return std::equal(
			std::begin(this->data),
			std::end(this->data),
			std::begin(tmp.data)
		);
	}

	inline bool operator!=(const Raw<Size>& tmp) const {
		return !this->operator==(tmp);
	}
};

}

#endif  // BINARY_MAPPING_SRC_RAW_H_
