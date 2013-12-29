#ifndef BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_

#include "utility.h"

namespace BinaryMapping {

template <class Endianess>
struct OutOfPlaceSorter {
	template <typename Key>
	static inline Key mix(ConstLValueReference<Key> number) {
		return Endianess::template toTarget<Key>(number);
	}

	template <typename Key>
	static inline Key sort(
		typename std::add_pointer<Key>::type buffer
	) {
		return Endianess::template toHost<Key>(*buffer);
	}

	template <typename Key>
	static inline Key sort(Key number) {
		return Endianess::template toHost<Key>(number);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
