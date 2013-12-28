#ifndef BINARY_MAPPING_SRC_CONTAINER_H_
#define BINARY_MAPPING_SRC_CONTAINER_H_

#include <stdexcept>

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

		inline typename type::CarbonCopy operator[] (size_t index) const {
			this->tuple_.move(index);

			return this->tuple_.carbonCopy();
		}

		inline typename type::CarbonCopy front() const {
			this->tuple_.move(0);

			return this->tuple_.carbonCopy();
		}

		inline typename type::CarbonCopy back() const {
			this->tuple_.move(this->tuple_count_);

			return this->tuple_.carbonCopy();
		}

		inline type* data() {
			return &this->tuple_;
		}

	private:
		uint8_t* const data_;
		const size_t size_;

		const size_t tuple_count_;
		type tuple_;

};

template <typename... Types>
using PlainContainer = Container<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_CONTAINER_H_
