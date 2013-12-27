#ifndef BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
#define BINARY_MAPPING_SRC_ENDIANESS_BIG_H_

namespace BinaryMapping {

struct BigEndian {
	template <typename Key>
	static inline Key toTarget(typename std::add_lvalue_reference<
		typename std::add_const<Key>::type
	>::type);

	template <typename Key>
	static inline Key toHost(typename std::add_lvalue_reference<
		typename std::add_const<Key>::type
	>::type);
};

template <>
uint64_t BigEndian::toTarget<uint64_t>(const uint64_t& number) {
	return htobe64(number);
}

template <>
uint32_t BigEndian::toTarget<uint32_t>(const uint32_t& number) {
	return htobe32(number);
}

template <>
uint16_t BigEndian::toTarget<uint16_t>(const uint16_t& number) {
	return htobe16(number);
}

template <>
uint8_t BigEndian::toTarget<uint8_t>(const uint8_t& number) {
	return number;
}

template <>
uint64_t BigEndian::toHost<uint64_t>(const uint64_t& number) {
	return be64toh(number);
}

template <>
uint32_t BigEndian::toHost<uint32_t>(const uint32_t& number) {
	return be32toh(number);
}

template <>
uint16_t BigEndian::toHost<uint16_t>(const uint16_t& number) {
	return be16toh(number);
}

template <>
uint8_t BigEndian::toHost<uint8_t>(const uint8_t& number) {
	return number;
}

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_BIG_H_
