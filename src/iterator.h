#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <iterator>

#include "tuple/sliding_tuple.h"

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

		Iterator(const Buffer& buffer):
			data_(buffer.data),
			size_(buffer.size),
			tuple_count_(size_ / type::tuple_size),
			tuple_(buffer),
			index_(0) { }

		Iterator(uint8_t* data, size_t size):
			data_(data),
			size_(size),
			tuple_count_(size_ / type::tuple_size),
			tuple_(data),
			index_(0) { }

		inline bool operator==(const Iterator<Endianess, Types...>& src) const {
			return this->data_  == src.data_ &&
			       this->size_  == src.size_ &&
			       this->index_ == src.index_;
		}

		inline bool operator!=(const Iterator<Endianess, Types...>& src) const {
			return !(this == src);
		}

		inline type operator*() {
			return type(this->tuple_.data());
		}

		inline Iterator<Endianess, Types...>& operator++() {
			if ( this->index_ < this->tuple_count_ ) {
				++this->tuple_;
				++this->index_;
			}

			return *this;
		}

		inline Iterator<Endianess, Types...>& operator--() {
			if ( this->index_ > 0 ) {
				--this->tuple_;
				--this->index_;
			}

			return *this;
		}

		inline Iterator<Endianess, Types...>& operator+=(off_t offset) {
			if ( this->index_ + offset <= this->tuple_count_ ) {
				this->tuple_.move(this->index_ + offset);
				this->index_ += offset;
			}

			return *this;
		}

		inline Iterator<Endianess, Types...>& operator-=(off_t offset) {
			if ( this->index_ - offset >= 0 ) {
				this->tuple_.move(this->index_ - offset);
				this->index_ -= offset;
			}

			return *this;
		}

	private:
		uint8_t* const data_;
		const size_t size_;
		const off_t tuple_count_;

		SlidingTuple<Endianess, Types...> tuple_;
		off_t index_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
