#ifndef BINARY_MAPPING_SRC_IO_BUFFER_H_
#define BINARY_MAPPING_SRC_IO_BUFFER_H_

#include <stdexcept>

#include "buffer_iterator.h"

namespace BinaryMapping {

class Buffer {
	public:
		Buffer(uint8_t* d, size_t s):
			data_(d),
			size_(s),
			owner_(true) { }

		Buffer(const Buffer& src):
			data_(src.data_),
			size_(src.size_),
			owner_(false) { }

		~Buffer() {
			if ( this->owner_ ) {
				std::free(this->data_);
			}
		}

		inline uint8_t* begin() const {
			return this->data_;
		}

		template <size_t Size>
		inline uint8_t* at(size_t index) const {
			if ( index < this->size<Size> ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline uint8_t* operator[] (size_t index) const {
			return this->data_ + index;
		}

		template <size_t Size>
		inline BufferIterator<Size> begin() const {
			return BufferIterator<Size>(this->data_);
		}

		template <size_t Size>
		inline BufferIterator<Size> end() const {
			return BufferIterator<Size>(
				this->data_ + this->size<Size>() * Size
			);
		}

		template <size_t Size>
		inline size_t size() const {
			return this->size_ / Size;
		}

	private:
		uint8_t* const data_;
		const size_t size_;

		const bool owner_;
};

}

#endif  // BINARY_MAPPING_SRC_IO_BUFFER_H_
