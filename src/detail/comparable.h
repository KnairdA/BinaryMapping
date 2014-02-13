#ifndef BINARY_MAPPING_SRC_DETAIL_COMPARABLE_H_
#define BINARY_MAPPING_SRC_DETAIL_COMPARABLE_H_

#include "utility.h"

namespace BinaryMapping {
namespace dtl {

template <typename Type>
class Comparable {
	public:
		Comparable(Type value):
			index_(value) { }

		inline bool operator==(const_lvalue_reference<Comparable> src) const {
			return this->index_ == src.index_;
		}

		inline bool operator!=(const_lvalue_reference<Comparable> src) const {
			return !(*this == src);
		}

		inline bool operator<(const_lvalue_reference<Comparable> src) const {
			return this->index_ < src.index_;
		}

		inline bool operator>(const_lvalue_reference<Comparable> src) const {
			return this->index_ > src.index_;
		}

		inline bool operator<=(const_lvalue_reference<Comparable> src) const {
			return !this->operator>(src);
		}

		inline bool operator>=(const_lvalue_reference<Comparable> src) const {
			return !this->operator<(src);
		}

	protected:
		Type index_;

};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_COMPARABLE_H_
