#ifndef BINARY_MAPPING_SRC_UTILITY_H_
#define BINARY_MAPPING_SRC_UTILITY_H_

#include <type_traits>

namespace BinaryMapping {

template <
	typename Type,
	typename TypeA,
	typename TypeB
>
using EnableIfEither = typename std::enable_if<
	std::is_same<Type, TypeA>::value || std::is_same<Type, TypeB>::value,
	typename std::conditional<
		std::is_same<Type, TypeA>::value,
		TypeA,
		TypeB
	>::type
>::type;

template <typename Type>
using ConstLValueReference = typename std::add_lvalue_reference<
	typename std::add_const<Type>::type
>::type;

namespace {
	enum class dummy { };
}

template <bool Condition>
using enable_if = typename std::enable_if<Condition, dummy>::type;

template <typename Type>
constexpr typename std::enable_if<
	std::is_integral<Type>::value || std::is_union<Type>::value,
	size_t
>::type size_of() {
	return sizeof(Type);
}

template <typename Type>
constexpr typename std::enable_if<
	std::is_same<decltype(Type::size), size_t>::value,
	size_t
>::type size_of() {
	return Type::size;
}

}

#endif  // BINARY_MAPPING_SRC_UTILITY_H_
