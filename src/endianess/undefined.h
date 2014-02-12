#ifndef BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_
#define BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_

#include "detail/utility.h"

namespace BinaryMapping {

struct UndefinedEndian {
	template <
		typename Key,
		enable_if<std::is_integral<Key>::value> = 0
	>
	static inline Key toTarget(const_lvalue_reference<Key> number) {
		return number;
	}

	template <
		typename Key,
		enable_if<std::is_integral<Key>::value> = 0
	>
	static inline Key toHost(const_lvalue_reference<Key> number) {
		return number;
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_
