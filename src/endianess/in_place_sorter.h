#ifndef BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_

namespace BinaryMapping {

template <class Endianess>
struct InPlaceSorter {
	template <typename Key>
	static inline void mix(
		typename std::add_pointer<Key>::type buffer,
		typename std::add_lvalue_reference<
			typename std::add_const<Key>::type
		>::type number
	) {
		*buffer = Endianess::template toTarget<Key>(number);
	}

	template <typename Key>
	static inline void sort(
		typename std::add_pointer<Key>::type buffer
	) {
		*buffer = Endianess::template toHost<Key>(*buffer);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_
