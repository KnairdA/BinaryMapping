#ifndef BINARY_MAPPING_SRC_TUPLE_MAPPER_H_
#define BINARY_MAPPING_SRC_TUPLE_MAPPER_H_

#include <tuple>

#include "utility.h"

namespace BinaryMapping {

struct TupleMapper {
	template <
		typename Target,
		size_t Index     = 0,
		off_t Offset     = 0,
		typename Current = std::tuple<>,
		enable_if<Index  == std::tuple_size<Target>::value> = 0
	>
	static inline Target construct(
		uint8_t*const*,
		Current&& current
	) {
		return current;
	}

	template <
		typename Target,
		size_t Index     = 0,
		off_t Offset     = 0,
		typename Current = std::tuple<>,
		enable_if<Index  < std::tuple_size<Target>::value> = 0
	>
	static inline Target construct(
		uint8_t*const* buffer,
		Current&& current = std::tuple<>()
	) {
		return construct<
			Target,
			Index  + 1,
			Offset + size_of<
				typename std::tuple_element<Index, Target>::type::element_type
			>()
		>(
			buffer,
			std::tuple_cat(
				current,
				std::make_tuple(
					typename std::tuple_element<Index, Target>::type(
						buffer, Offset
					)
				)
			)
		);
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_MAPPER_H_
