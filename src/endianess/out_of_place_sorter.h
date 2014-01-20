#ifndef BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_

#include "utility.h"

namespace BinaryMapping {

template <class Endianess>
struct OutOfPlaceSorter {
	template <
		typename Key,
		enable_if<std::is_integral<Key>::value>...
	>
	static inline Key mix(ConstLValueReference<Key> number) {
		return Endianess::template toTarget<Key>(number);
	}

	template <
		typename Custom,
		enable_if<is_custom_serializable<Custom>::value>...
	>
	static inline Custom mix(ConstLValueReference<Custom> tmp) {
		return tmp;
	}

	template <
		typename Key,
		enable_if<std::is_integral<Key>::value>...
	>
	static inline Key sort(
		typename std::add_pointer<Key>::type buffer
	) {
		return Endianess::template toHost<Key>(*buffer);
	}

	template <
		typename Custom,
		enable_if<is_custom_serializable<Custom>::value>...
	>
	static inline Custom sort(
		typename std::add_pointer<Custom>::type buffer
	) {
		return *buffer;
	}

	template <
		typename Key,
		enable_if<std::is_integral<Key>::value>...
	>
	static inline Key sort(Key number) {
		return Endianess::template toHost<Key>(number);
	}

	template <
		typename Custom,
		enable_if<is_custom_serializable<Custom>::value>...
	>
	static inline Custom sort(Custom tmp) {
		return tmp;
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
