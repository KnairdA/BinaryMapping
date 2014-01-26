#ifndef BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
#define BINARY_MAPPING_SRC_TUPLE_TUPLE_H_

#include <tuple>

#include "utility.h" 
#include "base_ptr.h"

#include "mapper.h" 
#include "modifier/relative_tuple.h"
#include "modifier/value_tuple.h"

#include "weigher.h" 
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
	typedef std::tuple<RelativePointer<uint8_t, Types>...> relative_tuple;

	template <size_t Index>
	using type_at = typename std::tuple_element<
		Index,
		relative_tuple
	>::type::element_type;

	public:
		typedef std::tuple<Types...> tuple_type;

		static const size_t size = TupleWeigher::size<relative_tuple>();

		Tuple(uint8_t*const data):
			base_ptr_(data),
			tuple_(TupleMapper::construct<
				RelativeTuple,
				relative_tuple
			>(
				this->base_ptr_.get()
			)) { }

		Tuple(Buffer* buffer):
			Tuple(buffer->front()) { }

		Tuple(const BufferIterator<size>& iter):
			base_ptr_(iter()),
			tuple_(TupleMapper::construct<
				RelativeTuple,
				relative_tuple
			>(
				this->base_ptr_.get()
			)) { }

		inline tuple_type get() const {
			return TupleMapper::construct<
				ValueTuple<Endianess>,
				tuple_type
			>(
				this->base_ptr_.get()
			);
		}

		template <size_t Index> 
		inline type_at<Index> get() const {
			return OutOfPlaceSorter<Endianess>::sort(
				*std::get<Index>(this->tuple_)
			);
		}

		inline uint8_t* ptr() const {
			return *this->base_ptr_.get();
		}

		template <size_t Index> 
		inline typename std::add_pointer<type_at<Index>>::type ptr() const {
			return std::get<Index>(this->tuple_).get();
		}

		template <size_t Index>
		inline void set(const_lvalue_reference<type_at<Index>> value) {
			InPlaceSorter<Endianess>::template mix<
				type_at<Index>
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

			Serializer<CustomOrder>::serialize(this->tuple_);
		}

		template <typename CustomOrder>
		inline void deserialize() {
			static_assert(
				std::is_same<Endianess, UndefinedEndian>::value,
				"Endianess must be UndefinedEndian to use deserialize<*>()"
			);

			Serializer<CustomOrder>::deserialize(this->tuple_);
		}

	protected:
		const detail::BasePtr base_ptr_;
		const relative_tuple tuple_;

};

template <typename... Types>
using PlainTuple = Tuple<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
