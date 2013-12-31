#ifndef BINARY_MAPPING_SRC_CONTAINER_H_
#define BINARY_MAPPING_SRC_CONTAINER_H_

#include <stdexcept>

#include "tuple/tuple.h"
#include "tuple/sliding_tuple.h"
#include "endianess/undefined.h"

#include "iterator.h"

namespace BinaryMapping {

template<
	typename Endianess,
	typename... Types
>
class Container {
	public:
		typedef Tuple<Endianess, Types...> type;
		typedef Iterator<Endianess, Types...> iterator_type;

		Container(Buffer* buffer):
			buffer_(buffer),
			tuple_count_(buffer->size<type::tuple_size>()) { }

		inline size_t size() const {
			return this->tuple_count_;
		}

		inline type operator[](size_t index) {
			return type(
				this->buffer_->template at<type::tuple_size>(index)
			);
		}

		inline typename type::CarbonCopy operator[](size_t index) const {
			return type(
				this->buffer_->template at<type::tuple_size>(index)
			).carbonCopy();
		}

		inline type at(size_t index) {
			if ( index <= this->tuple_count_ ) {
				return this->operator[](index);
			} else {
				throw std::out_of_range("container range violated");
			}
		}

		inline typename type::CarbonCopy at(size_t index) const {
			if ( index <= this->tuple_count_ ) {
				return this->operator[](index);
			} else {
				throw std::out_of_range("container range violated");
			}
		}

		inline type front() {
			return type(this->buffer_->begin());
		}

		inline typename type::CarbonCopy front() const {
			return type(this->buffer_->begin()).carbonCopy();
		}

		inline type back() {
			return type(
				this->buffer_->template at<type::tuple_size>(this->tuple_count_ - 1)
			);
		}

		inline typename type::CarbonCopy back() const {
			return type(
				this->buffer_->template at<type::tuple_size>(this->tuple_count_ - 1)
			).carbonCopy();
		}

		inline iterator_type begin() const {
			return iterator_type(this->buffer_);
		}

	private:
		Buffer* const buffer_;
		const size_t tuple_count_;

};

template <typename... Types>
using PlainContainer = Container<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_CONTAINER_H_
