#ifndef BINARY_MAPPING_SRC_TUPLE_DEREFERENCER_H_
#define BINARY_MAPPING_SRC_TUPLE_DEREFERENCER_H_

#include <tuple>

#include "utility.h"

#include "endianess/out_of_place_sorter.h" 

namespace BinaryMapping {

struct TupleDereferencer {
	template <
		typename Endianess,
		typename Source,
		typename Target,
		size_t Index     = 0,
		typename Current = std::tuple<>,
		enable_if<Index  == std::tuple_size<Source>::value> = 0
	>
	static inline Target dereference(
		const Source&,
		Current&& current
	) {
		return current;
	}

	template <
		typename Endianess,
		typename Source,
		typename Target,
		size_t Index     = 0,
		typename Current = std::tuple<>,
		enable_if<Index  < std::tuple_size<Source>::value> = 0
	>
	static inline Target dereference(
		const Source& source,
		Current&& current = std::tuple<>()
	) {
		return dereference<
			Endianess,
			Source,
			Target,
			Index  + 1
		>(
			source,
			std::tuple_cat(
				current,
				std::make_tuple(
					typename std::tuple_element<Index, Source>::type::element_type(
						OutOfPlaceSorter<Endianess>::sort(
							*std::get<Index>(source)
						)
					)
				)
			)
		);
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_DEREFERENCER_H_
