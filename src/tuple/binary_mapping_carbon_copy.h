#ifndef BINARY_MAPPING_SRC_TUPLE_BINARY_MAPPING_CARBON_COPY_H_
#define BINARY_MAPPING_SRC_TUPLE_BINARY_MAPPING_CARBON_COPY_H_

namespace BinaryMapping {

template <typename... Types>
class BinaryMappingCarbonCopy {
	public:
		typedef std::tuple<Types...> tuple_type;

		template <typename Source>
		BinaryMappingCarbonCopy(const Source& src):
			tuple_(TupleMapper::carbonCopy<tuple_type>(src)) { }

		template <size_t Index> inline typename
		std::tuple_element<Index, tuple_type>::type get() const {
			return std::get<Index>(this->tuple_);
		}

	private:
		const tuple_type tuple_;

};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_BINARY_MAPPING_CARBON_COPY_H_
