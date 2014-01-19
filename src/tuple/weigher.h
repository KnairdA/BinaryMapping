#ifndef BINARY_MAPPING_SRC_TUPLE_WEIGHER_H_
#define BINARY_MAPPING_SRC_TUPLE_WEIGHER_H_

#include <tuple>

#include "utility.h"

namespace BinaryMapping {

struct TupleWeigher {
	template <
		typename Tuple,
		size_t Index,
		size_t Size,
		enable_if<Index == std::tuple_size<Tuple>::value>...
	>
	static constexpr size_t size() {
		return Size;
	}

	template <
		typename Tuple,
		size_t Index    = 0,
		size_t Size     = 0,
		enable_if<Index < std::tuple_size<Tuple>::value>...
	>
	static constexpr size_t size() { 
		return size<
			Tuple,
			Index + 1,
			Size  + size_of<
				typename std::tuple_element<Index, Tuple>::type::element_type
			>()
		>();
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_WEIGHER_H_
