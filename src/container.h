#ifndef BINARY_MAPPING_SRC_CONTAINER_H_
#define BINARY_MAPPING_SRC_CONTAINER_H_

#include <stdexcept>

#include "tuple/tuple.h"
#include "endianess/undefined.h"

#include "iterator.h"

namespace BinaryMapping {

template<
	typename Endianess,
	typename... Types
>
class Container {
	public:
		typedef Tuple<Endianess, Types...> tuple_type;
		typedef Iterator<Endianess, Types...> iterator_type;

		Container(Buffer* buffer):
			buffer_(buffer),
			tuple_count_(buffer->size<tuple_type::size>()) { }

		inline size_t size() const {
			return this->tuple_count_;
		}

		inline tuple_type operator[](size_t index) {
			return tuple_type(
				this->buffer_->template at<tuple_type::size>(index)
			);
		}

		inline typename tuple_type::carbon_copy operator[](size_t index) const {
			return tuple_type(
				this->buffer_->template at<tuple_type::size>(index)
			).carbonCopy();
		}

		inline tuple_type at(size_t index) {
			if ( index <= this->tuple_count_ ) {
				return this->operator[](index);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline typename tuple_type::carbon_copy at(size_t index) const {
			if ( index <= this->tuple_count_ ) {
				return this->operator[](index);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline tuple_type front() {
			return tuple_type(this->buffer_->front());
		}

		inline typename tuple_type::carbon_copy front() const {
			return tuple_type(this->buffer_->front()).carbonCopy();
		}

		inline tuple_type back() {
			return tuple_type(
				this->buffer_->template at<tuple_type::size>(
					this->tuple_count_ - 1
				)
			);
		}

		inline typename tuple_type::carbon_copy back() const {
			return tuple_type(
				this->buffer_->template at<tuple_type::size>(
					this->tuple_count_ - 1
				)
			).carbonCopy();
		}

		inline iterator_type begin() const {
			return iterator_type(
				this->buffer_,
				this->buffer_->template begin<tuple_type::size>()
			);
		}

		inline iterator_type end() const {
			return iterator_type(
				this->buffer_,
				this->buffer_->template end<tuple_type::size>()
			);
		}

	private:
		Buffer* const buffer_;
		const size_t tuple_count_;

};

template <typename... Types>
using PlainContainer = Container<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_CONTAINER_H_
