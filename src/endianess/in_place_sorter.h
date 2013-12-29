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
		typename Endianess::template toTarget<Key> toTarget;
		*buffer = toTarget(number);
	}

	template <typename Key>
	static inline void sort(
		typename std::add_pointer<Key>::type buffer
	) {
		typename Endianess::template toHost<Key> toHost;
		*buffer = toHost(*buffer);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_IN_PLACE_SORTER_H_
