#ifndef BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_
#define BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_

namespace BinaryMapping {

struct UndefinedEndian {
	template <typename Key>
	static inline Key toTarget(typename std::add_lvalue_reference<
		typename std::add_const<Key>::type
	>::type number) {
		return number;
	}

	template <typename Key>
	static inline Key toHost(typename std::add_lvalue_reference<
		typename std::add_const<Key>::type
	>::type number) {
		return number;
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_UNDEFINED_H_
