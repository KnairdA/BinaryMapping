#ifndef BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
#define BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_

namespace BinaryMapping {

struct LittleEndian {
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
uint64_t LittleEndian::toTarget<uint64_t>(const uint64_t& number) {
	return htole64(number);
}

template <>
uint32_t LittleEndian::toTarget<uint32_t>(const uint32_t& number) {
	return htole32(number);
}

template <>
uint16_t LittleEndian::toTarget<uint16_t>(const uint16_t& number) {
	return htole16(number);
}

template <>
uint8_t LittleEndian::toTarget<uint8_t>(const uint8_t& number) {
	return number;
}

template <>
uint64_t LittleEndian::toHost<uint64_t>(const uint64_t& number) {
	return le64toh(number);
}

template <>
uint32_t LittleEndian::toHost<uint32_t>(const uint32_t& number) {
	return le32toh(number);
}

template <>
uint16_t LittleEndian::toHost<uint16_t>(const uint16_t& number) {
	return le16toh(number);
}

template <>
uint8_t LittleEndian::toHost<uint8_t>(const uint8_t& number) {
	return number;
}

}

#endif  // BINARY_MAPPING_SRC_ENDIANESS_LITTLE_H_
