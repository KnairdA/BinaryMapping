#ifndef BINARY_MAPPING_SRC_TYPE_TUPLE_H_
#define BINARY_MAPPING_SRC_TYPE_TUPLE_H_

#include <type_traits>

#include "detail/tuple/tuple.h"

namespace BinaryMapping {

template <
	typename Endianess,
	typename... Types
>
struct Tuple {
	template <typename Base>
	using type = typename std::conditional<
		std::is_const<Base>::value,
		dtl::Tuple<Base, Endianess, typename std::add_const<Types>::type...>,
		dtl::Tuple<Base, Endianess, Types...>
	>::type;
};

template <typename... Types>
using PlainTuple = Tuple<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TYPE_TUPLE_H_
