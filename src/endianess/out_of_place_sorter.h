#ifndef BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_

namespace BinaryMapping {

template <class Endianess>
struct OutOfPlaceSorter {
	template <typename Key>
	static inline Key mix(
		typename std::add_lvalue_reference<
			typename std::add_const<Key>::type
		>::type number
	) {
		typename Endianess::template toTarget<Key> toTarget;
		return toTarget(number);
	}

	template <typename Key>
	static inline Key sort(
		typename std::add_pointer<Key>::type buffer
	) {
		typename Endianess::template toHost<Key> toHost;
		return toHost(*buffer);
	}

	template <typename Key>
	static inline Key sort(Key number) {
		typename Endianess::template toHost<Key> toHost;
		return toHost(number);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_OUT_OF_PLACE_SORTER_H_
