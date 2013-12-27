#ifndef BINARY_MAPPING_SRC_TUPLE_WEIGHER_H_
#define BINARY_MAPPING_SRC_TUPLE_WEIGHER_H_

#include <tuple>

namespace BinaryMapping {

struct TupleWeigher {
	template <
		typename Tuple,
		size_t Index,
		size_t Size
	>
	static constexpr typename std::enable_if<
		Index == std::tuple_size<Tuple>::value, size_t
	>::type size() {
		return Size;
	}

	template <
		typename Tuple,
		size_t Index = 0,
		size_t Size  = 0
	>
	static constexpr typename std::enable_if<
		Index < std::tuple_size<Tuple>::value, size_t
	>::type size() { 
		return size<
			Tuple,
			Index + 1,
			Size  + sizeof(
				typename std::tuple_element<Index, Tuple>::type::element_type
			)
		>();
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_WEIGHER_H_
