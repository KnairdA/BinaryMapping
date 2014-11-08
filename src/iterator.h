#ifndef BINARY_MAPPING_SRC_ITERATOR_H_
#define BINARY_MAPPING_SRC_ITERATOR_H_

#include <cstddef>
#include <iterator>
#include <type_traits>

#include "detail/type/comparable.h"
#include "detail/io/iterator.h"

namespace BinaryMapping {

namespace dtl {
	template <typename Type, typename Base>
	using select_iterator = typename std::conditional<
		std::is_const<Base>::value,
		dtl::Buffer::const_iterator_type<Type::template type<Base>::size>,
		dtl::Buffer::iterator_type<Type::template type<Base>::size>
	>::type;
}

template <typename Type>
template <typename Base>
class Container<Type>::iterator:
	public std::iterator<
		std::random_access_iterator_tag,
		Type&,
		std::ptrdiff_t,
		Type*
	>,
	public dtl::Comparable<
		dtl::select_iterator<Type, Base>
	> {
	public:
		typedef typename Type::template type<Base> element_type;

		element_type& operator*() {
			return this->element_;
		}

		typename element_type::value_type operator*() const {
			return this->element_;
		}

		iterator& operator++() {
			++this->index_;

			return *this;
		}

		iterator operator++(int) {
			iterator tmp(*this);

			this->operator++();

			return tmp;
		}

		iterator& operator--() {
			--this->index_;

			return *this;
		}

		iterator operator--(int) {
			iterator tmp(*this);

			this->operator--();

			return tmp;
		}

		iterator& operator+=(std::ptrdiff_t offset) {
			this->index_ += offset;

			return *this;
		}

		iterator& operator-=(std::ptrdiff_t offset) {
			this->index_ -= offset;

			return *this;
		}

		iterator operator+(std::ptrdiff_t offset) const {
			return iterator(*this) += offset;
		}

		std::ptrdiff_t operator-(
			dtl::const_lvalue_reference<iterator> src) const {
			return this->index_ - src.index_;
		}

		iterator operator-(std::ptrdiff_t offset) const {
			return iterator(*this) -= offset;
		}

		iterator operator[](std::ptrdiff_t offset) const {
			return *(this->operator+(offset));
		}

		friend iterator operator+(
			std::ptrdiff_t offset,
			dtl::const_lvalue_reference<iterator> src
		) {
			return iterator(src) += offset;
		}

	protected:
		friend Container<Type>;

		explicit iterator(dtl::select_iterator<Type, Base>&& index):
			dtl::Comparable<dtl::select_iterator<Type, Base>>(index),
			element_(&this->index_) { }

	private:
		element_type element_;

};

}

#endif  // BINARY_MAPPING_SRC_ITERATOR_H_
