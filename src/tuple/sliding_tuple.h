#ifndef BINARY_MAPPING_SRC_TUPLE_SLIDING_TUPLE_H_
#define BINARY_MAPPING_SRC_TUPLE_SLIDING_TUPLE_H_

#include "tuple.h" 

namespace BinaryMapping {

template <
	typename Endianess,
	typename... Types
>
class SlidingTuple : public Tuple<Endianess, Types...> {
	public:
		using Tuple<Endianess, Types...>::CarbonCopy;
		using Tuple<Endianess, Types...>::tuple_size;

		using Tuple<Endianess, Types...>::Tuple;

		inline void move(off_t index) {
			this->base_ptr_ = this->data_ + index * tuple_size;
		}

		inline SlidingTuple<Endianess, Types...>& operator++() {
			this->base_ptr_ += tuple_size;

			return *this;
		}

		inline SlidingTuple<Endianess, Types...>& operator--() {
			this->base_ptr_ -= tuple_size;

			return *this;
		}

};

template <typename... Types>
using PlainSlidingTuple = SlidingTuple<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TUPLE_SLIDING_TUPLE_H_
