#ifndef BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_VALUE_TUPLE_H_
#define BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_VALUE_TUPLE_H_

#include <tuple>

#include "endianess/out_of_place_sorter.h" 

namespace BinaryMapping {
namespace dtl {

template <typename Endianess>
struct ValueTuple {
	template <
		typename Target,
		size_t Index,
		off_t Offset,
		typename Base
	>
	static inline typename std::tuple_element<Index, Target>::type
	create(Base buffer) {
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
		return size_of<
			typename std::tuple_element<Index, Target>::type
		>();
	}
};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_VALUE_TUPLE_H_
