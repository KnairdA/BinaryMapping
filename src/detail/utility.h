#ifndef BINARY_MAPPING_SRC_DETAIL_UTILITY_H_
#define BINARY_MAPPING_SRC_DETAIL_UTILITY_H_

#include <type_traits>

namespace BinaryMapping {
namespace dtl {

template <
	typename Type,
	typename Check
>
using check_if_class = typename std::conditional<
	std::is_class<Type>::value,
	Check,
	std::integral_constant<bool, false>
>::type;

template <typename Type>
struct has_data_member : std::integral_constant<
	bool,
	std::is_pod<decltype(Type:: data)>::value
> { };

template <typename Type>
struct has_size_member : std::integral_constant<
	bool,
	std::is_same<decltype(Type::size), const size_t>::value
> { };

template <typename Type>
using const_lvalue_reference = typename std::add_lvalue_reference<
	typename std::add_const<Type>::type
>::type;

template <bool Condition>
using enable_if = typename std::enable_if<Condition, size_t>::type;

template <
	typename Type,
	typename TypeA,
	typename TypeB
>
struct either : std::integral_constant<
	bool,
	std::is_same<Type, TypeA>::value || std::is_same<Type, TypeB>::value
> { };

template <typename Type>
struct is_custom_serializable : std::integral_constant<
	bool,
	check_if_class<
		Type,
		has_data_member<Type>
	>::value
> { };

template <typename Type>
struct provides_own_size : std::integral_constant<
	bool,
	check_if_class<
		Type,
		has_size_member<Type>
	>::value
> { };

template <
	typename Type,
	enable_if<provides_own_size<Type>::value> = 0
>
constexpr size_t size_of() {
	return Type::size;
}

template <
	typename Type,
	enable_if<std::is_integral<Type>::value> = 0
>
constexpr size_t size_of() {
	return sizeof(Type);
}

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_UTILITY_H_
