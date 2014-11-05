#ifndef BINARY_MAPPING_SRC_DETAIL_SFINAE_H_
#define BINARY_MAPPING_SRC_DETAIL_SFINAE_H_

#include <type_traits>

namespace BinaryMapping {
namespace dtl {

template <bool Condition>
using enable_if = typename std::enable_if<Condition, std::size_t>::type;

template <
	typename Type,
	typename TypeA,
	typename TypeB
>
using enable_if_either = enable_if<
	std::is_same<Type, TypeA>::value || std::is_same<Type, TypeB>::value
>;

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_SFINAE_H_
