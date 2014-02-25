#ifndef BINARY_MAPPING_SRC_CONTAINER_H_
#define BINARY_MAPPING_SRC_CONTAINER_H_

#include <stdexcept>

#include "tuple/tuple.h"
#include "endianess/undefined.h"

#include "iterator.h"

namespace BinaryMapping {

template <typename Type>
class Container {
	public:
		typedef Type tuple_type;
		typedef typename Type::tuple_type value_tuple_type;
		typedef Iterator<Type> iterator_type;
		typedef Iterator<const Type> const_iterator_type;

		Container(Buffer* buffer):
			buffer_(buffer),
			tuple_count_(buffer->size<tuple_type::size>()) { }

		inline size_t size() const {
			return this->tuple_count_;
		}

		inline value_tuple_type operator[](size_t index) const {
			return static_cast<value_tuple_type>(tuple_type(
				this->buffer_->template at<tuple_type::size>(index)
			));
		}

		inline value_tuple_type at(size_t index) const {
			if ( index <= this->tuple_count_ ) {
				return this->operator[](index);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline value_tuple_type front() const {
			return static_cast<value_tuple_type>(
				tuple_type(this->buffer_->front())
			);
		}

		inline value_tuple_type back() const {
			return static_cast<value_tuple_type>(tuple_type(
				this->buffer_->template at<tuple_type::size>(
					this->tuple_count_ - 1
				)
			));
		}

		inline const_iterator_type begin() const {
			return const_iterator_type(
				this->buffer_,
				this->buffer_->template begin<tuple_type::size>()
			);
		}

		inline const_iterator_type end() const {
			return const_iterator_type(
				this->buffer_,
				this->buffer_->template end<tuple_type::size>()
			);
		}

		inline tuple_type operator[](size_t index) {
			return tuple_type(
				this->buffer_->template at<tuple_type::size>(index)
			);
		}

		inline tuple_type at(size_t index) {
			if ( index <= this->tuple_count_ ) {
				return this->operator[](index);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		inline tuple_type front() {
			return tuple_type(this->buffer_->front());
		}

		inline tuple_type back() {
			return tuple_type(
				this->buffer_->template at<tuple_type::size>(
					this->tuple_count_ - 1
				)
			);
		}

		inline iterator_type begin() {
			return iterator_type(
				this->buffer_,
				this->buffer_->template begin<tuple_type::size>()
			);
		}

		inline iterator_type end() {
			return iterator_type(
				this->buffer_,
				this->buffer_->template end<tuple_type::size>()
			);
		}

	private:
		Buffer* const buffer_;
		const size_t tuple_count_;

};

}

#endif  // BINARY_MAPPING_SRC_CONTAINER_H_
