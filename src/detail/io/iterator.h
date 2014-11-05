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
		inline Base* operator*() const {
			return this->index_;
		}

		inline Base*const* operator&() const {
			return &this->index_;
		}

		inline iterator& operator++() {
			this->index_ += Size;

			return *this;
		}

		inline iterator operator++(int) {
			iterator tmp(*this);

			this->operator++();

			return tmp;
		}

		inline iterator& operator--() {
			this->index_ -= Size;

			return *this;
		}

		inline iterator operator--(int) {
			iterator tmp(*this);

			this->operator--();

			return tmp;
		}

		inline iterator& operator+=(std::ptrdiff_t offset) {
			this->index_ += offset * Size;

			return *this;
		}

		inline iterator& operator-=(std::ptrdiff_t offset) {
			this->index_ -= offset * Size;

			return *this;
		}

		inline iterator operator+(std::ptrdiff_t offset) const {
			return iterator(*this) += offset;
		}

		inline std::ptrdiff_t operator-(
			dtl::const_lvalue_reference<iterator> src
		) const {
			return ( this->index_ - src.index_ ) / Size;
		}

		inline iterator operator-(std::ptrdiff_t offset) const {
			return iterator(*this) -= offset;
		}

		inline iterator operator[](std::ptrdiff_t offset) const {
			return *(this->operator+(offset));
		}

		friend inline iterator operator+(
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
