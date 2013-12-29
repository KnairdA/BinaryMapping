#ifndef BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_
#define BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_

#include "utility.h"

namespace BinaryMapping {

struct UndefinedEndian {

template <typename Key>
struct toTarget {
	inline Key operator()(typename ConstLValueReference<Key>::type number) {
		return number;
	}
};

template <typename Key>
struct toHost {
	inline Key operator()(typename ConstLValueReference<Key>::type number) {
		return number;
	}
};

};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_
