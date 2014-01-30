# BinaryMapping

... is a collection of C++ templates which may be used to map binary structures into tuples. These tuples can then be traversed using integrated containers and iterators. This is useful for many kinds of data serialization tasks.

A explanation of an earlier version of this template library can be found on my [blog](http://blog.kummerlaender.eu/artikel/mapping-binary-structures-as-tuples-using-template-metaprogramming).

Basic usage of this library is documented in the [wiki](https://github.com/KnairdA/BinaryMapping/wiki/Basic-Usage).

## Current features

- Support for any kind of flat structure that consists of integral types
- Full support for serialization in either big or little endianess
- Container and Iterator templates for fast traversal of collections of tuples
- Integrated relative pointer template
- Builds on `std::tuple` and doesn't require any external libraries
- Header only library because of heavy usage of template metaprogramming
- Unit Tests based on GoogleTest
- MIT license

## Example usage

```
BinaryMapping::Buffer buffer(100);

BinaryMapping::Container<
	BinaryMapping::LittleEndian,
	uint32_t,
	int16_t,
	BinaryMapping::Raw<3>,
	uint8_t
> container(&buffer);

for ( auto&& tuple : container ) {
	tuple.set<0>(UINT32_MAX);
	tuple.set<1>(INT16_MAX);
	tuple.set<2>({1, 2, 3});
	tuple.set<3>(42);
}

uint32_t test = container.at(5).get<0>();
```

The code listet above instantiates a 100 byte buffer, defines a container of a structure consisting of a `uint32_t`, `int16_t`, 3-byte and `uint8_t` field with little endianess on this buffer, iterates through all 10 elements, gives them values, transparently converts to the correct endianess and extracts the value of the first field of the fifth tuple contained in the buffer.
In short: BinaryMapping is a library that abstracts endianess aware serializing of binary structures into tuples, containers and iterators.
If you are interested in further details of the usage of all features provided by BinaryMapping don't hesitate to check out the appropriate [wiki-page](https://github.com/KnairdA/BinaryMapping/wiki/Basic-Usage).

## Building

As the BinaryMapping library is a header only library in can only be built in conjunction with the code which is making use of it.
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
