#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <iterator>

namespace BinaryMapping {

template<
	typename Endianess,
	typename... Types
>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      Tuple<Endianess, Types...>&,
                                      off_t,
                                      Tuple<Endianess, Types...>*,
                                      Tuple<Endianess, Types...>&> {
	typedef Iterator<Endianess, Types...> iterator_type;

	public:
		typedef Tuple<Endianess, Types...> tuple_type;

		Iterator(Buffer* buffer):
			buffer_(buffer),
			begin_( buffer_->begin<tuple_type::size>()),
			end_(   buffer_->end<tuple_type::size>()),
			iter_(  buffer_->begin<tuple_type::size>()),
			tuple_( iter_) { }

		Iterator(Buffer* buffer, size_t index):
			buffer_(buffer),
			begin_( buffer_->begin<tuple_type::size>()),
			end_(   buffer_->end<tuple_type::size>()),
			iter_(  (*buffer_)[index * tuple_type::size]),
			tuple_( iter_) { }

		inline bool operator==(const iterator_type& src) const {
			return this->iter_  == src.iter_;
		}

		inline bool operator!=(const iterator_type& src) const {
			return !(*this == src);
		}

		inline bool operator<(const iterator_type& src) const {
			return this->iter_ < src.iter_;
		}

		inline bool operator>(const iterator_type& src) const {
			return this->iter_ > src.iter_;
		}

		inline bool operator<=(const iterator_type& src) const {
			return !this->operator>(src);
		}

		inline bool operator>=(const iterator_type& src) const {
			return !this->operator<(src);
		}

		inline tuple_type& operator*() {
			return this->tuple_;
		}

		inline iterator_type& operator++() {
			if ( this->iter_ < this->end_ ) {
				++this->iter_;
			}

			return *this;
		}

		inline iterator_type& operator--() {
			if ( this->iter_ > this->begin_ ) {
				--this->iter_;
			}

			return *this;
		}

		inline iterator_type& operator+=(off_t offset) {
			if ( this->iter_ + offset < this->end_ ) {
				this->iter_ += offset;
			}

			return *this;
		}

		inline iterator_type& operator-=(off_t offset) {
			if ( this->iter_ - offset >= this->begin_ ) {
				this->iter_ -= offset;
			}

			return *this;
		}

		inline iterator_type operator+(off_t offset) const {
			iterator_type tmpIter(*this);
			tmpIter += offset;

			return tmpIter;
		}

		inline off_t operator-(const iterator_type& src) const {
			return this->iter_ - src.iter_;
		}

		inline iterator_type operator-(off_t offset) const {
			iterator_type tmpIter(*this);
			tmpIter -= offset;

			return tmpIter;
		}

		inline iterator_type operator[](off_t offset) const {
			return *(this->operator+(offset));
		}

		friend inline iterator_type operator+(
			off_t offset,
			const iterator_type& src) {
			iterator_type tmpIter(src);
			tmpIter += offset;

			return tmpIter;
		}

	private:
		Buffer* const buffer_;

		BufferIterator<tuple_type::size> begin_;
		BufferIterator<tuple_type::size> end_;
		BufferIterator<tuple_type::size> iter_;

		Tuple<Endianess, Types...> tuple_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
