#ifndef BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_
#define BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_

#include <cstdlib>
#include <stdexcept>

#include "buffer_iterator.h"

namespace BinaryMapping {
namespace dtl {

class Buffer {
	public:
		typedef std::add_pointer<uint8_t>::type memory_type;
		typedef pointer_to_const<uint8_t> const_memory_type;

		template <size_t Size>
		using iterator_type = BufferIterator<uint8_t, Size>;

		template <size_t Size>
		using const_iterator_type = BufferIterator<const uint8_t, Size>;

		explicit Buffer(size_t size):
			data_(reinterpret_cast<uint8_t*>(
				std::calloc(size, sizeof(uint8_t))
			)),
			size_(size),
			owner_(true) { }

		Buffer(uint8_t*const data, size_t size):
			data_(data),
			size_(size),
			owner_(false) { }

		~Buffer() {
			if ( this->owner_ ) {
				std::free(this->data_);
			}
		}

		inline const_memory_type front() const {
			return this->data_;
		}

		inline const_memory_type at(size_t index) const {
			return this->at<sizeof(uint8_t)>(index);
		}

		template <size_t Size>
		inline const_memory_type at(size_t index) const {
			if ( index < this->size<Size>() ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline const_memory_type operator[] (size_t index) const {
			return this->data_ + index;
		}

		template <size_t Size>
		inline const_iterator_type<Size> begin() const {
			return const_iterator_type<Size>(this->data_);
		}

		template <size_t Size>
		inline const_iterator_type<Size> end() const {
			return const_iterator_type<Size>(
				this->data_ + this->size<Size>() * Size
			);
		}

		inline size_t size() const {
			return this->size_;
		}

		template <size_t Size>
		inline size_t size() const {
			return this->size_ / Size;
		}

		inline memory_type front() {
			return this->data_;
		}

		inline memory_type at(size_t index) {
			return this->at<sizeof(uint8_t)>(index);
		}

		template <size_t Size>
		inline memory_type at(size_t index) {
			if ( index < this->size<Size>() ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline memory_type operator[] (size_t index) {
			return this->data_ + index;
		}

		template <size_t Size>
		inline iterator_type<Size> begin() {
			return iterator_type<Size>(this->data_);
		}

		template <size_t Size>
		inline iterator_type<Size> end() {
			return iterator_type<Size>(
				this->data_ + this->size<Size>() * Size
			);
		}

	private:
		memory_type const data_;
		const size_t size_;

		const bool owner_;
};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_
