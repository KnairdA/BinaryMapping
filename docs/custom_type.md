### Implementing custom types

While many different structures can be expressed using the `Tuple` template provided by BinaryMapping one may wish to implement custom types to be used by the libraries `Container` and `Iterator` templates. This file aims to document the aspects such a type has to provide to be accepted as a specialization type for the `Container` and consequently the `Iterator` template.

Most of the complexity required in custom types is caused by the need to make them specializable on different base types in the library itself. Types need to be specializable on different base types to preserve const-correctness from the raw buffer up to the higher level interface provided by this library. This means that each custom type consists of at least two parts: its implementation and a kind of alias template which is used to specialize on base types.

The following example implements the logic of a simple custom type which maps a single field of the provided type.

```
#include "<library>/helper/base_pointer.h"
#include "<library>/helper/relative_pointer.h"

template <
	typename Base,
	typename Type,
>
class TestTypeImpl {
	public:
		typedef typename std::remove_const<Type>::type value_type;

		static const size_t size = sizeof(Type);

		template <typename BaseType>
		TestTypeImpl(BaseType data):
			base_ptr_(data),
			value_(base_ptr_.get(), 0) { }

		inline operator value_type() const {
			return *this->value_.get();
		}

		inline void operator=(value_type value) {
			*this->value_.get() = value;
		}

	private:
		const BinaryMapping::BasePointer<Base> base_ptr_;
		BinaryMapping::RelativePointer<Base, Type> value_;

};
```

As we can see this code snippet implements a class template which takes two arguments: a base type and a type to specialize the content. As we have to implement an alias template for this type its specialization signature can be choosen freely. The only things that are required to be provided is the `value_type` typedef which defines the type of the contained value, a operator to cast the value to this type, a static const size field  which provides the fixed size of the contained value, a constructor which accepts both const and non-const versions of the base type and an assignment operator which can be used to set the contained value through a `value_type` instance. In this example we make use of the helper templates `BasePointer` and `RelativePointer`. These types are used and provided by the library and simplifiy the development of custom types by offering the possibility of relative and indirect pointers. However we are not required to use these types.

```
template <
	typename Type
>
struct TestType {
	template <typename Base>
	using type = typename std::conditional<
		std::is_const<Base>::value,
		TestTypeImpl<
			Base,
			typename std::add_const<Type>::type
		>,
		TestTypeImpl<Base, Type>
	>::type;
};
```

This example depicts the appropriate alias template which is required to integrate our `TestTypeImpl` template type into the BinaryMapping libary. As we can see the alias struct only contains a single alias template `type` which offers the possibility of base type specialization. If we wanted to use this type we could specialize a `Container` template instance as follows:

```
BinaryMapping::Container<
	TestType<uint32_t>
> container(10);
```

This code snippet specializes the `Container` template and constructs it to contain ten instances of the given type. We have now implemented a simple example type that can be used to map all custom serializable or integral types onto raw binary buffers. While this may not be particularly usefull it should provide us with all the information needed to start to implement our own mapping types. If one wanted to see a more complex example one may look into the special use case test cases or simply read the `Tuple` template implementation.
