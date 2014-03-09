#ifndef BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
#define BINARY_MAPPING_SRC_ENDIANESS_BIG_H_

#include <cstdint>

#include "endian.h"
#include "detail/utility.h"

namespace BinaryMapping {

struct BigEndian {
	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint64_t, std::int64_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return htobe64(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint32_t, std::int32_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return htobe32(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint16_t, std::int16_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return htobe16(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint8_t, std::int8_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return number;
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint64_t, std::int64_t> = 0
	>
	static inline Key toHost(
		dtl::const_lvalue_reference<Key> number
	) {
		return be64toh(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint32_t, std::int32_t> = 0
	>
	static inline Key toHost(
		dtl::const_lvalue_reference<Key> number
	) {
		return be32toh(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint16_t, std::int16_t> = 0
	>
	static inline Key toHost(
		dtl::const_lvalue_reference<Key> number
	) {
		return be16toh(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint8_t, std::int8_t> = 0
	>
	static inline Key toHost(
		dtl::const_lvalue_reference<Key> number
	) {
		return number;
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
