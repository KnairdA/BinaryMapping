#ifndef BINARY_MAPPING_SRC_DETAIL_TUPLE_TUPLE_H_
#define BINARY_MAPPING_SRC_DETAIL_TUPLE_TUPLE_H_

#include <cstddef>
#include <tuple>

#include "detail/type/transformation.h"

#include "helper/base_pointer.h"
#include "helper/relative_pointer.h"
#include "helper/in_place_sorter.h"
#include "helper/out_of_place_sorter.h"

#include "detail/tuple/setter.h"
#include "detail/tuple/weigher.h"
#include "detail/tuple/serializer.h"

#include "detail/tuple/mapper.h"
#include "detail/tuple/modifier/relative_tuple.h"
#include "detail/tuple/modifier/value_tuple.h"

#include "endianess/undefined.h"

namespace BinaryMapping {
namespace dtl {

template <
	typename Base,
	typename Endianess,
	typename... Types
>
class Tuple {
	typedef std::tuple<RelativePointer<Base, Types>...> relative_tuple;

	template <std::size_t Index>
	using type_at = typename std::tuple_element<
		Index,
		relative_tuple
	>::type::element_type;

	public:
		typedef std::tuple<
			typename std::remove_const<Types>::type...
		> value_type;

		static const std::size_t size = Weigher::size<relative_tuple>();

		template <typename BaseType>
		Tuple(BaseType data):
			base_ptr_(data),
			tuple_(Mapper::construct<
				RelativeTuple,
				relative_tuple
			>(
				this->base_ptr_.get()
			)) { }

		operator value_type() const {
			return Mapper::construct<
				ValueTuple<Endianess>,
				value_type
			>(
				this->base_ptr_.get()
			);
		}

		template <std::size_t Index>
		type_at<Index> get() const {
			return OutOfPlaceSorter<Endianess>::sort(
				*std::get<Index>(this->tuple_)
			);
		}

		template <std::size_t Index>
		pointer_to_const<type_at<Index>> ptr() const {
			return std::get<Index>(this->tuple_).get();
		}

		void operator=(const_lvalue_reference<value_type> values) {
			Setter<Endianess>::template populate<
				relative_tuple,
				value_type
			>(values, this->tuple_);
		}

		template <std::size_t Index>
		void set(const_lvalue_reference<type_at<Index>> value) {
			InPlaceSorter<Endianess>::template mix<
				type_at<Index>
			>(
				std::get<Index>(this->tuple_).get(),
				value
			);
		}

		template <std::size_t Index>
		typename std::add_pointer<type_at<Index>>::type ptr() {
			return std::get<Index>(this->tuple_).get();
		}

		template <typename CustomOrder>
		void serialize() {
			static_assert(
				std::is_same<Endianess, UndefinedEndian>::value,
				"Endianess must be UndefinedEndian to use serialize<*>()"
			);

			dtl::Serializer<CustomOrder>::serialize(this->tuple_);
		}

		template <typename CustomOrder>
		void deserialize() {
			static_assert(
				std::is_same<Endianess, UndefinedEndian>::value,
				"Endianess must be UndefinedEndian to use deserialize<*>()"
			);

			dtl::Serializer<CustomOrder>::deserialize(this->tuple_);
		}

	protected:
		const BasePointer<Base> base_ptr_;
		const relative_tuple tuple_;

};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_TUPLE_TUPLE_H_
