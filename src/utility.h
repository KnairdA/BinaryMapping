#ifndef BINARY_MAPPING_SRC_UTILITY_H_
#define BINARY_MAPPING_SRC_UTILITY_H_

#include <type_traits>

namespace BinaryMapping {

template <
	typename Type,
	typename TypeA,
	typename TypeB
>
struct EnableIfEither {
	typedef typename std::enable_if<
		std::is_same<Type, TypeA>::value || std::is_same<Type, TypeB>::value,
		typename std::conditional<
			std::is_same<Type, TypeA>::value,
			TypeA,
			TypeB
		>::type
	>::type type;
};

template <typename Type>
struct ConstLValueReference {
	typedef typename std::add_lvalue_reference<
		typename std::add_const<Type>::type
	>::type type;
};

}

#endif  // BINARY_MAPPING_SRC_UTILITY_H_
