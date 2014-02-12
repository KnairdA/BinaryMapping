#ifndef BINARY_MAPPING_SRC_DETAIL_BASE_PTR_H_
#define BINARY_MAPPING_SRC_DETAIL_BASE_PTR_H_

namespace BinaryMapping {
namespace detail {

struct BasePtr {
	enum class Tag : uint8_t {
		Direct,
		Indirect
	};

	BasePtr(uint8_t*const ptr):
		direct(ptr),
		tag(Tag::Direct) { }

	BasePtr(uint8_t*const* ptr):
		indirect(ptr),
		tag(Tag::Indirect) { }

	inline uint8_t*const* get() const {
		switch ( this->tag ) {
			case Tag::Direct:   return &this->direct;
			case Tag::Indirect: return this->indirect;
			default:            return nullptr;
		}
	}

	union {
		uint8_t*const  direct;
		uint8_t*const* indirect; 
	};

	const Tag tag;
};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_BASE_PTR_H_
