#ifndef BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
#define BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_

#include <cstdint>

#include "endian.h"
#include <detail/utility.h>

namespace BinaryMapping {

struct LittleEndian {
	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint64_t, std::int64_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return htole64(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint32_t, std::int32_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return htole32(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint16_t, std::int16_t> = 0
	>
	static inline Key toTarget(
		dtl::const_lvalue_reference<Key> number
	) {
		return htole16(number);
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
		return le64toh(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint32_t, std::int32_t> = 0
	>
	static inline Key toHost(
		dtl::const_lvalue_reference<Key> number
	) {
		return le32toh(number);
	}

	template <
		typename Key,
		dtl::enable_if_either<Key, std::uint16_t, std::int16_t> = 0
	>
	static inline Key toHost(
		dtl::const_lvalue_reference<Key> number
	) {
		return le16toh(number);
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

#endif  // BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
