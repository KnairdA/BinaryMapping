#ifndef BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
#define BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_

#include "endian.h"
#include <utility.h>

namespace BinaryMapping {

struct LittleEndian {

template <
	typename Key,
	typename Specializer = Key
>
struct toTarget;

template <typename Key>
struct toTarget<Key, typename EnableIfEither<Key, uint64_t, int64_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return htole64(number);
	}
};

template <typename Key>
struct toTarget<Key, typename EnableIfEither<Key, uint32_t, int32_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return htole32(number);
	}
};

template <typename Key>
struct toTarget<Key, typename EnableIfEither<Key, uint16_t, int16_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return htole16(number);
	}
};

template <typename Key>
struct toTarget<Key, typename EnableIfEither<Key, uint8_t, int8_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return number;
	}
};

template <
	typename Key,
	typename Specializer = Key
>
struct toHost;

template <typename Key>
struct toHost<Key, typename EnableIfEither<Key, uint64_t, int64_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return le64toh(number);
	}
};

template <typename Key>
struct toHost<Key, typename EnableIfEither<Key, uint32_t, int32_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return le32toh(number);
	}
};

template <typename Key>
struct toHost<Key, typename EnableIfEither<Key, uint16_t, int16_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return le16toh(number);
	}
};

template <typename Key>
struct toHost<Key, typename EnableIfEither<Key, uint8_t, int8_t>::type> {
	Key operator()(typename ConstLValueReference<Key>::type number) {
		return number;
	}
};

};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
