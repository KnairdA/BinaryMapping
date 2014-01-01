#ifndef BINARY_MAPPING_SRC_TUPLE_RELATIVE_POINTER_H_
#define BINARY_MAPPING_SRC_TUPLE_RELATIVE_POINTER_H_

namespace BinaryMapping {

template<
	typename Base,
	typename Type,
	typename BasePtr   = typename std::enable_if<
		std::is_integral<Base>::value,
		typename std::add_pointer<
			typename std::add_const<
				typename std::add_pointer<Base>::type
			>::type
		>::type
	>::type,
	typename TargetPtr = typename std::enable_if<
		std::is_integral<Type>::value,
		typename std::add_pointer<Type>::type
	>::type
>
class RelativePointer {
	public:
		typedef Type element_type;
		typedef TargetPtr pointer;

		RelativePointer(BasePtr base, off_t offset):
			base_(base),
			offset_(offset) { }

		inline TargetPtr get() const {
			return reinterpret_cast<TargetPtr>(
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
		BasePtr const base_;
		const off_t offset_;
};

}

#endif  // BINARY_MAPPING_SRC_TUPLE_RELATIVE_POINTER_H_
