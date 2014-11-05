#ifndef BINARY_MAPPING_SRC_DETAIL_TYPE_QUERY_H_
#define BINARY_MAPPING_SRC_DETAIL_TYPE_QUERY_H_

#include <type_traits>

#include "sfinae.h"

namespace BinaryMapping {
namespace dtl {

template <
	typename Type,
	typename Check
>
using check_if_class = typename std::conditional<
	std::is_class<Type>::value,
	Check,
	std::false_type
>::type;

template <typename Type>
struct has_data_member : std::integral_constant<
	bool,
	std::is_pod<decltype(Type:: bytes)>::value
> { };

template <typename Type>
using is_custom_serializable = std::integral_constant<
	bool,
	check_if_class<
		Type,
		has_data_member<Type>
	>::value
>;

template <
	typename Type,
	enable_if<is_custom_serializable<Type>::value> = 0
>
constexpr std::size_t size_of() {
	return std::tuple_size<decltype(Type:: bytes)>::value;
}

template <
	typename Type,
	enable_if<std::is_pod<Type>::value> = 0
>
constexpr std::size_t size_of() {
	return sizeof(Type);
}

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TYPE_QUERY_H_
