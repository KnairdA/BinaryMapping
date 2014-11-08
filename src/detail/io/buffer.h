#ifndef BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_
#define BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_

#include <cstdint>
#include <stdexcept>

#include "detail/type/transformation.h"

namespace BinaryMapping {
namespace dtl {

class Buffer {
	template <typename, std::size_t> class iterator;

	public:
		typedef std::uint8_t memory_type;
		typedef std::size_t size_type;
		typedef std::add_pointer<memory_type>::type pointer;
		typedef pointer_to_const<memory_type> const_pointer;

		template <size_type Size>
		using iterator_type = iterator<memory_type, Size>;

		template <size_type Size>
		using const_iterator_type = iterator<const memory_type, Size>;

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

		const_pointer front() const {
			return this->data_;
		}

		const_pointer at(size_type index) const {
			return this->at<sizeof(memory_type)>(index);
		}

		template <size_type Size>
		const_pointer at(size_type index) const {
			if ( index < this->size<Size>() ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		const_pointer operator[] (size_type index) const {
			return this->data_ + index;
		}

		template <size_type Size>
		const_iterator_type<Size> begin() const {
			return const_iterator_type<Size>(this->data_);
		}

		template <size_type Size>
		const_iterator_type<Size> end() const {
			return const_iterator_type<Size>(
				this->data_ + this->size<Size>() * Size
			);
		}

		size_type size() const {
			return this->size_;
		}

		template <size_type Size>
		size_type size() const {
			return this->size_ / Size;
		}

		pointer front() {
			return this->data_;
		}

		pointer at(size_type index) {
			return this->at<sizeof(memory_type)>(index);
		}

		template <size_type Size>
		pointer at(size_type index) {
			if ( index < this->size<Size>() ) {
				return this->data_ + index * Size;
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		pointer operator[] (size_type index) {
			return this->data_ + index;
		}

		template <size_type Size>
		iterator_type<Size> begin() {
			return iterator_type<Size>(this->data_);
		}

		template <size_type Size>
		iterator_type<Size> end() {
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

#include "iterator.h"

#endif  // BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_H_
