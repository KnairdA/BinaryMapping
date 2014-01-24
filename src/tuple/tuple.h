#ifndef BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
#define BINARY_MAPPING_SRC_TUPLE_TUPLE_H_

#include <tuple>

#include "utility.h" 

#include "mapper.h" 
#include "weigher.h" 
#include "relative_pointer.h" 

#include "io/buffer.h" 

#include "endianess/serializer.h" 
#include "endianess/in_place_sorter.h" 
#include "endianess/out_of_place_sorter.h" 
#include "endianess/undefined.h" 

namespace BinaryMapping {

namespace {
	enum class Target : uint8_t {
		Pointer,
		Iterator
	};
}

template <
	typename Endianess,
	typename... Types
>
class Tuple {
	public:
		typedef std::tuple<RelativePointer<uint8_t, Types>...> tuple_type;

		template <size_t Index>
		using type_at = typename std::tuple_element<
			Index,
			tuple_type
		>::type::element_type;

		static const size_t size = TupleWeigher::size<tuple_type>();

		Tuple(uint8_t* data):
			base_ptr_(
				reinterpret_cast<uintptr_t>(data)
			),
			tuple_(TupleMapper::construct<tuple_type>(
				reinterpret_cast<uint8_t*const*>(&this->base_ptr_)
			)),
			target_(
				Target::Pointer
			) { }

		Tuple(Buffer* buffer):
			Tuple(buffer->front()) { }

		Tuple(const BufferIterator<size>& iter):
			base_ptr_(
				reinterpret_cast<uintptr_t>(iter())
			),
			tuple_(TupleMapper::construct<tuple_type>(
				reinterpret_cast<uint8_t*const*>(this->base_ptr_)
			)),
			target_(
				Target::Iterator
			) { }

		Tuple<Endianess, Types...> anchored_copy() {
			switch ( this->target_ ) {
				case Target::Pointer:  return Tuple<Endianess, Types...>(
					reinterpret_cast<uint8_t*>(this->base_ptr_)
				);
				case Target::Iterator: return Tuple<Endianess, Types...>(
					*reinterpret_cast<uint8_t*const*>(this->base_ptr_)
				);
			}
		}

		template <size_t Index> 
		inline type_at<Index> get() const {
			return OutOfPlaceSorter<Endianess>::sort(
				*std::get<Index>(this->tuple_)
			);
		}

		template <size_t Index> 
		inline typename std::add_pointer<type_at<Index>>::type ptr() const {
			return std::get<Index>(this->tuple_).get();
		}

		template <size_t Index>
		inline void set(ConstLValueReference<type_at<Index>> value) {
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
		const uintptr_t base_ptr_;
		const tuple_type tuple_;
		const Target target_;

};

template <typename... Types>
using PlainTuple = Tuple<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
