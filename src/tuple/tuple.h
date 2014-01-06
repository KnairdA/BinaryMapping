#ifndef BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
#define BINARY_MAPPING_SRC_TUPLE_TUPLE_H_

#include <tuple>

#include "utility.h" 

#include "mapper.h" 
#include "weigher.h" 
#include "tuple_carbon_copy.h" 
#include "relative_pointer.h" 

#include "io/buffer.h" 

#include "endianess/serializer.h" 
#include "endianess/in_place_sorter.h" 
#include "endianess/out_of_place_sorter.h" 
#include "endianess/undefined.h" 

namespace BinaryMapping {

template <
	typename Endianess,
	typename... Types
>
class Tuple {
	public:
		typedef TupleCarbonCopy<Types...> carbon_copy;
		typedef std::tuple<RelativePointer<uint8_t, Types>...> tuple_type;

		static const size_t size = TupleWeigher::size<tuple_type>();

		Tuple(Buffer* buffer):
			base_ptr_(buffer->front()),
			tuple_(TupleMapper::construct<tuple_type>(&this->base_ptr_)) { }

		Tuple(uint8_t* data):
			base_ptr_(data),
			tuple_(TupleMapper::construct<tuple_type>(&this->base_ptr_)) { }

		Tuple(const BufferIterator<size>& iter):
			base_ptr_(nullptr),
			tuple_(TupleMapper::construct<tuple_type>(iter())) { }

		template <size_t Index> inline typename
		std::tuple_element<Index, tuple_type>::type::element_type get() const {
			return OutOfPlaceSorter<Endianess>::sort(
				*std::get<Index>(this->tuple_)
			);
		}

		template <size_t Index>
		inline void set(ConstLValueReference<
			typename std::tuple_element<Index, tuple_type>::type::element_type
		> value) {
			InPlaceSorter<Endianess>::template mix<
				typename std::tuple_element<Index, tuple_type>::type::element_type
			>(
				std::get<Index>(this->tuple_).get(),
				value
			);
		}

		template <typename CustomOrder>
		inline void serialize() {
			static_assert(
				std::is_same<Endianess, UndefinedEndian>::value,
				"Endianess must be UndefinedEndian to use serialize<*>()"
			);

			Serializer<InPlaceSorter<CustomOrder>>::serialize(this->tuple_);
		}

		template <typename CustomOrder>
		inline void deserialize() {
			static_assert(
				std::is_same<Endianess, UndefinedEndian>::value,
				"Endianess must be UndefinedEndian to use deserialize<*>()"
			);

			Serializer<InPlaceSorter<CustomOrder>>::deserialize(this->tuple_);
		}

		carbon_copy carbonCopy() const {
			return carbon_copy(*this);
		}

	protected:
		uint8_t* base_ptr_;
		const tuple_type tuple_;

};

template <typename... Types>
using PlainTuple = Tuple<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
