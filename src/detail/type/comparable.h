#ifndef BINARY_MAPPING_SRC_DETAIL_COMPARABLE_H_
#define BINARY_MAPPING_SRC_DETAIL_COMPARABLE_H_

#include "transformation.h"

namespace BinaryMapping {
namespace dtl {

template <typename Type>
class Comparable {
	public:
		bool operator==(const_lvalue_reference<Comparable> src) const {
			return this->index_ == src.index_;
		}

		bool operator!=(const_lvalue_reference<Comparable> src) const {
			return !(*this == src);
		}

		bool operator<(const_lvalue_reference<Comparable> src) const {
			return this->index_ < src.index_;
		}

		bool operator>(const_lvalue_reference<Comparable> src) const {
			return this->index_ > src.index_;
		}

		bool operator<=(const_lvalue_reference<Comparable> src) const {
			return !this->operator>(src);
		}

		bool operator>=(const_lvalue_reference<Comparable> src) const {
			return !this->operator<(src);
		}

	protected:
		Type index_;

		explicit Comparable(Type value):
			index_(value) { }


};

}
}

#endif  // BINARY_MAPPING_SRC_DETAIL_COMPARABLE_H_
