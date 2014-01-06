#ifndef BINARY_MAPPING_SRC_TUPLE_RELATIVE_POINTER_H_
#define BINARY_MAPPING_SRC_TUPLE_RELATIVE_POINTER_H_

namespace BinaryMapping {

template<
	typename Base,
	typename Type
>
class RelativePointer {
	static_assert(
		std::is_integral<Base>::value,
		"RelativePointer accepts only integral base types"
	);

	static_assert(
		std::is_integral<Type>::value,
		"RelativePointer accepts only integral target types"
	);

	typedef typename std::add_pointer<
		typename std::add_const<
			typename std::add_pointer<Base>::type
		>::type
	>::type base_ptr;

	typedef typename std::add_pointer<Type>::type target_ptr;

	public:
		typedef Type element_type;

		RelativePointer(base_ptr base, off_t offset):
			base_(base),
			offset_(offset) { }

		inline target_ptr get() const {
			return reinterpret_cast<target_ptr>(
				*this->base_ + this->offset_
			);
		}

		inline Type operator*() const {
			return *this->get();
		}

		bool operator==(const RelativePointer<Base, Type>& ptr) const {
			return this->get() == ptr.get();
		}

		bool operator!=(const RelativePointer<Base, Type>& ptr) const {
			return this->get() != ptr.get();
		}

	private:
		base_ptr const base_;
		const off_t offset_;
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_RELATIVE_POINTER_H_
