# BinaryMapping

... is a collection of C++ templates which may be used to map binary structures into tuples and various other structures. These structures can then be traversed using integrated containers and iterators. This is useful for many kinds of data serialization tasks.

A explanation of an earlier version of this template library can be found on my [blog](http://blog.kummerlaender.eu/artikel/mapping-binary-structures-as-tuples-using-template-metaprogramming).

Basic usage of this library is documented in the appropriate [file](https://github.com/KnairdA/BinaryMapping/blob/master/docs/basic_usage.md).

## Current features

- Support for any kind of flat structure that can be expressed using integral types and arbitrarily sized byte-arrays
- Support for serialization in either big or little endianess
- Offers Container and Iterator templates for fast traversal of collections of tuples or other structures
- Support for developing custom types to be used in the Container and Iterator templates
- Support for nesting structures inside each other
- BitField template offers bit-level access to ByteField byte-arrays
- Doesn't require any external libraries besides the GNU libraries _endian.h_
- Header only library because of heavy usage of template metaprogramming
- Unit Tests based on GoogleTest
- MIT license

## Example usage

```
BinaryMapping::Container<
	BinaryMapping::Tuple<
		BinaryMapping::LittleEndian,
		std::uint32_t,
		std::int16_t,
		BinaryMapping::ByteField<3>,
		std::uint8_t
	>
> container(10);

for ( auto&& tuple : container ) {
	tuple.set<0>(UINT32_MAX);
	tuple.set<1>(INT16_MAX);
	tuple.set<2>({1, 2, 3});
	tuple.set<3>(42);
}

std::uint32_t test = container.at(5).get<0>();
```

The code listed above defines a container of a tuple consisting of a `std::uint32_t`, `std::int16_t`, 3-byte and `std::uint8_t` field with little endianess, instantiates a buffer containing ten instances of this tuple, iterates through all 10 elements, gives them values, transparently converts to the correct endianess and extracts the value of the first field of the fifth tuple contained in the buffer.
In short: BinaryMapping is a library that abstracts endianess aware serializing of binary structures into structures, containers and iterators.
If you are interested in further details of the usage of all features provided by BinaryMapping don't hesitate to check out the [documentation](https://github.com/KnairdA/BinaryMapping/blob/master/docs/).

## Limitations

It is currently no problem to define unaligned structures using this library. What this means is that BinaryMapping is only fully supported on processors supporting unaligned memory access such as x86. As the test cases currently contain unaligned structures they will fail in parts on unsupported architectures. One way to work around this issue is to define only aligned structures.

## Building

As the BinaryMapping library is a header only library it can only be built in conjunction with the code which is making use of it.
The GoogleTest based test cases of BinaryMapping are using CMake as a build system and can be cloned and compiled as follows:

```
git clone "https://github.com/KnairdA/BinaryMapping.git"
cd BinaryMapping
mkdir build
cd build
cmake ..
make
```

## Requirements

- Current version of GCC or Clang C++ compiler with full support for C++11 (tested in g++ >= 4.8.2 and clang++ >= 3.3)
- GNU libraries _endian.h_ for endianess conversion support
- [CMake](http://www.cmake.org/) for building
- [GoogleTest](http://code.google.com/p/googletest/) for tests
