#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <cstddef>
#include <iterator>

#include "detail/comparable.h"
#include "detail/io/iterator.h"

namespace BinaryMapping {

template <
	typename Base,
	typename Type
>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      Type&,
                                      std::ptrdiff_t,
                                      Type*>,
                 public dtl::Comparable<Base> {
	public:
		typedef Type element_type;

		explicit Iterator(Base&& index):
			dtl::Comparable<Base>(index),
			element_(&this->index_) { }

		inline element_type& operator*() {
			return this->element_;
		}

		inline typename element_type::value_type operator*() const {
			return this->element_;
		}

		inline Iterator& operator++() {
			++this->index_;

			return *this;
		}

		inline Iterator operator++(int) {
			Iterator tmp(*this);

			this->operator++();

			return tmp;
		}

		inline Iterator& operator--() {
			--this->index_;

			return *this;
		}

		inline Iterator operator--(int) {
			Iterator tmp(*this);

			this->operator--();

			return tmp;
		}

		inline Iterator& operator+=(std::ptrdiff_t offset) {
			this->index_ += offset;

			return *this;
		}

		inline Iterator& operator-=(std::ptrdiff_t offset) {
			this->index_ -= offset;

			return *this;
		}

		inline Iterator operator+(std::ptrdiff_t offset) const {
			return Iterator(*this) += offset;
		}

		inline std::ptrdiff_t operator-(
			dtl::const_lvalue_reference<Iterator> src
		) const {
			return this->index_ - src.index_;
		}

		inline Iterator operator-(std::ptrdiff_t offset) const {
			return Iterator(*this) -= offset;
		}

		inline Iterator operator[](std::ptrdiff_t offset) const {
			return *(this->operator+(offset));
		}

		friend inline Iterator operator+(
			std::ptrdiff_t offset,
			dtl::const_lvalue_reference<Iterator> src
		) {
			return Iterator(src) += offset;
		}

	private:
		element_type element_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
