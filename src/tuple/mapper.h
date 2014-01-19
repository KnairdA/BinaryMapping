#ifndef BINARY_MAPPING_SRC_TUPLE_MAPPER_H_
#define BINARY_MAPPING_SRC_TUPLE_MAPPER_H_

#include <tuple>

#include "utility.h"

namespace BinaryMapping {

struct TupleMapper {
	template <
		typename Tuple,
		size_t Index     = 0,
		off_t Offset     = 0,
		typename Current,
		enable_if<Index  == std::tuple_size<Tuple>::value>...
	>
	static inline Tuple construct(uint8_t*const*, Current&& tuple) {
		return tuple;
	}

	template <
		typename Tuple,
		size_t Index     = 0,
		off_t Offset     = 0,
		typename Current = std::tuple<>,
		enable_if<Index  < std::tuple_size<Tuple>::value>...
	>
	static inline Tuple construct(
		uint8_t*const* buffer,
		Current&& tuple = std::tuple<>()
	) {
		return construct<
			Tuple,
			Index  + 1,
			Offset + size_of<
				typename std::tuple_element<Index, Tuple>::type::element_type
			>()
		>(
			buffer,
			std::tuple_cat(
				tuple,
				std::make_tuple(
					typename std::tuple_element<Index, Tuple>::type(
						buffer, Offset
					)
				)
			)
		);
	}

	template <
		typename Tuple,
		typename Source,
		size_t Index     = 0,
		typename Current,
		enable_if<Index  == std::tuple_size<Tuple>::value>...
	>
	static inline Tuple carbonCopy(const Source&, Current&& tuple) {
		return tuple;
	}

	template <
		typename Tuple,
		typename Source,
		size_t Index     = 0,
		typename Current = std::tuple<>,
		enable_if<Index  < std::tuple_size<Tuple>::value>...
	>
	static inline Tuple carbonCopy(
		const Source& src,
		Current&& tuple = std::tuple<>()
	) {
		return carbonCopy<
			Tuple,
			Source,
			Index + 1
		>(
			src,
			std::tuple_cat(
				tuple,
				std::make_tuple(
					typename std::tuple_element<Index, Tuple>::type(
						src.template get<Index>()
					)
				)
			)
		);
	}
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_MAPPER_H_
