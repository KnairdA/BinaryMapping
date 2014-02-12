#ifndef BINARY_MAPPING_SRC_TUPLE_MODIFIER_VALUE_TUPLE_H_
#define BINARY_MAPPING_SRC_TUPLE_MODIFIER_VALUE_TUPLE_H_

#include <tuple>

#include "endianess/out_of_place_sorter.h" 

namespace BinaryMapping {

template <typename Endianess>
struct ValueTuple {
	template <
		typename Target,
		size_t Index,
		off_t Offset
	>
	static inline typename std::tuple_element<Index, Target>::type
	create(uint8_t*const* buffer) {
		return typename std::tuple_element<Index, Target>::type(
			OutOfPlaceSorter<Endianess>::sort(
				*reinterpret_cast<typename std::add_pointer<
					typename std::tuple_element<Index, Target>::type
				>::type>(*buffer + Offset)
			)
		);
	}

	template <
		typename Target,
		size_t Index
	>
	static constexpr size_t size() {
		return dtl::size_of<
			typename std::tuple_element<Index, Target>::type
		>();
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_MODIFIER_VALUE_TUPLE_H_
