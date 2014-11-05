#ifndef BINARY_MAPPING_SRC_DETAIL_TYPE_TRANSFORMATION_H_
#define BINARY_MAPPING_SRC_DETAIL_TYPE_TRANSFORMATION_H_

#include <type_traits>

namespace BinaryMapping {
namespace dtl {

template <typename Type>
using const_lvalue_reference = typename std::add_lvalue_reference<
	typename std::add_const<Type>::type
>::type;

template <typename Type>
using pointer_to_const = typename std::add_pointer<
	typename std::add_const<Type>::type
>::type;

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TYPE_TRANSFORMATION_H_
