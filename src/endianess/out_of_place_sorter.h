#ifndef BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_

#include "detail/utility.h"

namespace BinaryMapping {

template <class Endianess>
struct OutOfPlaceSorter {
	template <
		typename Key,
		dtl::enable_if<std::is_integral<Key>::value> = 0
	>
	static inline Key mix(dtl::const_lvalue_reference<Key> number) {
		return Endianess::template toTarget<Key>(number);
	}

	template <
		typename Custom,
		dtl::enable_if<dtl::is_custom_serializable<Custom>::value> = 0
	>
	static inline Custom mix(dtl::const_lvalue_reference<Custom> tmp) {
		return tmp;
	}

	template <
		typename Key,
		dtl::enable_if<std::is_integral<Key>::value> = 0
	>
	static inline Key sort(
		typename std::add_pointer<Key>::type buffer
	) {
		return Endianess::template toHost<Key>(*buffer);
	}

	template <
		typename Custom,
		dtl::enable_if<dtl::is_custom_serializable<Custom>::value> = 0
	>
	static inline Custom sort(
		typename std::add_pointer<Custom>::type buffer
	) {
		return *buffer;
	}

	template <
		typename Key,
		dtl::enable_if<std::is_integral<Key>::value> = 0
	>
	static inline Key sort(Key number) {
		return Endianess::template toHost<Key>(number);
	}

	template <
		typename Custom,
		dtl::enable_if<dtl::is_custom_serializable<Custom>::value> = 0
	>
	static inline Custom sort(Custom tmp) {
		return tmp;
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
