#ifndef BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_ITERATOR_H_
#define BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_ITERATOR_H_

#include <iterator>

#include "detail/comparable.h"

namespace BinaryMapping {
namespace dtl {

template <
	typename Base,
	size_t Size
>
struct BufferIterator : public std::iterator<std::random_access_iterator_tag,
                                             Base*,
                                             off_t>,
                        public Comparable<Base*> {
	using Comparable<Base*>::Comparable;

	inline Base* operator*() const {
		return this->index_;
	}

	inline Base*const* operator&() const {
		return &this->index_;
	}

	inline BufferIterator& operator++() {
		this->index_ += Size;

		return *this;
	}

	inline BufferIterator operator++(int) {
		BufferIterator tmp(*this);

		this->operator++();

		return tmp;
	}

	inline BufferIterator& operator--() {
		this->index_ -= Size;

		return *this;
	}

	inline BufferIterator operator--(int) {
		BufferIterator tmp(*this);

		this->operator--();

		return tmp;
	}

	inline BufferIterator& operator+=(off_t offset) {
		this->index_ += offset * Size;

		return *this;
	}

	inline BufferIterator& operator-=(off_t offset) {
		this->index_ -= offset * Size;

		return *this;
	}

	inline BufferIterator operator+(off_t offset) const {
		return BufferIterator(*this) += offset;
	}

	inline off_t operator-(
		dtl::const_lvalue_reference<BufferIterator> src
	) const {
		return ( this->index_ - src.index_ ) / Size;
	}

	inline BufferIterator operator-(off_t offset) const {
		return BufferIterator(*this) -= offset;
	}

	inline BufferIterator operator[](off_t offset) const {
		return *(this->operator+(offset));
	}

	friend inline BufferIterator operator+(
		off_t offset,
		dtl::const_lvalue_reference<BufferIterator> src
	) {
		return BufferIterator(src) += offset;
	}
};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_IO_BUFFER_ITERATOR_H_