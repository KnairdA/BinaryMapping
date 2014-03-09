#ifndef BINARY_MAPPING_SRC_TYPE_BIT_FIELD_REFERENCE_H_
#define BINARY_MAPPING_SRC_TYPE_BIT_FIELD_REFERENCE_H_

#include <cstddef>

namespace BinaryMapping {

template <std::size_t Size>
class BitField<Size>::reference {
	friend BitField<Size>;

	public:
		inline void operator=(bool value) {
			this->field_.set(this->index_, value);
		}

		inline void flip() {
			this->field_.flip(this->index_);
		}

		inline operator bool() const {
			return this->field_.test(this->index_);
		}

		inline bool operator~() const {
			return !this->operator bool();
		}

	protected:
		reference(BitField<Size>& field, std::size_t index):
			index_(index),
			field_(field) { }

	private:
		const std::size_t index_;
		BitField<Size>& field_;

};

}

#endif  // BINARY_MAPPING_SRC_TYPE_BIT_FIELD_REFERENCE_H_
