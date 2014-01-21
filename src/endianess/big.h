#ifndef BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
#define BINARY_MAPPING_SRC_ENDIANESS_BIG_H_

#include "endian.h"
#include "utility.h"

namespace BinaryMapping {

struct BigEndian {
	template <
		typename Key,
		enable_if<either<Key, uint64_t, int64_t>::value> = 0
	>
	static inline Key toTarget(
		ConstLValueReference<Key> number
	) {
		return htobe64(number);
	}

	template <
		typename Key,
		enable_if<either<Key, uint32_t, int32_t>::value> = 0
	>
	static inline Key toTarget(
		ConstLValueReference<Key> number
	) {
		return htobe32(number);
	}

	template <
		typename Key,
		enable_if<either<Key, uint16_t, int16_t>::value> = 0
	>
	static inline Key toTarget(
		ConstLValueReference<Key> number
	) {
		return htobe16(number);
	}

	template <
		typename Key,
		enable_if<either<Key, uint8_t, int8_t>::value> = 0
	>
	static inline Key toTarget(
		ConstLValueReference<Key> number
	) {
		return number;
	}

	template <
		typename Key,
		enable_if<either<Key, uint64_t, int64_t>::value> = 0
	>
	static inline Key toHost(
		ConstLValueReference<Key> number
	) {
		return be64toh(number);
	}

	template <
		typename Key,
		enable_if<either<Key, uint32_t, int32_t>::value> = 0
	>
	static inline Key toHost(
		ConstLValueReference<Key> number
	) {
		return be32toh(number);
	}

	template <
		typename Key,
		enable_if<either<Key, uint16_t, int16_t>::value> = 0
	>
	static inline Key toHost(
		ConstLValueReference<Key> number
	) {
		return be16toh(number);
	}

	template <
		typename Key,
		enable_if<either<Key, uint8_t, int8_t>::value> = 0
	>
	static inline Key toHost(
		ConstLValueReference<Key> number
	) {
		return number;
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
