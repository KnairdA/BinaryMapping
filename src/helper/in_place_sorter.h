#ifndef BINARY_MAPPING_SRC_HELPER_IN_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_HELPER_IN_PLACE_SORTER_H_

#include "detail/type/sfinae.h"
#include "detail/type/query.h"
#include "detail/type/transformation.h"

namespace BinaryMapping {

template <class Endianess>
struct InPlaceSorter {
	template <
		typename Key,
		dtl::enable_if<std::is_integral<Key>::value> = 0
	>
	static void mix(
		typename std::add_pointer<Key>::type buffer,
		dtl::const_lvalue_reference<Key>     number
	) {
		*buffer = Endianess::template toTarget<Key>(number);
	}

	template <
		typename Custom,
		dtl::enable_if<dtl::is_custom_serializable<Custom>::value> = 0
	>
	static void mix(
		typename std::add_pointer<Custom>::type buffer,
		dtl::const_lvalue_reference<Custom>     tmp
	) {
		*buffer = tmp;
	}

	template <
		typename Key,
		dtl::enable_if<std::is_integral<Key>::value> = 0
	>
	static void sort(typename std::add_pointer<Key>::type buffer) {
		*buffer = Endianess::template toHost<Key>(*buffer);
	}

	template <
		typename Custom,
		dtl::enable_if<dtl::is_custom_serializable<Custom>::value> = 0
	>
	static void sort(typename std::add_pointer<Custom>::type) { }
};

}

#endif  // BINARY_MAPPING_SRC_HELPER_IN_PLACE_SORTER_H_
