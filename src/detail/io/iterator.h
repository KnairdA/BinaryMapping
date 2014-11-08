#ifndef BINARY_MAPPING_SRC_DETAIL_IO_ITERATOR_H_
#define BINARY_MAPPING_SRC_DETAIL_IO_ITERATOR_H_

#include <iterator>

#include "detail/type/comparable.h"

namespace BinaryMapping {
namespace dtl {

template <
	typename Base,
	std::size_t Size
>
class Buffer::iterator : public std::iterator<std::random_access_iterator_tag,
                                              Base*>,
                         public Comparable<Base*> {
	public:
		Base* operator*() const {
			return this->index_;
		}

		Base*const* operator&() const {
			return &this->index_;
		}

		iterator& operator++() {
			this->index_ += Size;

			return *this;
		}

		iterator operator++(int) {
			iterator tmp(*this);

			this->operator++();

			return tmp;
		}

		iterator& operator--() {
			this->index_ -= Size;

			return *this;
		}

		iterator operator--(int) {
			iterator tmp(*this);

			this->operator--();

			return tmp;
		}

		iterator& operator+=(std::ptrdiff_t offset) {
			this->index_ += offset * Size;

			return *this;
		}

		iterator& operator-=(std::ptrdiff_t offset) {
			this->index_ -= offset * Size;

			return *this;
		}

		iterator operator+(std::ptrdiff_t offset) const {
			return iterator(*this) += offset;
		}

		std::ptrdiff_t operator-(
			dtl::const_lvalue_reference<iterator> src) const {
			return ( this->index_ - src.index_ ) / Size;
		}

		iterator operator-(std::ptrdiff_t offset) const {
			return iterator(*this) -= offset;
		}

		iterator operator[](std::ptrdiff_t offset) const {
			return *(this->operator+(offset));
		}

		friend iterator operator+(
			std::ptrdiff_t offset,
			dtl::const_lvalue_reference<iterator> src
		) {
			return iterator(src) += offset;
		}

	protected:
		friend Buffer;

		using Comparable<Base*>::Comparable;

};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_IO_ITERATOR_H_
