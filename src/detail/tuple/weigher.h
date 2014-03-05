#ifndef BINARY_MAPPING_SRC_DETAIL_TUPLE_WEIGHER_H_
#define BINARY_MAPPING_SRC_DETAIL_TUPLE_WEIGHER_H_

#include <tuple>

#include "detail/utility.h"

namespace BinaryMapping {
namespace dtl {

struct Weigher {
	template <
		typename Tuple,
		size_t Index    = 0,
		size_t Size     = 0,
		enable_if<Index == std::tuple_size<Tuple>::value> = 0
	>
	static constexpr size_t size() {
		return Size;
	}

	template <
		typename Tuple,
		size_t Index    = 0,
		size_t Size     = 0,
		enable_if<Index < std::tuple_size<Tuple>::value> = 0
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
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TUPLE_WEIGHER_H_
