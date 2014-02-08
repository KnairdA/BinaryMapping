#ifndef BINARY_MAPPING_SRC_TUPLE_SETTER_H_
#define BINARY_MAPPING_SRC_TUPLE_SETTER_H_

namespace BinaryMapping {

struct Setter {
	template <
		typename Target,
		typename Source,
		typename Tuple,
		size_t Index     = 0,
		enable_if<Index  == std::tuple_size<Source>::value> = 0
	>
	static inline void populate(const Source&, Tuple*) { }

	template <
		typename Target,
		typename Source,
		typename Tuple,
		size_t Index     = 0,
		enable_if<Index  < std::tuple_size<Source>::value> = 0
	>
	static inline void populate(const Source& source, Tuple* target) {
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

		target->template set<Index>(
			std::get<Index>(source)
		);

		populate<
			Target,
			Source,
			Tuple,
			Index  + 1
		>(
			source,
			target
		);
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_SETTER_H_
