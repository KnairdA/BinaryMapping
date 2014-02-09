#ifndef BINARY_MAPPING_SRC_TUPLE_SETTER_H_
#define BINARY_MAPPING_SRC_TUPLE_SETTER_H_

#include "endianess/in_place_sorter.h" 

namespace BinaryMapping {

template <typename Endianess>
struct Setter {
	template <
		typename Target,
		typename Source,
		size_t Index     = 0,
		enable_if<Index  == std::tuple_size<Source>::value> = 0
	>
	static inline void populate(const Source&, const Target&) { }

	template <
		typename Target,
		typename Source,
		size_t Index     = 0,
		enable_if<Index  < std::tuple_size<Source>::value> = 0
	>
	static inline void populate(
		const Source& source,
		const Target& target
	) {
		static_assert(
			std::is_same<
				typename std::tuple_element<
					Index,
					Source
				>::type,
				typename std::tuple_element<
					Index,
					Target
				>::type::element_type
			>::value,
			"element_type of the target has to match the source type"
		);

		InPlaceSorter<Endianess>::template mix<
			typename std::tuple_element<
				Index,
				Target
			>::type::element_type
		>(
			std::get<Index>(target).get(),
			std::get<Index>(source)
		);

		populate<
			Target,
			Source,
			Index  + 1
		>(
			source,
			target
		);
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_SETTER_H_
