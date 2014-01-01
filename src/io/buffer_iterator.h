#ifndef BINARY_MAPPING_SRC_IO_BUFFER_ITERATOR_H_
#define BINARY_MAPPING_SRC_IO_BUFFER_ITERATOR_H_

#include <iterator>

namespace BinaryMapping {

template <size_t Size>
class BufferIterator : public std::iterator<std::random_access_iterator_tag,
                              uint8_t*,
                              off_t,
                              uint8_t**,
                              uint8_t*&> {
	public:
		BufferIterator(uint8_t* buffer):
			index_ptr_(buffer) { }

		inline bool operator==(const BufferIterator<Size>& src) const {
			return this->index_ptr_ == src.index_ptr_;
		}

		inline bool operator!=(const BufferIterator<Size>& src) const {
			return !(this == src);
		}

		inline uint8_t* operator*() const {
			return this->index_ptr_;
		}

		inline uint8_t*const* operator()() const {
			return &this->index_ptr_;
		}

		inline BufferIterator<Size>& operator++() {
			this->index_ptr_ += Size;

			return *this;
		}

		inline BufferIterator<Size>& operator--() {
			this->index_ptr_ -= Size;

			return *this;
		}

		inline BufferIterator<Size>& operator+=(off_t offset) {
			this->index_ptr_ += offset * Size;

			return *this;
		}

		inline BufferIterator<Size>& operator-=(off_t offset) {
			this->index_ptr_ -= offset * Size;

			return *this;
		}

		inline BufferIterator<Size> operator+(off_t offset) const {
			BufferIterator<Size> tmpIter(*this);
			tmpIter += offset;

			return tmpIter;
		}

		inline off_t operator-(const BufferIterator<Size>& src) const {
			return ( this->index_ptr_ - src.index_ptr_ ) / Size;
		}

		inline BufferIterator<Size> operator-(off_t offset) const {
			BufferIterator<Size> tmpIter(*this);
			tmpIter -= offset;

			return tmpIter;
		}

		inline BufferIterator<Size> operator[](off_t offset) const {
			return *(this->operator+(offset));
		}

		friend inline BufferIterator<Size> operator+(
			off_t offset,
			const BufferIterator<Size>& src) {
			BufferIterator<Size> tmpIter(src);
			tmpIter += offset;

			return tmpIter;
		}

	private:
		uint8_t* index_ptr_;

};


}

#endif  // BINARY_MAPPING_SRC_IO_BUFFER_ITERATOR_H_
