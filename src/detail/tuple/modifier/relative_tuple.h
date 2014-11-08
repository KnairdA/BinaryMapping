#ifndef BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_RELATIVE_TUPLE_H_
#define BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_RELATIVE_TUPLE_H_

#include <cstddef>
#include <tuple>

namespace BinaryMapping {
namespace dtl {

struct RelativeTuple {
	template <
		typename       Target,
		std::size_t    Index,
		std::ptrdiff_t Offset,
		typename       Base
	>
	static typename std::tuple_element<Index, Target>::type create(Base buffer) {
		return typename std::tuple_element<Index, Target>::type(
			buffer, Offset
		);
	}

	template <
		typename    Target,
		std::size_t Index
	>
	static constexpr std::size_t size() {
		return size_of<
			typename std::tuple_element<Index, Target>::type::element_type
		>();
	}
};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TUPLE_MODIFIER_RELATIVE_TUPLE_H_
