#ifndef BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
#define BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_

#include "endian.h"
#include <utility.h>

namespace BinaryMapping {

struct LittleEndian {
	template <typename Key>
	struct Implementation {
		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint64_t, int64_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return htole64(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint32_t, int32_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return htole32(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint16_t, int16_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return htole16(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint8_t, int8_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return number;
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint64_t, int64_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return le64toh(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint32_t, int32_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return le32toh(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint16_t, int16_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return le16toh(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint8_t, int8_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return number;
		}
	};

	template <typename Key>
	static inline Key toTarget(ConstLValueReference<Key> number) {
		return Implementation<Key>::toTarget(number);
	}

	template <typename Key>
	static inline Key toHost(ConstLValueReference<Key> number) {
		return Implementation<Key>::toHost(number);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
