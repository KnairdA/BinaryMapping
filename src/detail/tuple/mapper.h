#ifndef BINARY_MAPPING_SRC_DETAIL_TUPLE_MAPPER_H_
#define BINARY_MAPPING_SRC_DETAIL_TUPLE_MAPPER_H_

#include <cstddef>
#include <tuple>

#include "detail/type/sfinae.h"

namespace BinaryMapping {
namespace dtl {

struct Mapper {
	template <
		typename       Modifier,
		typename       Target,
		std::size_t    Index   = 0,
		std::ptrdiff_t Offset  = 0,
		typename       Current = std::tuple<>,
		typename       Base,
		enable_if<Index == std::tuple_size<Target>::value> = 0
	>
	static Target construct(Base, Current&& current) {
		return current;
	}

	template <
		typename       Modifier,
		typename       Target,
		std::size_t    Index   = 0,
		std::ptrdiff_t Offset  = 0,
		typename       Current = std::tuple<>,
		typename       Base,
		enable_if<Index < std::tuple_size<Target>::value> = 0
	>
	static Target construct(Base buffer, Current&& current = std::tuple<>()) {
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
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TUPLE_MAPPER_H_
