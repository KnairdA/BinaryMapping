#ifndef BINARY_MAPPING_SRC_ENDIANESS_SERIALIZER_H_
#define BINARY_MAPPING_SRC_ENDIANESS_SERIALIZER_H_

#include <tuple>

namespace BinaryMapping {

template <class ByteSorter>
struct Serializer {
	template <
		typename Tuple,
		size_t Index
	>
	static inline typename std::enable_if<
		Index == std::tuple_size<Tuple>::value, void
	>::type serialize(Tuple&) { }

	template <
		typename Tuple,
		size_t Index = 0
	>
	static inline typename std::enable_if<
		Index < std::tuple_size<Tuple>::value, void
	>::type serialize(Tuple& tuple) { 
		ByteSorter::template mix<
			typename std::tuple_element<Index, Tuple>::type::element_type
		>(
			std::get<Index>(tuple).get(), *std::get<Index>(tuple)
		);

		serialize<Tuple, Index + 1>(tuple);
	}

	template <
		typename Tuple,
		size_t Index
	>
	static inline typename std::enable_if<
		Index == std::tuple_size<Tuple>::value, void
	>::type deserialize(Tuple&) { }

	template <
		typename Tuple,
		size_t Index = 0
	>
	static inline typename std::enable_if<
		Index < std::tuple_size<Tuple>::value, void
	>::type deserialize(Tuple& tuple) { 
		ByteSorter::template sort<
			typename std::tuple_element<Index, Tuple>::type::element_type
		>(std::get<Index>(tuple).get());

		deserialize<Tuple, Index + 1>(tuple);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_SERIALIZER_H_
