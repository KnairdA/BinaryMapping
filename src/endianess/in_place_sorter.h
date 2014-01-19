#ifndef BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_

#include "utility.h"

namespace BinaryMapping {

template <class Endianess>
struct InPlaceSorter {
	template <
		typename Key,
		enable_if<std::is_integral<Key>::value>...
	>
	static inline void mix(
		typename std::add_pointer<Key>::type buffer,
		ConstLValueReference<Key> number
	) {
		*buffer = Endianess::template toTarget<Key>(number);
	}

	template <
		typename Union,
		enable_if<std::is_union<Union>::value>...
	>
	static inline void mix(
		typename std::add_pointer<Union>::type buffer,
		ConstLValueReference<Union> tmp
	) {
		*buffer = tmp;
	}

	template <
		typename Key,
		enable_if<std::is_integral<Key>::value>...
	>
	static inline void sort(
		typename std::add_pointer<Key>::type buffer
	) {
		*buffer = Endianess::template toHost<Key>(*buffer);
	}

	template <
		typename Union,
		enable_if<std::is_union<Union>::value>...
	>
	static inline void sort(
		typename std::add_pointer<Union>::type
	) { }
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_
