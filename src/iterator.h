#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <iterator>

namespace BinaryMapping {

template<
	typename Endianess,
	typename... Types
>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                      Tuple<Endianess, Types...>,
                                      off_t,
                                      Tuple<Endianess, Types...>*,
                                      Tuple<Endianess, Types...>&> {
	public:
		typedef Tuple<Endianess, Types...> type;

		Iterator(Buffer* buffer):
			buffer_(buffer),
			begin_(buffer_->begin<type::tuple_size>()),
			end_(buffer_->end<type::tuple_size>()),
			iter_(buffer_->begin<type::tuple_size>()),
			tuple_(iter_) { }

		Iterator(Buffer* buffer, size_t index):
			buffer_(buffer),
			begin_(buffer_->begin<type::tuple_size>()),
			end_(buffer_->end<type::tuple_size>()),
			iter_(buffer_->at<type::tuple_size>(index)),
			tuple_(iter_) { }

		inline bool operator==(const Iterator<Endianess, Types...>& src) const {
			return this->iter_  == src.iter_;
		}

		inline bool operator!=(const Iterator<Endianess, Types...>& src) const {
			return !(*this == src);
		}

		inline bool operator<(const Iterator<Endianess, Types...>& src) const {
			return this->iter_ < src.iter_;
		}

		inline bool operator>(const Iterator<Endianess, Types...>& src) const {
			return this->iter_ > src.iter_;
		}

		inline bool operator<=(const Iterator<Endianess, Types...>& src) const {
			return !this->operator>(src);
		}

		inline bool operator>=(const Iterator<Endianess, Types...>& src) const {
			return !this->operator<(src);
		}

		inline type operator*() {
			return type(*this->iter_);
		}

		inline Iterator<Endianess, Types...>& operator++() {
			if ( this->iter_ < this->end_ ) {
				++this->iter_;
			}

			return *this;
		}

		inline Iterator<Endianess, Types...>& operator--() {
			if ( this->iter_ > this->begin_ ) {
				--this->iter_;
			}

			return *this;
		}

		inline Iterator<Endianess, Types...>& operator+=(off_t offset) {
			if ( this->iter_ + offset < this->end_ ) {
				this->iter_ += offset;
			}

			return *this;
		}

		inline Iterator<Endianess, Types...>& operator-=(off_t offset) {
			if ( this->iter_ - offset >= this->begin_ ) {
				this->iter_ -= offset;
			}

			return *this;
		}

	private:
		Buffer* const buffer_;

		BufferIterator<type::tuple_size> begin_;
		BufferIterator<type::tuple_size> end_;
		BufferIterator<type::tuple_size> iter_;

		Tuple<Endianess, Types...> tuple_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
