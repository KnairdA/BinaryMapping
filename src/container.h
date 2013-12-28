#ifndef BINARY_MAPPING_SRC_CONTAINER_H_
#define BINARY_MAPPING_SRC_CONTAINER_H_

#include <stdexcept>

#include "tuple/tuple.h"
#include "tuple/sliding_tuple.h"
#include "endianess/undefined.h"

namespace BinaryMapping {

template<
	typename Endianess,
	typename... Types
>
class Container {
	public:
		typedef Tuple<Endianess, Types...> type;

		Container(const BufferGuard& buffer):
			data_(buffer.data),
			size_(buffer.size),
			tuple_count_(size_ / type::tuple_size),
			tuple_(buffer) { }

		inline size_t size() const {
			return this->tuple_count_;
		}

		inline typename type::CarbonCopy at(size_t index) const {
			if ( index <= this->tuple_count_ ) {
				this->tuple_.move(index);

				return this->tuple_.carbonCopy();
			} else {
				throw std::out_of_range("container range violated");
			}
		}

		inline type at(size_t index) {
			if ( index <= this->tuple_count_ ) {
				return type(
					this->data_ + index * type::tuple_size
				);
			} else {
				throw std::out_of_range("container range violated");
			}
		}

		inline typename type::CarbonCopy operator[] (size_t index) const {
			this->tuple_.move(index);

			return this->tuple_.carbonCopy();
		}

		inline type operator[] (size_t index) {
			return type(
				this->data_ + index * type::tuple_size
			);
		}

		inline typename type::CarbonCopy front() const {
			this->tuple_.move(0);

			return this->tuple_.carbonCopy();
		}

		inline type front() {
			return type(this->data_);
		}

		inline typename type::CarbonCopy back() const {
			this->tuple_.move(this->tuple_count_ - 1);

			return this->tuple_.carbonCopy();
		}

		inline type back() {
			return type(
				this->data_ + (this->tuple_count_ - 1) * type::tuple_size
			);
		}

		inline type* data() const {
			return static_cast<type*>(&this->tuple_);
		}

	private:
		uint8_t* const data_;
		const size_t size_;

		const size_t tuple_count_;
		mutable SlidingTuple<Endianess, Types...> tuple_;

};

template <typename... Types>
using PlainContainer = Container<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_CONTAINER_H_
