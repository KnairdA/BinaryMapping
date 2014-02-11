#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <iterator>

namespace BinaryMapping {

template <typename Type>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      Type&,
                                      off_t,
                                      Type*,
                                      Type&> {
	public:
		typedef Type tuple_type;

		Iterator(Buffer* buffer, BufferIterator<tuple_type::size>&& iter):
			buffer_(buffer),
			iter_(  std::move(iter)),
			tuple_( iter_),
			begin_( buffer_->begin<tuple_type::size>()),
			end_(   buffer_->end<tuple_type::size>()) { }

		inline bool operator==(const Iterator& src) const {
			return this->iter_  == src.iter_;
		}

		inline bool operator!=(const Iterator& src) const {
			return !(*this == src);
		}

		inline bool operator<(const Iterator& src) const {
			return this->iter_ < src.iter_;
		}

		inline bool operator>(const Iterator& src) const {
			return this->iter_ > src.iter_;
		}

		inline bool operator<=(const Iterator& src) const {
			return !this->operator>(src);
		}

		inline bool operator>=(const Iterator& src) const {
			return !this->operator<(src);
		}

		inline tuple_type& operator*() {
			return this->tuple_;
		}

		inline Iterator& operator++() {
			if ( this->iter_ < this->end_ ) {
				++this->iter_;
			}

			return *this;
		}

		inline Iterator operator++(int) {
			Iterator tmp(*this);

			this->operator++();

			return tmp;
		}

		inline Iterator& operator--() {
			if ( this->iter_ > this->begin_ ) {
				--this->iter_;
			}

			return *this;
		}

		inline Iterator operator--(int) {
			Iterator tmp(*this);

			this->operator--();

			return tmp;
		}

		inline Iterator& operator+=(off_t offset) {
			if ( this->iter_ + offset < this->end_ ) {
				this->iter_ += offset;
			}

			return *this;
		}

		inline Iterator& operator-=(off_t offset) {
			if ( this->iter_ - offset >= this->begin_ ) {
				this->iter_ -= offset;
			}

			return *this;
		}

		inline Iterator operator+(off_t offset) const {
			Iterator tmpIter(*this);
			tmpIter += offset;

			return tmpIter;
		}

		inline off_t operator-(const Iterator& src) const {
			return this->iter_ - src.iter_;
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

		BufferIterator<tuple_type::size> iter_;
		tuple_type tuple_;

		const BufferIterator<tuple_type::size> begin_;
		const BufferIterator<tuple_type::size> end_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
