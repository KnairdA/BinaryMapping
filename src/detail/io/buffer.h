#ifndef BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_
#define BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_

#include <cstdint>
#include <stdexcept>

#include "buffer_iterator.h"

namespace BinaryMapping {
namespace dtl {

class Buffer {
	public:
		typedef std::uint8_t memory_type;
		typedef std::size_t size_type;
		typedef std::add_pointer<memory_type>::type pointer;
		typedef pointer_to_const<memory_type> const_pointer;

		template <size_type Size>
		using iterator_type = BufferIterator<memory_type, Size>;

		template <size_type Size>
		using const_iterator_type = BufferIterator<const memory_type, Size>;

		explicit Buffer(size_type size):
			data_(new memory_type[size]()),
			size_(size),
			owner_(true) { }

		Buffer(pointer const data, size_type size):
			data_(data),
			size_(size),
			owner_(false) { }

		~Buffer() {
			if ( this->owner_ ) {
				delete[] this->data_;
			}
		}

		inline const_pointer front() const {
			return this->data_;
		}

		inline const_pointer at(size_type index) const {
			return this->at<sizeof(memory_type)>(index);
		}

		template <size_type Size>
		inline const_pointer at(size_type index) const {
			if ( index < this->size<Size>() ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline const_pointer operator[] (size_type index) const {
			return this->data_ + index;
		}

		template <size_type Size>
		inline const_iterator_type<Size> begin() const {
			return const_iterator_type<Size>(this->data_);
		}

		template <size_type Size>
		inline const_iterator_type<Size> end() const {
			return const_iterator_type<Size>(
				this->data_ + this->size<Size>() * Size
			);
		}

		inline size_type size() const {
			return this->size_;
		}

		template <size_type Size>
		inline size_type size() const {
			return this->size_ / Size;
		}

		inline pointer front() {
			return this->data_;
		}

		inline pointer at(size_type index) {
			return this->at<sizeof(memory_type)>(index);
		}

		template <size_type Size>
		inline pointer at(size_type index) {
			if ( index < this->size<Size>() ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline pointer operator[] (size_type index) {
			return this->data_ + index;
		}

		template <size_type Size>
		inline iterator_type<Size> begin() {
			return iterator_type<Size>(this->data_);
		}

		template <size_type Size>
		inline iterator_type<Size> end() {
			return iterator_type<Size>(
				this->data_ + this->size<Size>() * Size
			);
		}

	private:
		pointer const data_;
		const size_type size_;
		const bool owner_;

};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_
