#ifndef BINARY_MAPPING_SRC_CUSTOM_BIT_FIELD_REFERENCE_H_
#define BINARY_MAPPING_SRC_CUSTOM_BIT_FIELD_REFERENCE_H_

namespace BinaryMapping {

template <size_t Size>
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
		reference(BitField<Size>& field, size_t index):
			field_(field),
			index_(index) { }

	private:
		BitField<Size>& field_;
		size_t index_;

};

}

#endif  // BINARY_MAPPING_SRC_CUSTOM_BIT_FIELD_REFERENCE_H_
