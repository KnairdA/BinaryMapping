#ifndef BINARY_MAPPING_SRC_TUPLE_MAPPER_H_
#define BINARY_MAPPING_SRC_TUPLE_MAPPER_H_

#include <tuple>

#include "detail/utility.h"

namespace BinaryMapping {

struct Mapper {
	template <
		typename Modifier,
		typename Target,
		size_t Index     = 0,
		off_t Offset     = 0,
		typename Current = std::tuple<>,
		dtl::enable_if<Index  == std::tuple_size<Target>::value> = 0
	>
	static inline Target construct(
		uint8_t*const*,
		Current&& current
	) {
		return current;
	}

	template <
		typename Modifier,
		typename Target,
		size_t Index     = 0,
		off_t Offset     = 0,
		typename Current = std::tuple<>,
		dtl::enable_if<Index  < std::tuple_size<Target>::value> = 0
	>
	static inline Target construct(
		uint8_t*const* buffer,
		Current&& current = std::tuple<>()
	) {
		return construct<
			Modifier,
			Target,
			Index  + 1,
			Offset + Modifier::template size<Target, Index>()
		>(
			buffer,
			std::tuple_cat(
				current,
				std::make_tuple(
					Modifier::template create<Target, Index, Offset>(buffer)
				)
			)
		);
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_MAPPER_H_
