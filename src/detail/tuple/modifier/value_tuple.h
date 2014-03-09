#ifndef BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_VALUE_TUPLE_H_
#define BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_VALUE_TUPLE_H_

#include <cstddef>
#include <tuple>

#include "endianess/out_of_place_sorter.h" 

namespace BinaryMapping {
namespace dtl {

template <typename Endianess>
struct ValueTuple {
	template <
		typename Target,
		std::size_t Index,
		std::ptrdiff_t Offset,
		typename Base
	>
	static inline typename std::tuple_element<Index, Target>::type
	create(Base buffer) {
		return typename std::tuple_element<Index, Target>::type(
			OutOfPlaceSorter<Endianess>::sort(
				*reinterpret_cast<pointer_to_const<
					typename std::tuple_element<Index, Target>::type
				>>(*buffer + Offset)
			)
		);
	}

	template <
		typename Target,
		std::size_t Index
	>
	static constexpr std::size_t size() {
		return size_of<
			typename std::tuple_element<Index, Target>::type
		>();
	}
};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_VALUE_TUPLE_H_
