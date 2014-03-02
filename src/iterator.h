#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <iterator>

#include "detail/comparable.h"
#include "detail/io/buffer_iterator.h"

namespace BinaryMapping {

template <typename Type> class Container;

template <typename Type>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      Type&,
                                      off_t,
                                      Type*>,
                 public dtl::Comparable<dtl::BufferIterator<Type::size>> {
	public:
		typedef Type element_type;
		typedef typename Type::value_type element_value_type;

		inline element_type& operator*() {
			return this->element_;
		}

		inline element_value_type operator*() const {
			return static_cast<element_value_type>(
				this->element_
			);
		}

		inline Iterator& operator++() {
			if ( this->index_ < this->end_ ) {
				++this->index_;
			}

			return *this;
		}

		inline Iterator operator++(int) {
			Iterator tmp(*this);

			this->operator++();

			return tmp;
		}

		inline Iterator& operator--() {
			if ( this->index_ > this->begin_ ) {
				--this->index_;
			}

			return *this;
		}

		inline Iterator operator--(int) {
			Iterator tmp(*this);

			this->operator--();

			return tmp;
		}

		inline Iterator& operator+=(off_t offset) {
			if ( this->index_ + offset < this->end_ ) {
				this->index_ += offset;
			}

			return *this;
		}

		inline Iterator& operator-=(off_t offset) {
			if ( this->index_ - offset >= this->begin_ ) {
				this->index_ -= offset;
			}

			return *this;
		}

		inline Iterator operator+(off_t offset) const {
			return Iterator(*this) += offset;
		}

		inline off_t operator-(
			dtl::const_lvalue_reference<Iterator> src
		) const {
			return this->index_ - src.index_;
		}

		inline Iterator operator-(off_t offset) const {
			return Iterator(*this) -= offset;
		}

		inline Iterator operator[](off_t offset) const {
			return *(this->operator+(offset));
		}

		friend inline Iterator operator+(
			off_t offset,
			dtl::const_lvalue_reference<Iterator> src
		) {
			return Iterator(src) += offset;
		}

	protected:
		friend Container<typename std::remove_cv<Type>::type>;
		friend Container<typename std::add_const<Type>::type>;

		Iterator(dtl::BufferIterator<element_type::size>&& index,
		         const dtl::BufferIterator<element_type::size>&& begin,
		         const dtl::BufferIterator<element_type::size>&& end):
			dtl::Comparable<dtl::BufferIterator<element_type::size>>(index),
			element_(&this->index_),
			begin_(begin),
			end_(end) { }

	private:
		element_type element_;

		const dtl::BufferIterator<element_type::size> begin_;
		const dtl::BufferIterator<element_type::size> end_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
