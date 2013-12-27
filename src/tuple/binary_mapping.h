#ifndef BINARY_MAPPING_SRC_TUPLE_BINARY_MAPPING_H_
#define BINARY_MAPPING_SRC_TUPLE_BINARY_MAPPING_H_

#include <tuple>

#include "mapper.h" 
#include "weigher.h" 
#include "binary_mapping_carbon_copy.h" 
#include "relative_pointer.h" 

#include "io/buffer_guard.h" 

#include "endianess/serializer.h" 
#include "endianess/in_place_sorter.h" 
#include "endianess/out_of_place_sorter.h" 
#include "endianess/undefined.h" 

namespace BinaryMapping {

template <
	typename Endianess,
	typename... Types
>
class BinaryMapping {
	public:
		typedef BinaryMappingCarbonCopy<Types...> CarbonCopy;
		typedef std::tuple<RelativePointer<uint8_t, Types>...> tuple_type;

		static const size_t tuple_size = TupleWeigher::size<tuple_type>();

		BinaryMapping(BufferGuard& data):
			buffer_(data.data),
			tuple_(TupleMapper::construct<tuple_type>(&this->buffer_)) { }

		template <size_t Index> inline typename
		std::tuple_element<Index, tuple_type>::type::element_type get() const {
			return OutOfPlaceSorter<Endianess>::sort(
				*std::get<Index>(this->tuple_)
			);
		}

		template <size_t Index>
		inline void set(
			typename std::add_lvalue_reference<
				typename std::add_const<
					typename std::tuple_element<Index, tuple_type>::type::element_type
				>::type
			>::type value
		) {
			InPlaceSorter<Endianess>::template mix<
				typename std::tuple_element<Index, tuple_type>::type::element_type
			>(
				std::get<Index>(this->tuple_).get(),
				value
			);
		}

		template <
			typename CustomOrder,
			typename Helper = Endianess
		>
		inline typename std::enable_if<
			std::is_same<UndefinedEndian, Helper>::value,
			void
		>::type serialize() {
			Serializer<InPlaceSorter<CustomOrder>>::serialize(this->tuple_);
		}

		template <
			typename CustomOrder,
			typename Helper = Endianess
		>
		inline typename std::enable_if<
			std::is_same<UndefinedEndian, Helper>::value,
			void
		>::type deserialize() {
			Serializer<InPlaceSorter<CustomOrder>>::deserialize(this->tuple_);
		}

		inline void slide(off_t offset) {
			this->buffer_ += tuple_size * offset;
		}

		CarbonCopy carbonCopy() const {
			return CarbonCopy(*this);
		}

	private:
		uint8_t* buffer_;
		const tuple_type tuple_;

};

template <typename... Types>
using PlainBinaryMapping = BinaryMapping<UndefinedEndian, Types...>;

}

#endif  // BINARY_MAPPING_SRC_TUPLE_BINARY_MAPPING_H_
