#ifndef BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
#define BINARY_MAPPING_SRC_ENDIANESS_BIG_H_

#include "endian.h"
#include "utility.h"

namespace BinaryMapping {

struct BigEndian {
	template <typename Key>
	struct Implementation {
		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint64_t, int64_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return htobe64(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint32_t, int32_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return htobe32(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint16_t, int16_t> toTarget(
			ConstLValueReference<Helper> number
		) {
			return htobe16(number);
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
			return be64toh(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint32_t, int32_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return be32toh(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint16_t, int16_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return be16toh(number);
		}

		template <typename Helper = Key>
		static inline EnableIfEither<Helper, uint8_t, int8_t> toHost(
			ConstLValueReference<Helper> number
		) {
			return number;
		}
	};

	template <typename Key>
	inline static Key toTarget( ConstLValueReference<Key> number) {
		return Implementation<Key>::toTarget(number);
	}

	template <typename Key>
	inline static Key toHost( ConstLValueReference<Key> number) {
		return Implementation<Key>::toHost(number);
	}
};

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
