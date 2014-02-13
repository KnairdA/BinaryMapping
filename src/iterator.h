#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <iterator>

#include "detail/comparable.h"

namespace BinaryMapping {

template <typename Type>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      Type&,
                                      off_t,
                                      Type*,
                                      Type&>,
                 public dtl::Comparable<BufferIterator<Type::size>> {
	public:
		typedef Type tuple_type;

		Iterator(Buffer* buffer, BufferIterator<tuple_type::size>&& iter):
			dtl::Comparable<BufferIterator<tuple_type::size>>(
				std::move(iter)
			),
			buffer_(buffer),
			tuple_(this->index_),
			begin_(buffer_->begin<tuple_type::size>()),
			end_(buffer_->end<tuple_type::size>()) { }

		inline tuple_type& operator*() {
			return this->tuple_;
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
			Iterator tmpIter(*this);
			tmpIter += offset;

			return tmpIter;
		}

		inline off_t operator-(const Iterator& src) const {
			return this->index_ - src.index_;
		}

		inline Iterator operator-(off_t offset) const {
			Iterator tmpIter(*this);
			tmpIter -= offset;

			return tmpIter;
		}

		inline Iterator operator[](off_t offset) const {
			return *(this->operator+(offset));
		}

		friend inline Iterator operator+(
			off_t offset,
			const Iterator& src) {
			Iterator tmpIter(src);
			tmpIter += offset;

			return tmpIter;
		}

	private:
		Buffer* const buffer_;
		tuple_type tuple_;

		const BufferIterator<tuple_type::size> begin_;
		const BufferIterator<tuple_type::size> end_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
