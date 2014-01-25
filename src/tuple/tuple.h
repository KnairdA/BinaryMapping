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
	enum class Tag: uint8_t {
		Direct,
		Indirect
	};

	struct BasePtr {
		BasePtr(uint8_t*const ptr):
			direct(ptr),
			tag(Tag::Direct) { }

		BasePtr(uint8_t*const* ptr):
			indirect(ptr),
			tag(Tag::Indirect) { }

		const union {
			uint8_t*const  direct;
			uint8_t*const* indirect; 
		};

		const Tag tag;
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

		Tuple(uint8_t*const data):
			base_ptr_(
				data
			),
			tuple_(
				TupleMapper::construct<tuple_type>(&this->base_ptr_.direct)
			) { }

		Tuple(Buffer* buffer):
			Tuple(buffer->front()) { }

		Tuple(const BufferIterator<size>& iter):
			base_ptr_(
				iter()
			),
			tuple_(
				TupleMapper::construct<tuple_type>(this->base_ptr_.indirect)
			) { }

		Tuple<Endianess, Types...> anchored_copy() {
			switch ( this->base_ptr_.tag ) {
				case Tag::Direct: return Tuple<Endianess, Types...>(
					this->base_ptr_.direct
				);
				case Tag::Indirect: return Tuple<Endianess, Types...>(
					this->base_ptr_.indirect
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
		const BasePtr base_ptr_;
		const tuple_type tuple_;

};

template <typename... Types>
using PlainTuple = Tuple<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TUPLE_TUPLE_H_
